#include <glm/glm.hpp>
#include <gl/glew.h>

class Cube
{
public:
	Cube(const glm::mat4& transform, GLuint programID);
	~Cube();
	void draw();
private:
	void initOpenGLObjects();
	void regenerateColors();
private:
	glm::mat4 m_transform;
	GLfloat m_colors[36];
	GLint m_transformLocation;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
	GLuint m_colorVBO;
};