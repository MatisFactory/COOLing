#pragma once

#include <gl/glew.h>
#include <glfw/glfw3.h>

#include "settings/window_settings.hpp"

class Window
{
public:
	Window(WindowSettings settings = {});
	~Window();

	bool windowShouldClose();
	GLFWwindow* getGLFWwindow();
private:
	GLFWwindow* m_window = nullptr;
	WindowSettings m_settings;
};