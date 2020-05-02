#include <cooling/culling_manager.hpp>
#include <cooling/utils/visibility_tests.hpp>

namespace Cooling
{
CullingManager::CullingManager()
{
}

Object CullingManager::registerObject(const AABB& aabb)
{
	m_objects.emplace_back(aabb);
	m_isVisibleObject.push_back(false);

	return m_objects.back();
}

bool CullingManager::isVisible(UniqueIndex index) const
{
	return m_isVisibleObject[index];
}

bool CullingManager::isVisible(Object object) const
{
	return isVisible(object.getID());
}

void CullingManager::update()
{
	cleanupObjectsInfo();

	m_frustumView.updateFrustumView();

	for (auto& object : m_objects)
	{
		if (isAABBVisible(m_frustumView.getFrustumPlanes(), object.getAABB()))
		{
			m_isVisibleObject[object.getID()] = true;
		}
	}
}

void CullingManager::setViewProjectionMatrix(const glm::mat4& viewProjection)
{
	m_frustumView.setViewProjection(viewProjection);
}

void CullingManager::cleanupObjectsInfo()
{
	for (auto& isVisible : m_isVisibleObject)
	{
		isVisible = false;
	}
}

} // namespace Cooling