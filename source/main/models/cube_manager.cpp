#include <main/models/cube_manager.hpp>
#include <main/core/camera/camera_manager.hpp>
#include <cooling/utils/visibility_tests.hpp>

#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <random>
#include <cassert>

namespace
{
	constexpr float WIDTH = 1000.f;
	constexpr float HEIGHT = 200.f;
}

CubeManager::CubeManager()
	: m_shader("../../../shaders/Cube.vertexShader", "../../../shaders/Cube.fragmentShader")
	, m_transformLocation(glGetUniformLocation(m_shader.ID, "model"))
{
}

void CubeManager::init(uint32_t count /*= COUNT_OF_CUBES*/)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution plate(-WIDTH, WIDTH);
	std::uniform_real_distribution vertical(-HEIGHT, HEIGHT);

	m_cubes.reserve(count);

	assert(m_cullingManager);

	for (size_t i = 0; i < count; i++)
	{
		glm::mat4 transform = glm::mat4(1.f);
		transform[3][0] = plate(gen);
		transform[3][1] = vertical(gen);
		transform[3][2] = plate(gen);
		m_cubes.emplace_back(transform);
		m_objects.emplace_back(m_cullingManager->registerObject(Cooling::createAABBByVertex(m_cubes.back().getVertices())));
	}
}

void CubeManager::setCullingManager(Cooling::CullingManager* manager)
{
	m_cullingManager = manager;
}

void CubeManager::draw()
{
	m_shader.use();
	setupViewProjection();

	for (uint32_t i = 0; i < m_cubes.size(); i++)
	{
		if (m_cullingManager)
		{
			if (!m_cullingManager->isVisible(i))
			{
				continue;
			}
		}
		glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(m_cubes[i].worldTransform()));
		m_cubes[i].draw();
	}
}

void CubeManager::setupViewProjection()
{
	GLint viewLoc = glGetUniformLocation(m_shader.ID, "view");
	GLint projLoc = glGetUniformLocation(m_shader.ID, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(CameraManager::mainViewMatrix()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(CameraManager::mainProjectionMatrix()));
}
