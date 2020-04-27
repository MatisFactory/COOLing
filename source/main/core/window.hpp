#pragma once

#include <gl/glew.h>
#include <glfw/glfw3.h>

#include <core/settings/window_settings.hpp>
#include <core/signal/signal.hpp>

class Window
{
public:
	// TODO: remove this
	static Signal<GLfloat, GLfloat> windowSizeChanged;
public:
	Window(WindowSettings settings = {});
	~Window();

	bool windowShouldClose();
	
	GLFWwindow* getGLFWwindow();
	WindowSettings getWindowSettings() const;

	bool isKeyPressed(int key) const;
private:
	void bindKeyCallback();
	void bindFrameBufferCallback();
private:
	GLFWwindow* m_window;
	WindowSettings m_windowSettings;
};