#pragma once

#include <core/camera/camera.hpp>
#include <core/window.hpp>

#include <string>
#include <list>
#include <memory>

using CameraPtr = std::shared_ptr<Camera>;
using CameraPack = std::vector<CameraPtr>;

class CameraManager
{
public:
	CameraManager(Window& window, uint32_t count = 1);
	Camera* getMainCamera();
	void setMainCamera(int index);

	int getMainCameraIndex() const;
	int count() const;
	CameraPack getCameraPack() const;
	

	void tick(float dt);
	void insertCamera();
private:
	Window& m_window;
	int m_currentCameraIndex;
	CameraPack m_cameraPack;
	
	CameraPtr m_mainCamera;
	std::string m_name;
};