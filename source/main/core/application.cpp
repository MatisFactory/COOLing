#include <main/core/application.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <cassert>

namespace
{
	static bool isOpen = true;
	static bool isCullingOptimizationForMain = true;
	static bool isCullingOptimizationForNotMain = false;
	static bool rotateNotMainCameraByYaw = false;
}

Application::Application()
	: m_cameraManager(m_window)
{
	m_cubeManager.setCullingManager(&m_cullingManager);
	m_cubeManager.init();
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

	Camera* notMainCamera = m_cameraManager.getFirstNotMainCamera();
	m_cameraDrawer.setCameraToDraw(notMainCamera);

	if(isCullingOptimizationForMain)
	{
		m_cullingManager.setViewProjectionMatrix(CameraManager::mainProjectionMatrix() * CameraManager::mainViewMatrix());
	}
	else if (isCullingOptimizationForNotMain && notMainCamera)
	{
		m_cullingManager.setViewProjectionMatrix(notMainCamera->getProjection() * notMainCamera->getView());
	}

	if (rotateNotMainCameraByYaw)
	{
		notMainCamera->rotateByYaw(dt * notMainCamera->cameraSpeed()/2.f);
	}

	m_cullingManager.update();
}

void Application::draw()
{
	m_cameraDrawer.draw();
	m_cubeManager.draw();
}

void Application::imguiNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Application::addToDrawImGui()
{
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
		if (ImGui::Combo("Camera pack", &currentCameraIndex, cameraGetter, static_cast<void*>(&cameraPack), m_cameraManager.size()))
		{
			m_cameraManager.setMainCamera(currentCameraIndex);
		}

		if (ImGui::Button("Add camera"))
		{
			m_cameraManager.insertCamera();
		}

		if (ImGui::Checkbox("Culling objects by main camera", &isCullingOptimizationForMain) ||
			ImGui::Checkbox("Culling objects by not main camera", &isCullingOptimizationForNotMain))
		{
			if (isCullingOptimizationForMain || isCullingOptimizationForNotMain)
			{
				m_cubeManager.setCullingManager(&m_cullingManager);
			}
			else
			{
				m_cubeManager.setCullingManager(nullptr);
			}
		}

		ImGui::Checkbox("Rotate not main camera", &rotateNotMainCameraByYaw);

		ImGui::End();
	}
}

void Application::renderImGui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
