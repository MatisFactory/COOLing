#pragma once

#include <cooling/export/cooling_dll.hpp>

#include <cooling/algorithms/algorithm.hpp>

namespace Cooling
{
class COOLING_DLL BasicCullingAlgorithm : public Algorithm
{
public:
	BasicCullingAlgorithm() = default;
	void init(const Objects& objects, const AABB& sceneAABB) override;
	void cullObjects(const FrustumPlanes& planes) override;
private:
	Objects m_objects;
};
} // namespace Cooling
