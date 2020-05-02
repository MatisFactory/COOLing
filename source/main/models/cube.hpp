#include <main/core/shader/shader.hpp>

#include <glm/glm.hpp>

class Cube
{
public:
	Cube(const glm::mat4& transform);
	~Cube();
	void draw();
private:
	void initOpenGLObjects();
	void regenerateColors();
	void setupViewProjection();
private:
	Shader m_shader;

	glm::mat4 m_transform;

	GLfloat m_colors[36];
	GLint m_transformLocation;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
	GLuint m_colorVBO;
};