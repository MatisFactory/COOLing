#pragma once

#include <cooling/export/cooling_dll.hpp>

#include <cooling/frustum_view.hpp>
#include <cooling/utils/aabb.hpp>

#include <glm/glm.hpp>

namespace Cooling
{
COOLING_DLL bool isDistancePositive(const glm::vec3& point, const Plane& plane);
COOLING_DLL float distance(const glm::vec3& point, const Plane& plane);
COOLING_DLL glm::vec3 getPositiveVertex(const glm::vec3& normal, const AABB& aabb);
COOLING_DLL bool isAABBVisible(const FrustumPlanes& planes, const AABB& aabb);
} // namespace Cooling