#include <main/models/cube.hpp>
#include <main/core/camera/camera_manager.hpp>

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <random>

namespace
{
	constexpr size_t COUNT_VERTEX_PART = 12*3;
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

Cube::Cube(const glm::mat4& transform)
	: m_transform(transform)
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
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, COUNT_VERTEX_PART, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

std::vector<glm::vec3> Cube::getVertices() const
{
	std::vector<glm::vec3> result;
	for (int i = 0; i < 8; i++)
	{
		glm::vec4 v = glm::vec4(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2], 1);
		result.push_back(m_transform*v);
	}

	return result;
}

glm::mat4 Cube::worldTransform() const
{
	return m_transform;
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

	for (int i = 0; i < COUNT_VERTEX_PART; i++)
	{
		m_colors[i] = dis(gen);
	}
}