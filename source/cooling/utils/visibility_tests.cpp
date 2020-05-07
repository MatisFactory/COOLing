#include <cooling/utils/visibility_tests.hpp>

#include <cmath>

namespace Cooling
{

Objects intersectedObject(const AABB& aabb, const Objects& objects)
{
	Objects result;
	for (const auto& object : objects)
	{
		if (object->getAABB().isIntersect(aabb))
		{
			result.push_back(object);
		}
	}

	return result;
}

bool isDistancePositive(const glm::vec3& point, const Plane& plane)
{
	return point[0] * plane[0] + point[1] * plane[1] + point[2] * plane[2] + plane[3] > 0.f;
}

float distance(const glm::vec3& point, const Plane& plane)
{
	return point[0] * plane[0] + point[1] * plane[1] + point[2] * plane[2] + plane[3] / sqrt(plane[0] * plane[0] + plane[1] * plane[1] + plane[2] * plane[2]);
}

glm::vec3 getPositiveVertex(const glm::vec3& normal, const AABB& aabb)
{
	glm::vec3 positive = aabb.min;
	if (normal.x >= 0)
		positive.x = aabb.max.x;
	if (normal.y >= 0)
		positive.y = aabb.max.y;
	if (normal.z >= 0)
		positive.z = aabb.max.z;
	return positive;
}

bool Cooling::isAABBVisible(const FrustumPlanes& planes, const AABB& aabb)
{
	for (auto& plane : planes.planes)
	{
		if (!isDistancePositive(getPositiveVertex(plane, aabb), plane))
		{
			return false;
		}
	}

	return true;
}

} // namespace Cooling