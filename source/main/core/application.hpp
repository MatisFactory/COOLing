#pragma once

#include <main/core/window.hpp>
#include <main/core/camera/camera_manager.hpp>
#include <main/core/clock/clock.hpp>
#include <main/core/shader/shader.hpp>
#include <main/models/cube_manager.hpp>
#include <main/core/drawers/camera_drawer.hpp>
#include <main/core/drawers/obj_model_drawer.hpp>

class ObjModelDrawer;

class Application
{
public:
	Application();

	void run();
private:
	void tick(float dt);
	
	void preUpdate();
	void update();
	void postUpdate();

	void tickCameraManager(float dt);
	void tickCullingManager(float dt);
	
	void draw();

	void imguiNewFrame();
	void addToDrawImGui();
	void drawImGui();
private:
	Window m_window;
	Clock m_clock;

	ObjModelDrawer m_objDrawer;
	CubeManager m_cubeManager;

	CameraManager m_cameraManager;
	CameraDrawer m_cameraDrawer;
};