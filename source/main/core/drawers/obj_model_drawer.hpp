#pragma once

#include <main/core/shader/shader.hpp>
#include <main/models/obj_model.hpp>

#include <glm/glm.hpp>

#include <vector>

class ObjModelDrawer
{
public:
	ObjModelDrawer();
	ObjModelDrawer(const ObjModel& model);
	
	void activateShader(Shader& m_shader);
	void draw(const glm::mat4& transforms);
private:
	void loadOpenGLObjects();
private:
	ObjModel m_model;

	std::vector<glm::vec3> m_vertices;

	GLint m_transformLocation;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
};