#include "application.hpp"

#include <cassert>

Application::Application()
{
}

void Application::run()
{
	while (!m_window.windowShouldClose())
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window.getGLFWwindow());
	}
}
