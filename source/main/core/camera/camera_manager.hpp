#pragma once

#include <main/core/camera/camera.hpp>
#include <main/core/window.hpp>

#include <string>
#include <list>
#include <memory>

using CameraPtr = std::shared_ptr<Camera>;
using CameraPack = std::vector<CameraPtr>;

class CameraManager
{
public:
	CameraManager(Window& window, uint32_t count = 1);
	
	Camera* getCurrentCamera() const;
	void setCurrentCamera(int index);
	int getCurrentCameraIndex() const;
	Camera* getFirstNotCurrentCamera() const;

	int size() const;
	CameraPack getCameraPack() const;

	bool rotateByYaw() const;
	void setRotateByYaw(bool value);

	void tick(float dt);

	void insertCamera();

	static glm::mat4 currentViewMatrix();
	static glm::mat4 currentProjectionMatrix();
private:
	Window& m_window;
	int m_currentCameraIndex;
	CameraPack m_cameraPack;
	
	CameraPtr m_currentCamera;
	std::string m_name;

	bool m_rotateByYaw = false;

	static glm::mat4 s_viewMatrixMainCamera;
	static glm::mat4 s_projectionMatrixMainCamera;
};