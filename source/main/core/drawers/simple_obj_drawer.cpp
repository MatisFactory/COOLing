#include <main/core/drawers/obj_model_drawer.hpp>
#include <main/core/camera/camera_manager.hpp>
#include <main/third_party/OBJ_Loader.h>

#include <glm/gtc/type_ptr.hpp>

ObjModelDrawer::ObjModelDrawer(const std::string& fileName)
     : m_fileName(fileName)
     , m_shader("../../../shaders/SimpleObj.vertexShader", "../../../shaders/SimpleObj.fragmentShader")
	 , m_transformLocation(glGetUniformLocation(m_shader.ID, "model"))
	 , m_transform(glm::mat4(1.f))
{
	m_loader = std::make_unique<objl::Loader>();
	m_loader->LoadFile(m_fileName);
	loadOpenGLObjects();
	normalizeTransform();
}

ObjModelDrawer::~ObjModelDrawer()
{

}

void ObjModelDrawer::draw()
{
	
	m_shader.use();
	setupViewProjection();
	
	glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, glm::value_ptr(m_transform));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size() / 3);
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ObjModelDrawer::normalizeTransform()
{
	float max = 0;

	for (const auto& value : m_vertices)
	{
		if (abs(value) > max)
		{
			max = abs(value);
		}
	}

	float newScale = 1.f/max;

	m_transform = glm::scale(m_transform, glm::vec3(newScale, newScale, newScale));
}

void ObjModelDrawer::loadOpenGLObjects()
{
	m_vertices.reserve(m_loader->LoadedVertices.size());

	for (const auto& vertex : m_loader->LoadedVertices)
	{
		m_vertices.push_back(vertex.Position.X);
		m_vertices.push_back(vertex.Position.Y);
		m_vertices.push_back(vertex.Position.Z);
	}

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
}

void ObjModelDrawer::setupViewProjection()
{
	GLint viewLoc = glGetUniformLocation(m_shader.ID, "view");
	GLint projLoc = glGetUniformLocation(m_shader.ID, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(CameraManager::currentViewMatrix()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(CameraManager::currentProjectionMatrix()));
}