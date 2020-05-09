#include <main/core/application.hpp>
#include <main/core/settings/scene_settings.hpp>

#include <main/core/drawers/obj_model_drawer.hpp>

#include <cooling/utils/aabb.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <cassert>

namespace
{
	static bool isCullingOptimizationActive = false;
	static bool cullObjectsForCurrentCamera = false;
	static bool cullObjectsForNotCurrentCamera = false;
	static bool basicCullingAlgorithm = false;
	static bool octreeAlgorithm = false;
	static bool regularSpacePartitioningAlgorithm = false;
	static bool rotateNotMainCameraByYaw = false;
	static bool visualizeNotMainCamera = false;
}

Application::Application()
	: m_cameraManager(m_window)
	, m_objDrawer(new ObjModelDrawer("../../../obj_models/airplane.obj"))
{
	Cooling::AABB aabb;
	m_cullingManager.setSceneAABB(Cooling::AABB(glm::vec3(-SCENE_WIDTH, -SCENE_HEIGHT, -SCENE_WIDTH),
												glm::vec3(SCENE_WIDTH, SCENE_HEIGHT, SCENE_WIDTH)));

	//m_cullingManager.setAlgorithm(Cooling::AlRegularSpacePartitioning);

	m_cubeManager.setCullingManager(&m_cullingManager);
	m_cubeManager.init();

	m_cubeManager.setCullObjects(isCullingOptimizationActive);
}

void Application::run()
{
	m_clock.update();

	while (!m_window.windowShouldClose())
	{
		preUpdate();
		update();
		postUpdate();
	}
}

void Application::preUpdate()
{
	glfwPollEvents();

	imguiNewFrame();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::update()
{
	m_clock.update();
	tick(m_clock.getDeltaTime());
}

void Application::postUpdate()
{
	draw();
	addToDrawImGui();
	drawImGui();

	glfwSwapBuffers(m_window.getGLFWwindow());
}

void Application::tick(float dt)
{
	tickCameraManager(dt);
	tickCullingManager(dt);
}

void Application::tickCameraManager(float dt)
{
	m_cameraManager.tick(dt);

	Camera* notMainCamera = m_cameraManager.getFirstNotCurrentCamera();
	m_cameraDrawer.setCameraToDraw(notMainCamera);
}

void Application::tickCullingManager(float dt)
{
	Camera* firstNotCurrentCamera = m_cameraManager.getFirstNotCurrentCamera();

	if (cullObjectsForCurrentCamera)
	{
		m_cullingManager.setViewProjectionMatrix(CameraManager::currentProjectionMatrix() * CameraManager::currentViewMatrix());
	}
	else if (cullObjectsForNotCurrentCamera && firstNotCurrentCamera)
	{
		m_cullingManager.setViewProjectionMatrix(firstNotCurrentCamera->getProjection() * firstNotCurrentCamera->getView());
	}

	m_cullingManager.update();
}

void Application::draw()
{
	if (visualizeNotMainCamera)
	{
		m_cameraDrawer.draw();
	}

	m_objDrawer->draw();
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
		int currentCameraIndex = m_cameraManager.getCurrentCameraIndex();

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
			m_cameraManager.setCurrentCamera(currentCameraIndex);
		}

		if (ImGui::Button("Add camera"))
		{
			m_cameraManager.insertCamera();
		}

		isCullingOptimizationActive = m_cubeManager.cullObjects();
		if (ImGui::Checkbox("Cull objects", &isCullingOptimizationActive))
		{
			m_cubeManager.setCullObjects(isCullingOptimizationActive);
			
			if(isCullingOptimizationActive)
			{
				cullObjectsForCurrentCamera = true;
			}
		}

		if (isCullingOptimizationActive)
		{
			ImGui::Checkbox("Cull objects for current camera", &cullObjectsForCurrentCamera);
			ImGui::Checkbox("Cull objects for first not current camera", &cullObjectsForNotCurrentCamera);
		}

		isCullingOptimizationActive = isCullingOptimizationActive & 
			(cullObjectsForCurrentCamera || cullObjectsForNotCurrentCamera);
		
		m_cubeManager.setCullObjects(isCullingOptimizationActive);

		if (ImGui::Checkbox("Basic culling algorithm", &basicCullingAlgorithm))
		{
			m_cullingManager.setAlgorithm(basicCullingAlgorithm ? Cooling::Basic : Cooling::None);
		}
		if (ImGui::Checkbox("Octree algorithm", &octreeAlgorithm))
		{
			m_cullingManager.setAlgorithm(octreeAlgorithm ? Cooling::OctreeCulling : Cooling::None);
		}
		if (ImGui::Checkbox("Regular space partitioning algorithm", &regularSpacePartitioningAlgorithm))
		{
			m_cullingManager.setAlgorithm(regularSpacePartitioningAlgorithm ? Cooling::AlRegularSpacePartitioning : Cooling::None);
		}

		ImGui::Checkbox("Visualize first not current camera", &visualizeNotMainCamera);

		rotateNotMainCameraByYaw = m_cameraManager.rotateByYaw();
		if (ImGui::Checkbox("Rotate not main camera", &rotateNotMainCameraByYaw))
		{
			m_cameraManager.setRotateByYaw(rotateNotMainCameraByYaw);
		}

		ImGui::LabelText("", "Count drawed cube: %d", m_cubeManager.countDrawedCube());

		ImGui::End();
	}

	if (!ImGui::Begin("Camera", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		ImGuiIO& io = ImGui::GetIO();

		float currentSensitivity = m_cameraManager.getCurrentCamera()->sensitivity();
		if (ImGui::SliderFloat("Sensitivity", &currentSensitivity, 0.0f, 1.0f))
		{
			m_cameraManager.getCurrentCamera()->setSensitivity(currentSensitivity);
		}

		float rotationSpeed = m_cameraManager.getCurrentCamera()->rotationSpeed();
		if (ImGui::SliderFloat("Rotation speed", &rotationSpeed, 0.0f, 1.0f))
		{
			m_cameraManager.getCurrentCamera()->setRotationSpeed(rotationSpeed);
		}

		ImGui::End();
	}
}

void Application::drawImGui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
