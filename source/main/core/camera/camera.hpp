#pragma once

#include <main/core/window.hpp>

#include <glm/glm.hpp>

#include <string>

class Camera
{
	friend class CameraDrawer;
public:
	Camera(Window& window, float fov, float near, float far, std::string name);
	
	glm::mat4 getView() const;
	glm::mat4 getProjection() const;

	const char* getName() const;

	float sensitivity() const;
	void setSensitivity(float value);

	float rotationSpeed() const;
	void setRotationSpeed(float value);

	void setFar(float value);

	void rotateYaw(float angle);
	void rotatePitch(float angle);

	void tick(float dt);
private:
	float getRatio() const;
	glm::vec3 getDirection() const;
private:
	glm::vec3 m_position;
	glm::vec3 m_up;

	Window& m_window;
	std::string m_name;

	float m_fov;
	float m_near;
	float m_far;

	// in degree
	float m_yaw;
	float m_pitch;

	float m_sensitivity;
	float m_rotationSpeed;
};