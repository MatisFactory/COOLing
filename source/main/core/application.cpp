#include <core/application.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

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
	, m_cameraManager(m_window)
{
	initModels();
}

void Application::run()
{
	m_clock.update();

	while (!m_window.windowShouldClose())
	{
		glfwPollEvents();

		imguiNewFrame();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_shader.use();

		m_clock.update();
		tick(m_clock.getDeltaTime());

		draw();
		addToDrawImGui();
		
		renderImGui();

		glfwSwapBuffers(m_window.getGLFWwindow());
	}
}

void Application::tick(float dt)
{
	m_cameraManager.tick(dt);
	setupViewProjection();
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
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_cameraManager.getMainCamera()->getView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_cameraManager.getMainCamera()->getProjection()));
}

void Application::imguiNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Application::addToDrawImGui()
{
	static bool isOpen = true;

	if (!ImGui::Begin("Debug window", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		int currentCameraIndex = m_cameraManager.getMainCameraIndex();

		auto cameraGetter = [](void* vec, int idx, const char** out_text) -> bool
		{
			auto cameraPack = *static_cast<std::vector<CameraPtr>*>(vec);
			if (idx < 0 || idx >= cameraPack.size())
			{
				return false;
			}
			*out_text = cameraPack[idx]->getName();
			return true;
		};

		CameraPack cameraPack = m_cameraManager.getCameraPack();
		if (ImGui::Combo("Camera pack", &currentCameraIndex, cameraGetter, static_cast<void*>(&cameraPack), m_cameraManager.count()))
		{
			m_cameraManager.setMainCamera(currentCameraIndex);
		}

		if (ImGui::Button("Add camera"))
		{
			m_cameraManager.insertCamera();
		}

		ImGui::End();
	}
}

void Application::renderImGui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
