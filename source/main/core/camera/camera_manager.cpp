#include <main/core/camera/camera_manager.hpp>

#include <cassert>

namespace
{
	static const std::string CAMERA_NAME;
	constexpr float DEFAULT_FAR = 500.f;
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

	setCurrentCamera(m_currentCameraIndex);
}

Camera* CameraManager::getCurrentCamera() const
{
	return m_cameraPack[m_currentCameraIndex].get();
}

int CameraManager::getCurrentCameraIndex() const
{
	return m_currentCameraIndex;
}

void CameraManager::setCurrentCamera(int index)
{
	m_cameraPack[m_currentCameraIndex]->setFar(DEFAULT_FAR);
	m_currentCameraIndex = index;
	m_cameraPack[m_currentCameraIndex]->setFar(MAIN_CAMERA_FAR);
}

Camera* CameraManager::getFirstNotCurrentCamera() const
{
	for (const auto& camera : m_cameraPack)
	{
		if (camera.get() != getCurrentCamera())
		{
			return camera.get();
		}
	}

	return nullptr;
}

int CameraManager::size() const
{
	return m_cameraPack.size();
}

CameraPack CameraManager::getCameraPack() const
{
	return m_cameraPack;
}

bool CameraManager::rotateByYaw() const
{
	return m_rotateByYaw;
}

void CameraManager::setRotateByYaw(bool value)
{
	m_rotateByYaw = value;
}

void CameraManager::tick(float dt)
{	
	getCurrentCamera()->tick(dt);
	s_viewMatrixMainCamera = getCurrentCamera()->getView();
	s_projectionMatrixMainCamera = getCurrentCamera()->getProjection();

	if (m_rotateByYaw)
	{
		if (Camera* notCurrentCamera = getFirstNotCurrentCamera())
		{
			notCurrentCamera->rotateYaw(dt* notCurrentCamera->sensitivity());
		}
	}
}

void CameraManager::insertCamera()
{
	m_cameraPack.push_back(std::make_shared<Camera>(CAMERA_PARAMS(m_cameraPack.size())));
}

glm::mat4 CameraManager::currentViewMatrix()
{
	return s_viewMatrixMainCamera;
}

glm::mat4 CameraManager::currentProjectionMatrix()
{
	return s_projectionMatrixMainCamera;
}

