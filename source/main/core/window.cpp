#include <main/core/window.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <iostream>

Signal<GLfloat, GLfloat> Window::windowSizeChanged;

Window::Window(WindowSettings settings)
	: m_windowSettings(settings)
{
	if (glfwInit())
	{
		std::cout << "GLFW is inited\n";
	}
	else
	{
		std::cout << "GLFW doesn't inited\n";
	}

	int major = 3;
	int minor = 3;
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(settings.width, settings.height, settings.title.c_str(), NULL, NULL);
	if (m_window)
	{
		std::cout << "Window is created\n";
	}
	else
	{
		std::cout << "Can't create window\n";
	}
	glfwMakeContextCurrent(m_window);

	bindKeyCallback();
	bindFrameBufferCallback();

	glewExperimental = GL_TRUE;

	if (glewInit() == GLEW_OK)
	{
		std::cout << "Glew is inited\n";
	}
	else
	{
		std::cout << "Glew doesn't inited\n";
	}

	m_context = ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init();

	glEnable(GL_DEPTH_TEST);

	windowSizeChanged.connect([this](GLfloat width, GLfloat height)
	{
		m_windowSettings.width = width;
		m_windowSettings.height = height;
	});
}

Window::~Window()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext(m_context);
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

WindowSettings Window::getWindowSettings() const
{
	return m_windowSettings;
}

bool Window::isKeyPressed(int key) const
{
	return glfwGetKey(m_window, key) == GLFW_PRESS;
}

void Window::bindKeyCallback()
{
	/*auto keyCallback = [](GLFWwindow*, int key, int, int action, int)
	{
		if (action == GLFW_PRESS)
		{
			keyPressSignal(key);
		}
	};

	glfwSetKeyCallback(m_window, keyCallback);*/
}

void Window::bindFrameBufferCallback()
{
	auto frameBufferSizeCallback = [](GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);

		windowSizeChanged(width, height);
	};

	glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);
}

