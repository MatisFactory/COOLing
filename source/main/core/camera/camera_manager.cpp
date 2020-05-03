#include <main/core/camera/camera_manager.hpp>

#include <cassert>

namespace
{
	static const std::string CAMERA_NAME;
	constexpr float DEFAULT_FAR = 200.f;
	constexpr float MAIN_CAMERA_FAR = DEFAULT_FAR * 5;
}

#define CAMERA_PARAMS(id) m_window, 60.f, 0.1f, DEFAULT_FAR, "Camera " + std::to_string(id + 1)

glm::mat4 CameraManager::s_viewMatrixMainCamera;
glm::mat4 CameraManager::s_projectionMatrixMainCamera;

CameraManager::CameraManager(Window& window, uint32_t count)
	: m_window(window)
	, m_currentCameraIndex(0)
{
	m_cameraPack.reserve(count);
	
	for (int i = 0; i < count; i++)
	{
		m_cameraPack.push_back(std::make_shared<Camera>(CAMERA_PARAMS(i)));
	}

	m_mainCamera = m_cameraPack[m_currentCameraIndex];
	m_mainCamera->setFar(MAIN_CAMERA_FAR);
}

Camera* CameraManager::getMainCamera() const
{
	return m_cameraPack[m_currentCameraIndex].get();
}

int CameraManager::getMainCameraIndex() const
{
	return m_currentCameraIndex;
}

int CameraManager::size() const
{
	return m_cameraPack.size();
}

void CameraManager::setMainCamera(int index)
{
	m_cameraPack[m_currentCameraIndex]->setFar(DEFAULT_FAR);
	m_currentCameraIndex = index;
	m_cameraPack[m_currentCameraIndex]->setFar(MAIN_CAMERA_FAR);
}

CameraPack CameraManager::getCameraPack() const
{
	return m_cameraPack;
}

Camera* CameraManager::getFirstNotMainCamera() const
{
	for (const auto& camera : m_cameraPack)
	{
		if (camera.get() != getMainCamera())
		{
			return camera.get();
		}
	}

	return nullptr;
}

glm::mat4 CameraManager::mainViewMatrix()
{
	return s_viewMatrixMainCamera;
}

glm::mat4 CameraManager::mainProjectionMatrix()
{
	return s_projectionMatrixMainCamera;
}

void CameraManager::tick(float dt)
{	
	getMainCamera()->tick(dt);
	s_viewMatrixMainCamera = getMainCamera()->getView();
	s_projectionMatrixMainCamera = getMainCamera()->getProjection();
}

void CameraManager::insertCamera()
{
	m_cameraPack.push_back(std::make_shared<Camera>(CAMERA_PARAMS(m_cameraPack.size())));
}
