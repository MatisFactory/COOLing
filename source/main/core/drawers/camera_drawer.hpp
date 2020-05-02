#pragma once

#include <main/core/camera/camera.hpp>
#include <main/core/shader/shader.hpp>

#include <glm/glm.hpp>

#include <optional>

namespace
{
	constexpr uint32_t COUNT_UNIQUE_VERTEX_PART = 24;
}

class CameraDrawer
{
public:
	CameraDrawer(Camera* camera = nullptr);
	~CameraDrawer();
	void setCameraToDraw(Camera* camera);

	void draw();
private:
	void constructModel();
	void setupViewProjection();
	void initOpenGlObjects();
private:
	Shader m_shader;
	Camera* m_camera;
	GLfloat m_verticies[COUNT_UNIQUE_VERTEX_PART];

	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
};