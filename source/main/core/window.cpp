#include "window.hpp"

#include <cassert>

Window::Window(WindowSettings settings /*= {}*/)
	: m_settings(settings)
{
	// initialize the GLFW library
	assert(glfwInit());

	// setting the opengl version
	int major = 3;
	int minor = 3;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(settings.width, settings.height, settings.title.c_str(), NULL, NULL);
	assert(m_window);
	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	assert(glewInit() == GLEW_OK);
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::windowShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

GLFWwindow* Window::getGLFWwindow()
{
	return m_window;
}

