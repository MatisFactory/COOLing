#pragma once

#include <cooling/export/cooling_dll.hpp>

#include <glm/glm.hpp>

#include <vector>

namespace Cooling
{
struct COOLING_DLL AABB
{
     glm::vec3 min;
     glm::vec3 max;
};

COOLING_DLL AABB createAABBByVertex(const std::vector<glm::vec3>& vertecies);
} // namespace Cooling