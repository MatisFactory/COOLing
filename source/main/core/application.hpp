#pragma once

#include <core/window.hpp>
#include <core/camera/camera.hpp>
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
private:
	Window m_window;
	Camera m_camera;
	Shader m_shader;

	std::vector<Cube> m_cubes;
};