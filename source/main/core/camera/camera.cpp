#include <main/core/camera/camera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace
{
	constexpr float CAMERA_SENSITIVITY = 0.01f;
	constexpr float ROTATION_SPEED = 0.08f;
	constexpr glm::vec3 DEFAULT_POSITION = glm::vec3(5.f, 0.f, 0.f);
	constexpr glm::vec3 DEFAULT_TARGET = glm::vec3(0.f,0.f,0.f);
	constexpr glm::vec3 DEFAULT_UP = glm::vec3(0.f, 1.f, 0.f);
} // namespace

Camera::Camera(Window& window, float fov, float near, float far, std::string name)
	: m_window(window)
	, m_position(DEFAULT_POSITION)
	, m_up(DEFAULT_UP)
	, m_fov(glm::radians(fov))
	, m_near(near)
	, m_far(far)
	, m_name(name)
	, m_yaw(0.f)
	, m_pitch(90.f)
	, m_sensitivity(CAMERA_SENSITIVITY)
	, m_rotationSpeed(ROTATION_SPEED)
{
}

glm::mat4 Camera::getView() const
{
	return glm::lookAt(m_position, m_position + getDirection(), m_up);
}

glm::mat4 Camera::getProjection() const
{
	return glm::perspective(m_fov, getRatio(), m_near, m_far);
}

const char* Camera::getName() const
{
	return m_name.c_str();
}

float Camera::sensitivity() const
{
	return m_sensitivity;
}

void Camera::setSensitivity(float value)
{
	m_sensitivity = value;
}

float Camera::rotationSpeed() const
{
	return m_rotationSpeed;
}

void Camera::setRotationSpeed(float value)
{
	m_rotationSpeed = value;
}

void Camera::setFar(float value)
{
	m_far = value;
}

void Camera::rotateYaw(float angle)
{
	m_yaw += angle;
}

void Camera::rotatePitch(float angle)
{
	m_pitch += angle;
}

float Camera::getRatio() const
{
	return m_window.getWindowSettings().width / m_window.getWindowSettings().height;
}

glm::vec3 Camera::getDirection() const
{
	glm::vec3 direction;
	direction.x = glm::sin(glm::radians(m_pitch)) * glm::cos(glm::radians(m_yaw));
	direction.y = glm::cos(glm::radians(m_pitch));
	direction.z = glm::sin(glm::radians(m_pitch)) * glm::sin(glm::radians(m_yaw));
	return direction;
}

void Camera::tick(float dt)
{
	if (m_window.isKeyPressed(GLFW_KEY_W))
	{
		m_position += dt * m_sensitivity * getDirection();
	}
	if (m_window.isKeyPressed(GLFW_KEY_S))
	{
		m_position -= dt * m_sensitivity * getDirection();
	}
	if (m_window.isKeyPressed(GLFW_KEY_A))
	{
		m_position -= dt * m_sensitivity * glm::cross(getDirection(), m_up);
	}
	if (m_window.isKeyPressed(GLFW_KEY_D))
	{
		m_position += dt * m_sensitivity * glm::cross(getDirection(), m_up);
	}

	if (m_window.isKeyPressed(GLFW_KEY_LEFT))
	{
		m_yaw -= m_rotationSpeed * dt;
	}

	if (m_window.isKeyPressed(GLFW_KEY_RIGHT))
	{
		m_yaw += m_rotationSpeed * dt;
	}

	if (m_window.isKeyPressed(GLFW_KEY_UP))
	{
		m_pitch -= m_rotationSpeed * dt;
	}

	if (m_window.isKeyPressed(GLFW_KEY_DOWN))
	{
		m_pitch += m_rotationSpeed * dt;
	}

	m_pitch = m_pitch;
	m_yaw = m_yaw;
}