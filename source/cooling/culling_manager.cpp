#include <cooling/culling_manager.hpp>
#include <cooling/utils/visibility_tests.hpp>
#include <cooling/algorithms/basic_culling_algorithm.hpp>
#include <cooling/algorithms/bounding_volume_hierarchy.hpp>
#include <cooling/algorithms/octree.hpp>
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

UniqueIndex CullingManager::registerObject(const AABB& aabb, bool hardToDraw)
{
	m_objects.push_back(std::make_shared<Object>(aabb, hardToDraw));

	return m_objects.back()->getID();
}

bool CullingManager::isVisible(UniqueIndex index) const
{
	if(m_isEnabled)
	{
		return m_objects[index]->isVisible();
	}

	return true;
}

Objects& CullingManager::objects()
{
	return m_objects;
}

void CullingManager::update()
{
	if (!m_isEnabled)
	{
		return;
	}

	cleanupObjectsInfo();

	m_frustumView.updateFrustumView();

	if (m_algorithm)
	{
		m_algorithm->cullObjects(m_frustumView.getFrustumPlanes());
	}

	if (m_occlusionQueryEnabled)
	{
		m_queriesManager->applyResult();
	}
}

void CullingManager::runOcclusionQueryTasks()
{
	if (m_occlusionQueryEnabled)
	{
		m_queriesManager->runQueries();
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
		object->setIsInFrustumView(false);
		object->setOccludedResult(std::nullopt);
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
	else if (m_algorithmFilter & Basic)
	{
		m_algorithm = std::make_unique<BasicCullingAlgorithm>();
	}
	else if (m_algorithmFilter & AlRegularSpacePartitioning)
	{
		m_algorithm = std::make_unique<RegularSpacePartitioning>();
	}
	else if (m_algorithmFilter & OctreeCulling)
	{
		m_algorithm = std::make_unique<Octree>();
	}
	else if (m_algorithmFilter & BVH)
	{
		m_algorithm = std::make_unique<BoundingVolumeHierarchy>();
	}

	m_algorithm->init(m_objects, m_sceneAABB);
}

bool CullingManager::isEnabled() const
{
	return m_isEnabled;
}

void CullingManager::setEnabled(bool value)
{
	m_isEnabled = value;
}

bool CullingManager::occlusionQueryEnabled() const
{
	return m_occlusionQueryEnabled;
}

void CullingManager::setOcclusionQueryEnabled(bool value)
{
	m_occlusionQueryEnabled = value;
}

void CullingManager::setupQueriesManager(std::function<void(AABB)> drawedFunction)
{
	m_queriesManager = std::make_unique<QueriesManager>(std::move(drawedFunction), m_objects);
}

} // namespace Cooling