#include <core/application.hpp>
#include <core/clock/clock.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <cassert>
#include <random>

namespace
{
	static constexpr size_t COUNT_OF_CUBES = 10000;
	static constexpr float WIDTH = 500.f;
	static constexpr float HEIGHT = 20;
}

Application::Application()
	: m_shader("../../../shaders/VertexShader.txt", "../../../shaders/FragmentShader.txt")
	, m_camera(m_window, glm::vec3(0.f, 0.f, 0.f), 
		glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), 45.f, 0.1f, 1000.f)
{
	initModels();
}

void Application::run()
{
	Clock clock;

	while (!m_window.windowShouldClose())
	{
		ImGui_ImplGlfwGL3_NewFrame();

		{
			static float f = 0.0f;
			ImGui::Text("Hello, world!");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", clock.getDeltaTime(), 1000.f/clock.getDeltaTime());
		}

		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_shader.use();

		clock.computeDeltaTime();
		tick(clock.getDeltaTime());
		draw();

		ImGui::Render();

		setupViewProjection();
		glfwSwapBuffers(m_window.getGLFWwindow());
	}
}

void Application::tick(float dt)
{
	m_camera.tick(dt);
}

void Application::draw()
{
	for (auto& cube : m_cubes)
	{
		cube.draw();
	}
}

void Application::initModels()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution plate(-WIDTH, WIDTH);
	std::uniform_real_distribution vertical(-HEIGHT, HEIGHT);

	m_cubes.reserve(COUNT_OF_CUBES);

	for (size_t i = 0; i < COUNT_OF_CUBES; i++)
	{
		glm::mat4 transform = glm::mat4(1.f);
		transform[3][0] = plate(gen);
		transform[3][1] = vertical(gen);
		transform[3][2] = plate(gen);
		m_cubes.emplace_back(transform, m_shader.ID);
	}
}

void Application::setupViewProjection()
{
	GLint viewLoc = glGetUniformLocation(m_shader.ID, "view");
	GLint projLoc = glGetUniformLocation(m_shader.ID, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_camera.getView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_camera.getProjection()));
}
