#include <main/core/camera/camera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace
{
	constexpr float CAMERA_SPEED = 0.05f;
	constexpr float DELTA = 0.05f;
	constexpr glm::vec3 DEFAULT_POSITION = glm::vec3(5.f, 0.f, 0.f);
	constexpr glm::vec3 DEFAULT_TARGET = glm::vec3(0.f,0.f,0.f);
	constexpr glm::vec3 DEFAULT_UP = glm::vec3(0.f, 1.f, 0.f);

	int sign(float value)
	{
		return value > 0 ? 1 : -1;
	}

	float normalizeDegree(float degree)
	{
		float n = abs(degree/360.f);
		if (n > 1.f)
		{
			degree = sign(degree) * (abs(degree) - static_cast<int>(n) * abs(360.f));
		}

		if (degree < 0.f)
		{
			return degree + 360.f;
		}

		return degree;
	}
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

void Camera::setFov(float value)
{
	m_fov = value;
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

const char* Camera::getName() const
{
	return m_name.c_str();
}

void Camera::tick(float dt)
{
	if (m_window.isKeyPressed(GLFW_KEY_W))
	{
		m_position += dt * CAMERA_SPEED * getDirection();
	}
	if (m_window.isKeyPressed(GLFW_KEY_S))
	{
		m_position -= dt * CAMERA_SPEED * getDirection();
	}
	if (m_window.isKeyPressed(GLFW_KEY_A))
	{
		m_position -= dt * CAMERA_SPEED * glm::cross(getDirection(), m_up);
	}
	if (m_window.isKeyPressed(GLFW_KEY_D))
	{
		m_position += dt * CAMERA_SPEED * glm::cross(getDirection(), m_up);
	}

	if (m_window.isKeyPressed(GLFW_KEY_LEFT))
	{
		m_yaw -= CAMERA_SPEED * dt;
	}

	if (m_window.isKeyPressed(GLFW_KEY_RIGHT))
	{
		m_yaw += CAMERA_SPEED * dt;
	}

	if (m_window.isKeyPressed(GLFW_KEY_UP))
	{
		m_pitch -= CAMERA_SPEED * dt;
	}

	if (m_window.isKeyPressed(GLFW_KEY_DOWN))
	{
		m_pitch += CAMERA_SPEED * dt;
	}

	m_pitch = normalizeDegree(m_pitch);
	m_yaw = normalizeDegree(m_yaw);
}