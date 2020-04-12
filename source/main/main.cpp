#include <stdio.h>
#include <stdlib.h>
// �������� GLEW. ������ ��������� ��� �� gl.h � glfw.h
#include <GL/glew.h>
// �������� GLFW
#include <GLFW/glfw3.h>

// �������� GLM
#include <glm/glm.hpp>
using namespace glm;

int main() {

	// �������������� GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "������ ��� ������������� GLFWn");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x �����������
	glfwWindowHint(GLFW_VERSION_MAJOR, 3); // �� ����� ������������ OpenGL 3.3
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // �� �� ����� ������ OpenGL

	// ������� ���� � ������� � ��� �������� OpenGL
	GLFWwindow* window; // (� ���������������� �������� ���� ��� ���������� �������� ����������)
	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "���������� ������� ���� GLFW. ���� � ��� Intel GPU, �� �� �� ������������ ������ 3.3. ���������� ������ ������ ��� OpenGL 2.1.n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// �������������� GLEW
	glewExperimental = true; // ���� ��������� � Core-������ OpenGL
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "���������� ���������������� GLEWn");
		return -1;
	}

	// ������� ����� ������������ ������� ������, ��� �������� ����
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		// ���� ��� ������ �� �������. ��� ����� � ����� 2.

		// ���������� ������
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // ��������� ������� ������� Escape ��� �������� ����
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	system("pause");
	return 0;
}