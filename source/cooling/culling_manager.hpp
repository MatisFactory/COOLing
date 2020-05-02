#pragma once

#include <cooling/export/cooling_dll.hpp>

#include <cooling/object.hpp>
#include <cooling/frustum_view.hpp>

#include <glm/glm.hpp>

#include <vector>

namespace Cooling
{
class COOLING_DLL CullingManager
{
public:
	CullingManager();

	[[nodiscard]] Object registerObject(const AABB& aabb);
	void setViewProjectionMatrix(const glm::mat4& viewProjection);
	bool isVisible(UniqueIndex index) const;
	bool isVisible(Object object) const;

	void update();

	void cleanupObjectsInfo();
private:
	std::vector<bool> m_isVisibleObject;
	std::vector<Object> m_objects;

	FrustumView m_frustumView;
};
} // namespace Cooling