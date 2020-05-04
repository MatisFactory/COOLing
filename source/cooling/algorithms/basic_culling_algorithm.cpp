#include <cooling/algorithms/basic_culling_algorithm.hpp>

#include <cooling/utils/visibility_tests.hpp>

namespace Cooling
{
void BasicCullingAlgorithm::init(const Objects& objects, const AABB& sceneAABB)
{
	Algorithm::init(objects, sceneAABB);

	m_objects = objects;
}

void BasicCullingAlgorithm::cullObjects(const FrustumPlanes& planes)
{
	for (auto& object : m_objects)
	{
		if (isAABBVisible(planes, object->getAABB()))
		{
			object->setVisible(true);
		}
	}
}

} // namespace Cooling