#pragma once

#include <core/window.hpp>

#include <core/shader/shader.hpp>

class Application
{
public:
	Application();

	void run();
private:
	Window m_window;
	Shader m_shader;
};