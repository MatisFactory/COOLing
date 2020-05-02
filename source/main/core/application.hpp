#pragma once

#include <main/core/window.hpp>
#include <main/core/camera/camera_manager.hpp>
#include <main/core/clock/clock.hpp>
#include <main/core/shader/shader.hpp>
#include <main/models/cube_manager.hpp>
#include <main/core/drawers/camera_drawer.hpp>

class Application
{
public:
	Application();

	void run();
private:
	void tick(float dt);
	void draw();

	void imguiNewFrame();
	void addToDrawImGui();
	void renderImGui();
private:
	Window m_window;
	Clock m_clock;

	CubeManager m_cubeManager;

	CameraManager m_cameraManager;
	CameraDrawer m_cameraDrawer;
};