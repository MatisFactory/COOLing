#pragma once

#include <main/core/shader/shader.hpp>

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <memory>

namespace objl
{
class Loader;
}

class ObjModelDrawer
{
public:
	ObjModelDrawer(const std::string& fileName);
	~ObjModelDrawer();
	void draw();
private:
	void normalizeTransform();
	void loadOpenGLObjects();
	void setupViewProjection();
private:
	std::string m_fileName;
	std::vector<glm::vec3> m_vertices;
	
	Shader m_shader;
	std::unique_ptr<objl::Loader> m_loader;

	glm::mat4 m_transform;

	GLint m_transformLocation;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
};