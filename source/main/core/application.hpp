#pragma once

#include <core/window.hpp>
#include <core/camera/camera_manager.hpp>
#include <core/clock/clock.hpp>
#include <core/shader/shader.hpp>
#include <models/cube.hpp>

#include <vector>

class Application
{
public:
	Application();

	void run();
private:
	void tick(float dt);
	void draw();
	void initModels();
	void setupViewProjection();

	void imguiNewFrame();
	void addToDrawImGui();
	void renderImGui();
private:
	Window m_window;
	Shader m_shader;
	Clock m_clock;

	CameraManager m_cameraManager;

	std::vector<Cube> m_cubes;
};