#include <main/core/drawers/camera_drawer.hpp>
#include <main/core/camera/camera_manager.hpp>

#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace
{
	GLuint indices[] =
	{
		0,1,2,
		0,3,2,
		3,2,6,
		3,7,6,
		7,6,5,
		5,4,7,
		5,4,0,
		5,1,0,
		0,4,7,
		0,3,7,
		1,5,6,
		1,2,6
	};

	constexpr uint32_t COUNT_VERTEX_PART = 36;
	constexpr uint32_t COUNT_UNIQUE_VERTEX = 8;
} // namespace

CameraDrawer::CameraDrawer(Camera* camera)
	: m_camera(camera)
	, m_shader("../../../shaders/camera.vertexShader", "../../../shaders/camera.fragmentShader")
{
}

CameraDrawer::~CameraDrawer()
{
}

void CameraDrawer::setCameraToDraw(Camera* camera)
{
	m_camera = camera;
	initOpenGlObjects();
}


void CameraDrawer::draw()
{
	if (!m_camera)
	{
		return;
	}

	m_shader.use();

	setupViewProjection();
	constructModel();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, COUNT_VERTEX_PART, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CameraDrawer::constructModel()
{
	if(m_camera)
	{
		float near = m_camera->m_near;
		float far = m_camera->m_far;

		float heightNearPlane = m_camera->m_near * glm::tan(m_camera->m_fov/2) * 2;
		float widthNearPlane = heightNearPlane * m_camera->getRatio();

		float heightFarPlane = far * glm::tan(m_camera->m_fov / 2) * 2;
		float widthFarPlane = heightFarPlane * m_camera->getRatio();

		glm::vec3 right = glm::normalize(glm::cross(m_camera->getDirection(), m_camera->m_up));
		glm::vec3 position = m_camera->m_position;
		glm::vec3 direction = m_camera->getDirection();
		glm::vec3 up = m_camera->m_up;
		
		glm::vec3 verticies[COUNT_UNIQUE_VERTEX];

		verticies[0] = position + direction * near - right * widthNearPlane / 2.f - up * heightNearPlane / 2.f;
		verticies[1] = position + direction * near - right * widthNearPlane / 2.f + up * heightNearPlane / 2.f;
		verticies[2] = position + direction * near + right * widthNearPlane / 2.f + up * heightNearPlane / 2.f;
		verticies[3] = position + direction * near + right * widthNearPlane / 2.f - up * heightNearPlane / 2.f;

		verticies[4] = position + direction * far - right * widthFarPlane / 2.f - up * heightFarPlane / 2.f;
		verticies[5] = position + direction * far - right * widthFarPlane / 2.f + up * heightFarPlane / 2.f;
		verticies[6] = position + direction * far + right * widthFarPlane / 2.f + up * heightFarPlane / 2.f;
		verticies[7] = position + direction * far + right * widthFarPlane / 2.f - up * heightFarPlane / 2.f;

		for (int i = 0; i < COUNT_UNIQUE_VERTEX_PART; i++)
		{
			m_verticies[i] = verticies[i/3][i%3];
		}
	}
}

void CameraDrawer::setupViewProjection()
{
	GLint viewLoc = glGetUniformLocation(m_shader.ID, "view");
	GLint projLoc = glGetUniformLocation(m_shader.ID, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(CameraManager::currentViewMatrix()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(CameraManager::currentProjectionMatrix()));
}

void CameraDrawer::initOpenGlObjects()
{
	deleteOpenGlObjects();

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_verticies), m_verticies, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void CameraDrawer::deleteOpenGlObjects()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}
