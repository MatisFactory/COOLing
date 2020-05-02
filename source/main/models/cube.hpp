#include <main/core/shader/shader.hpp>

#include <glm/glm.hpp>

class Cube
{
public:
	Cube(const glm::mat4& transform);
	~Cube();

	void draw();

	glm::mat4 worldTransform() const;
private:
	void initOpenGLObjects();
	void regenerateColors();
private:
	glm::mat4 m_transform;

	GLfloat m_colors[36];
	
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
	GLuint m_colorVBO;
};