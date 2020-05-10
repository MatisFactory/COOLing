#include <main/core/drawers/obj_model_drawer.hpp>
#include <main/core/camera/camera_manager.hpp>
#include <main/core/culling_wrapper.hpp>
#include <main/third_party/OBJ_Loader.h>


#include <glm/gtc/type_ptr.hpp>

ObjModelDrawer::ObjModelDrawer(const ObjModel& model)
	: m_model(model)
{
	loadOpenGLObjects();
}

ObjModelDrawer::ObjModelDrawer()
	: m_model("")
{
}

void ObjModelDrawer::activateShader(Shader& shader)
{
	shader.use();

	m_transformLocation = glGetUniformLocation(shader.ID, "model");
	GLint viewLoc = glGetUniformLocation(shader.ID, "view");
	GLint projLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(CameraManager::currentViewMatrix()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(CameraManager::currentProjectionMatrix()));
}

void ObjModelDrawer::draw(const glm::mat4& transform)
{
	glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}


void ObjModelDrawer::loadOpenGLObjects()
{
	m_vertices = m_model.getVertices();

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
}