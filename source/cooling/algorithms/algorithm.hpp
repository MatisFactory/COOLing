#pragma once

#include <cooling/export/cooling_dll.hpp>

#include <cooling/object.hpp>
#include <cooling/frustum_view.hpp>
#include <cooling/utils/aabb.hpp>

namespace Cooling
{
class COOLING_DLL Algorithm
{
public:
	virtual void init(const Objects& objects, const AABB& sceneAABB) { setSceneAABB(sceneAABB); };
	virtual void cullObjects(const FrustumPlanes& planes) = 0;

	void setSceneAABB(const AABB& aabb) { m_sceneAABB = aabb; }
private:
	AABB m_sceneAABB;
};
} // namespace Cooling