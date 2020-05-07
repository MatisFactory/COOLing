#include <cooling/utils/aabb.hpp>

#include <limits>

namespace Cooling
{

AABB::AABB(const glm::vec3& min, const glm::vec3& max)
	: min(min)
	, max(max)
{
}

bool AABB::isIntersect(const AABB& aabb)
{
	return aabb.min.x <= max.x && min.x <= aabb.max.x &&
		aabb.min.y <= max.y && min.y <= aabb.max.y &&
		aabb.min.z <= max.z && min.z <= aabb.max.z;
}

AABB createAABBByVertex(const std::vector<glm::vec3>& vertecies)
{
     if(vertecies.empty())
     {
          return {glm::vec3(std::numeric_limits<float>().min()), glm::vec3(std::numeric_limits<float>().max())};
     }

     AABB aabb;
     aabb.min = vertecies.front();
     aabb.max = aabb.min;

     for(const auto& vertex : vertecies)
     {
          if(vertex.x < aabb.min.x)
          {
               aabb.min.x = vertex.x;
          }
          if(vertex.y < aabb.min.y)
          {
               aabb.min.y = vertex.y;
          }
          if(vertex.z < aabb.min.z)
          {
               aabb.min.z = vertex.z;
          }

          if(vertex.x > aabb.max.x)
          {
               aabb.max.x = vertex.x;
          }
          if(vertex.y > aabb.max.y)
          {
               aabb.max.y = vertex.y;
          }
          if(vertex.z > aabb.max.z)
          {
               aabb.max.z = vertex.z;
          }
     }

     return aabb;
}
} // namespace Cooling