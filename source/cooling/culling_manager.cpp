#include <cooling/culling_manager.hpp>
#include <cooling/utils/visibility_tests.hpp>
#include <cooling/algorithms/basic_culling_algorithm.hpp>
#include <cooling/algorithms/regular_space_partitioning.hpp>

namespace Cooling
{
CullingManager::CullingManager()
{
}

void CullingManager::setSceneAABB(const AABB& sceneAABB)
{
	m_sceneAABB = sceneAABB;
}

UniqueIndex CullingManager::registerObject(const AABB& aabb)
{
	m_objects.push_back(std::make_shared<Object>(aabb));

	return m_objects.back()->getID();
}

bool CullingManager::isVisible(UniqueIndex index) const
{
	return m_objects[index]->isVisible();
}

Objects& CullingManager::objects()
{
	return m_objects;
}

void CullingManager::update()
{
	cleanupObjectsInfo();

	m_frustumView.updateFrustumView();

	if (m_algorithm)
	{
		m_algorithm->cullObjects(m_frustumView.getFrustumPlanes());
	}
}

void CullingManager::setViewProjectionMatrix(const glm::mat4& viewProjection)
{
	m_frustumView.setViewProjection(viewProjection);
}

void CullingManager::cleanupObjectsInfo()
{
	for (auto& object : m_objects)
	{
		object->setVisible(false);
	}
}

bool CullingManager::hasAlgorithm() const
{
	return m_algorithm.get() != nullptr;
}

void CullingManager::setAlgorithm(uint32_t algorithm)
{
	m_algorithmFilter = algorithm;

	if (m_algorithmFilter & None)
	{
		m_algorithm = nullptr;
		return;
	}

	if (m_algorithmFilter & Basic)
	{
		m_algorithm = std::make_unique<BasicCullingAlgorithm>();
	}

	if (m_algorithmFilter & AlRegularSpacePartitioning)
	{
		m_algorithm = std::make_unique<RegularSpacePartitioning>();
	}

	m_algorithm->init(m_objects, m_sceneAABB);
}

} // namespace Cooling