#include <core/window.hpp>

#include <cassert>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

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
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	assert(glewInit() == GLEW_OK);

	glEnable(GL_DEPTH_TEST);
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::windowShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

GLFWwindow* Window::getGLFWwindow() const
{
	return m_window;
}

WindowSettings Window::getWindowSettings() const
{
	return m_settings;
}

