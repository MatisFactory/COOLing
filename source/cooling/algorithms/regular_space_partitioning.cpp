#include <cooling/algorithms/regular_space_partitioning.hpp>
#include <cooling/utils/visibility_tests.hpp>
#include <cooling/profiler/profiler.hpp>

#include <glm/glm.hpp>

namespace
{
	constexpr uint32_t COUNT_SEGMENT_ON_AXIS = 4;
}

namespace Cooling
{
RegularSpacePartitioning::RegularSpacePartitioning()
	: m_countSegmentOnAxis(COUNT_SEGMENT_ON_AXIS)
{
}

void RegularSpacePartitioning::init(const Objects& objects, const AABB& sceneAABB)
{
	Algorithm::init(objects, sceneAABB);

	// for convient
	uint32_t n = m_countSegmentOnAxis;

	m_nodes.resize(m_countSegmentOnAxis * m_countSegmentOnAxis * m_countSegmentOnAxis);

	float xLength = m_sceneAABB.max.x - m_sceneAABB.min.x;
	float yLength = m_sceneAABB.max.y - m_sceneAABB.min.y;
	float zLength = m_sceneAABB.max.z - m_sceneAABB.min.z;

	float xNodeLength = xLength / n;
	float yNodeLength = yLength / n;
	float zNodeLength = zLength / n;

	glm::vec3 xNodeVertex = glm::vec3(xNodeLength, 0, 0);
	glm::vec3 yNodeVertex = glm::vec3(0, yNodeLength, 0);
	glm::vec3 zNodeVertex = glm::vec3(0, 0, zNodeLength);

	glm::vec3 startVertex = m_sceneAABB.min;
	glm::vec toMaxVertex = glm::vec3(xNodeLength, yNodeLength, zNodeLength);

	for (int i = 0; i < m_countSegmentOnAxis; i++)
	{
		for (int j = 0; j < m_countSegmentOnAxis; j++)
		{
			for (int k = 0; k < m_countSegmentOnAxis; k++)
			{
				glm::vec3 min = startVertex + 
								xNodeVertex * static_cast<float>(k) +
								yNodeVertex * static_cast<float>(j) +
								zNodeVertex * static_cast<float>(i);

				m_nodes[i*n*n + j*n + k].aabb = {min, min + toMaxVertex}; 
			}
		}
	}

	for (const auto& object : objects)
	{
		for (auto& node : m_nodes)
		{
			if (node.aabb.isIntersect(object->getAABB()))
			{
				node.objects.push_back(object);
			}
		}
	}

}

void RegularSpacePartitioning::cullObjects(const FrustumPlanes& planes)
{
	for (auto& node : m_nodes)
	{
		if (isAABBVisible(planes, node.aabb))
		{
			for (auto& object : node.objects)
			{
				if (isAABBVisible(planes, object->getAABB()))
				{
					object->setIsInFrustumView(true);
				}
			}
		}
	}
	
}

} // namespace Cooling