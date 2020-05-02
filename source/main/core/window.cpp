#include <core/window.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


#include <cassert>

Signal<GLfloat, GLfloat> Window::windowSizeChanged;

Window::Window(WindowSettings settings)
	: m_windowSettings(settings)
{
	assert(glfwInit());

	int major = 3;
	int minor = 3;
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(settings.width, settings.height, settings.title.c_str(), NULL, NULL);
	assert(m_window);
	glfwMakeContextCurrent(m_window);

	bindKeyCallback();
	bindFrameBufferCallback();

	glewExperimental = GL_TRUE;
	assert(glewInit() == GLEW_OK);

	m_context = ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO();

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

