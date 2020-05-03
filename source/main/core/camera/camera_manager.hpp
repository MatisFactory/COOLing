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
	
	Camera* getMainCamera() const;
	void setMainCamera(int index);
	int getMainCameraIndex() const;

	int size() const;
	CameraPack getCameraPack() const;

	Camera* getFirstNotMainCamera() const;

	void tick(float dt);
	void insertCamera();

	static glm::mat4 mainViewMatrix();
	static glm::mat4 mainProjectionMatrix();
private:
	Window& m_window;
	int m_currentCameraIndex;
	CameraPack m_cameraPack;
	
	CameraPtr m_mainCamera;
	std::string m_name;

	static glm::mat4 s_viewMatrixMainCamera;
	static glm::mat4 s_projectionMatrixMainCamera;

	bool m_rotateByYaw = false;
};