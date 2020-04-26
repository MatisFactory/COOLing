#include <core/application.hpp>
#include <models/cube.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cassert>

Application::Application()
	: m_shader("../../../shaders/VertexShader.txt", "../../../shaders/FragmentShader.txt")
{
}

void Application::run()
{
	Cube cube(glm::mat4(1.f));

	while (!m_window.windowShouldClose())
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_shader.use();

		WindowSettings settings = m_window.getWindowSettings();

		// Create transformations
		glm::mat4 model = glm::mat4(1.f);
		glm::mat4 view = glm::mat4(1.f);
		glm::mat4 projection = glm::mat4(1.f);
		view = glm::lookAt(glm::vec3(5.f, 6.f, 8.f), glm::vec3(0.f, 0.f, 0.f),glm::vec3(0.f, 1.f, 0.f));
		projection = glm::perspective(45.0f, (GLfloat)settings.width / (GLfloat)settings.height, 0.1f, 100.0f);

		GLint modelLoc = glGetUniformLocation(m_shader.ID, "model");
		GLint viewLoc = glGetUniformLocation(m_shader.ID, "view");
		GLint projLoc = glGetUniformLocation(m_shader.ID, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		cube.draw();

		glfwSwapBuffers(m_window.getGLFWwindow());
	}
}
