#pragma once

#include <core/window.hpp>

#include <glm/glm.hpp>

#include <string>

class Camera
{
public:
	Camera(Window& window, const glm::vec3& position, const glm::vec3& direction,
			const glm::vec3& up, float fov, float near, float far, std::string name);
	glm::mat4 getView() const;
	glm::mat4 getProjection() const;

	const char* getName() const;

	void tick(float dt);

private:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_up;

	Window& m_window;
	std::string m_name;

	float m_fov;
	float m_near;
	float m_far;
};