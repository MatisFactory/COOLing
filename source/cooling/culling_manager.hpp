#pragma once

#include <cooling/export/cooling_dll.hpp>

#include <cooling/object.hpp>
#include <cooling/frustum_view.hpp>
#include <cooling/algorithms/algorithm.hpp>
#include <cooling/occlusion_query/queries_manager.hpp>

#include <glm/glm.hpp>

#include <functional>
#include <memory>

namespace Cooling
{
enum AlgoritmFilter : uint32_t
{
	None = 1 << 0,
	Basic = 1 << 1,
	AlRegularSpacePartitioning = 1 << 2,
	OctreeCulling = 1 << 3,
};

class COOLING_DLL CullingManager
{
public:
	CullingManager();
	
	void setSceneAABB(const AABB& sceneAABB);

	[[nodiscard]] UniqueIndex registerObject(const AABB& aabb, bool hardToDraw = false);
	void setViewProjectionMatrix(const glm::mat4& viewProjection);
	bool isVisible(UniqueIndex index) const;

	Objects& objects();

	void update();
	void runOcclusionQueryTasks();

	void cleanupObjectsInfo();

	bool hasAlgorithm() const;
	void setAlgorithm(uint32_t algorithm);

	bool isEnabled() const;
	void setEnabled(bool value);

	bool occlusionQueryEnabled() const;
	void setOcclusionQueryEnabled(bool value);

	void setupQueriesManager(std::function<void(AABB)> drawedFunction);
private:
	Objects m_objects;
	FrustumView m_frustumView;

	AABB m_sceneAABB;

	std::unique_ptr<Algorithm> m_algorithm;
	uint32_t m_algorithmFilter;

	std::unique_ptr<QueriesManager> m_queriesManager;

	// for run-time debugging purpose
	bool m_isEnabled = false;
	bool m_occlusionQueryEnabled = false;
};
} // namespace Cooling