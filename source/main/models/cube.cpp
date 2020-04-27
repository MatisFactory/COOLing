#include <models/cube.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include <random>

namespace
{
	static constexpr size_t SIZE_TRIANGLE_VERTEX = 36;
	GLfloat vertices[] = 
	{
		 -1.f, -1.f, -1.f,
		 -1.f, 1.f, -1.f,
		 1.f, 1.f, -1.f,
		 1.f, -1.f, -1.f,
		 1.f, 1.f, 1.f,
		 1.f, -1.f, 1.f,
		 -1.f, 1.f, 1.f,
		 -1.f, -1.f, 1.f,
	};

	GLfloat color[] =
	{
		 1.f, 1.f, 1.f,
		 1.f, 1.f, 1.f,
		 1.f, 1.f, 1.f,
		 1.f, 1.f, 1.f,
		 1.f, 1.f, 1.f,
		 1.f, 1.f, 1.f,
		 1.f, 1.f, 1.f,
		 1.f, 1.f, 1.f,
	};

	GLuint indices[] =
	{
		0,1,2,
		0,3,2,
		3,2,4,
		3,5,4,
		6,4,5,
		6,7,5,
		1,6,7,
		1,0,7,
		0,7,5,
		0,3,5,
		1,6,4,
		1,2,4
	};
} // namespace

Cube::Cube(const glm::mat4& transform, GLuint programID)
	: m_transform(transform)
	, m_transformLocation(glGetUniformLocation(programID, "model"))
{
	regenerateColors();
	initOpenGLObjects();
}

Cube::~Cube()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}

void Cube::draw()
{
	glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(m_transform));
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Cube::initOpenGLObjects()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_colorVBO);
	glGenBuffers(1, &m_IBO);

	glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_colors), m_colors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Cube::regenerateColors()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<GLfloat> dis(0.0, 1.0);

	for (int i = 0; i < SIZE_TRIANGLE_VERTEX; i++)
	{
		m_colors[i] = dis(gen);
	}
}
