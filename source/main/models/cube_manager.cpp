#include <main/models/cube_manager.hpp>
#include <main/core/camera/camera_manager.hpp>
#include <main/core/settings/scene_settings.hpp>
#include <main/core/culling_wrapper.hpp>

#include <cooling/utils/visibility_tests.hpp>
#include <cooling/utils/aabb.hpp>
#include <cooling/profiler/profiler.hpp>

#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <random>
#include <cassert>


CubeManager::CubeManager()
	: m_shader("../../../shaders/Cube.vertexShader", "../../../shaders/Cube.fragmentShader")
	, m_transformLocation(glGetUniformLocation(m_shader.ID, "model"))
{
}

void CubeManager::init(uint32_t count /*= COUNT_OF_CUBES*/)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution plate(-SCENE_WIDTH, SCENE_WIDTH);
	std::uniform_real_distribution vertical(-SCENE_HEIGHT, SCENE_HEIGHT);

	m_cubes.reserve(count);

	for (size_t i = 0; i < count; i++)
	{
		glm::mat4 transform = glm::mat4(1.f);
		transform[3][0] = plate(gen);
		transform[3][1] = vertical(gen);
		transform[3][2] = plate(gen);
		m_cubes.emplace_back(transform);

		Cooling::AABB aabb;
		aabb = Cooling::createAABBByVertex(m_cubes.back().getVertices());
		m_cullingIndexes.emplace_back(CullingWrapper::instance().cullingManager().registerObject(aabb));
	}
}

void CubeManager::draw()
{
	Cooling::Profiler p("Draw");

	m_countDrawedCube = 0;
	m_shader.use();
	setupViewProjection();

	for (uint32_t i = 0; i < m_cubes.size(); i++)
	{
		if (!CullingWrapper::instance().cullingManager().isVisible(i))
		{
			continue;
		}

		glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(m_cubes[i].worldTransform()));
		m_cubes[i].draw();
		m_countDrawedCube++;
	}
}

uint32_t CubeManager::countDrawedCube() const
{
	return m_countDrawedCube;
}

void CubeManager::setupViewProjection()
{
	GLint viewLoc = glGetUniformLocation(m_shader.ID, "view");
	GLint projLoc = glGetUniformLocation(m_shader.ID, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(CameraManager::currentViewMatrix()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(CameraManager::currentProjectionMatrix()));
}
