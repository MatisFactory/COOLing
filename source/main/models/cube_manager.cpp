#include <main/models/cube_manager.hpp>
#include <main/core/camera/camera_manager.hpp>

#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <random>

namespace
{
	constexpr float WIDTH = 500;
	constexpr float HEIGHT = 20;
}

CubeManager::CubeManager(uint32_t count)
	: m_shader("../../../shaders/Cube.vertexShader", "../../../shaders/Cube.fragmentShader")
	, m_transformLocation(glGetUniformLocation(m_shader.ID, "model"))
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution plate(-WIDTH, WIDTH);
	std::uniform_real_distribution vertical(-HEIGHT, HEIGHT);

	m_cubes.reserve(count);

	for (size_t i = 0; i < count; i++)
	{
		glm::mat4 transform = glm::mat4(1.f);
		transform[3][0] = plate(gen);
		transform[3][1] = vertical(gen);
		transform[3][2] = plate(gen);
		m_cubes.emplace_back(transform);
	}
}

void CubeManager::draw()
{
	m_shader.use();
	setupViewProjection();

	for (auto& cube : m_cubes)
	{
		glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(cube.worldTransform()));
		cube.draw();
	}
}

void CubeManager::setupViewProjection()
{
	GLint viewLoc = glGetUniformLocation(m_shader.ID, "view");
	GLint projLoc = glGetUniformLocation(m_shader.ID, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(CameraManager::mainViewMatrix()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(CameraManager::mainProjectionMatrix()));
}
