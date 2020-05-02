#include <main/core/camera/camera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace
{
	static constexpr float CAMERA_SPEED = 0.05f;
	static constexpr float DELTA = 0.05f;
} // namespace

Camera::Camera(Window& window, const glm::vec3& position, const glm::vec3& direction,
	const glm::vec3& up, float fov, float near, float far, std::string name)
	: m_window(window)
	, m_position(position)
	, m_direction(glm::normalize(direction))
	, m_up(glm::normalize(up))
	, m_fov(glm::radians(fov))
	, m_near(near)
	, m_far(far)
	, m_name(name)
{
}

glm::mat4 Camera::getView() const
{
	return glm::lookAt(m_position, m_position + m_direction, m_up);
}

glm::mat4 Camera::getProjection() const
{
	return glm::perspective(m_fov, getRatio(), m_near, m_far);
}

float Camera::getRatio() const
{
	return m_window.getWindowSettings().width / m_window.getWindowSettings().height;
}

const char* Camera::getName() const
{
	return m_name.c_str();
}

void Camera::tick(float dt)
{
	if (m_window.isKeyPressed(GLFW_KEY_W))
	{
		m_position += dt * CAMERA_SPEED * m_direction;
	}
	if (m_window.isKeyPressed(GLFW_KEY_S))
	{
		m_position -= dt * CAMERA_SPEED * m_direction;
	}
	if (m_window.isKeyPressed(GLFW_KEY_A))
	{
		m_position -= dt * CAMERA_SPEED * glm::cross(m_direction, m_up);
	}
	if (m_window.isKeyPressed(GLFW_KEY_D))
	{
		m_position += dt * CAMERA_SPEED * glm::cross(m_direction, m_up);
	}

	if (m_window.isKeyPressed(GLFW_KEY_LEFT))
	{
		glm::mat4 trans = glm::mat4(1.f);
		trans = glm::rotate(trans, glm::radians(-DELTA * dt), glm::vec3(0.0f, 1.f, 0.0f));
		m_direction = glm::vec4(m_direction, 1.f) * trans;
	}

	if (m_window.isKeyPressed(GLFW_KEY_RIGHT))
	{
		glm::mat4 trans = glm::mat4(1.f);
		trans = glm::rotate(trans, glm::radians(DELTA * dt), glm::vec3(0.0f, 1.f, 0.0f));
		m_direction = glm::vec4(m_direction, 1.f) * trans;
	}
}