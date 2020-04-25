#pragma once

#include "window.hpp"

#include "shader/shader.hpp"

class Application
{
public:
	Application();

	void run();
private:
	Window m_window;
	Shader m_shader;
};