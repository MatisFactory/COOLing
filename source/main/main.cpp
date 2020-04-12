#include <stdio.h>
#include <stdlib.h>
// Включаем GLEW. Всегда включайте его ДО gl.h и glfw.h
#include <GL/glew.h>
// Включаем GLFW
#include <GLFW/glfw3.h>

// Включаем GLM
#include <glm/glm.hpp>
using namespace glm;

int main() {

	GLFWwindow* window = NULL;

	// initialize the GLFW library
	if (!glfwInit()) {
		return -1;
	}

	// setting the opengl version
	int major = 3;
	int minor = 3;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create the window
	window = glfwCreateWindow(1024, 768, "oops", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Инициализируем GLEW
	glewExperimental = true; // Флаг необходим в Core-режиме OpenGL
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Невозможно инициализировать GLEWn");
		return -1;
	}

	// Включим режим отслеживания нажатия клавиш, для проверки ниже
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		// Пока что ничего не выводим. Это будет в уроке 2.

		// Сбрасываем буферы
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Проверяем нажатие клавиши Escape или закрытие окна
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	system("pause");
	return 0;
}