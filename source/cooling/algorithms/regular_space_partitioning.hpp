#pragma once

#include <cooling/export/cooling_dll.hpp>

#include <cooling/object.hpp>
#include <cooling/frustum_view.hpp>
#include <cooling/utils/aabb.hpp>
#include <cooling/algorithms/algorithm.hpp>

#include <vector>

namespace Cooling
{
struct COOLING_DLL Node
{
	Objects objects;
	AABB aabb;
};

class COOLING_DLL RegularSpacePartitioning : public Algorithm
{
public:
	RegularSpacePartitioning();

	void init(const Objects& objects, const AABB& sceneAABB) override;
	void cullObjects(const FrustumPlanes& planes) override;
private:
	AABB m_sceneAABB;
	uint32_t m_countSegmentOnAxis = 0;
	std::vector<Node> m_nodes;
};
} // namespace Cooling
