#include <cooling/algorithms/octree.hpp>
#include <cooling/utils/visibility_tests.hpp>

#include <cooling/profiler/profiler.hpp>

#include <glm/glm.hpp>

namespace
{
	constexpr uint32_t MIN_COUNT_OBJECT = 100;
	constexpr uint32_t MAX_CHILDREN = 8;
	constexpr uint32_t PART_COUNT_ON_AXIS = 2;
}

namespace Cooling
{
void Octree::init(const Objects& objects, const AABB& sceneAABB)
{
	Algorithm::init(objects, sceneAABB);

	m_root.node = Node(objects, sceneAABB);
	divideOctreeNode(&m_root);
}

void Octree::cullObjects(const FrustumPlanes& planes)
{
	recursiveProccessOctree(&m_root, planes);
}

void Octree::divideOctreeNode(OctreeNode* octreeNode)
{
	if (octreeNode->node.objects.size() < MIN_COUNT_OBJECT)
	{
		return;
	}

	uint32_t n = PART_COUNT_ON_AXIS;

	AABB octreeNodeAABB = octreeNode->node.aabb;

	OctreeChildrens& childrens = octreeNode->childrens;

	float xLength = octreeNodeAABB.max.x - octreeNodeAABB.min.x;
	float yLength = octreeNodeAABB.max.y - octreeNodeAABB.min.y;
	float zLength = octreeNodeAABB.max.z - octreeNodeAABB.min.z;

	float xNodeLength = xLength / n;
	float yNodeLength = yLength / n;
	float zNodeLength = zLength / n;

	glm::vec3 xNodeVertex = glm::vec3(xNodeLength, 0, 0);
	glm::vec3 yNodeVertex = glm::vec3(0, yNodeLength, 0);
	glm::vec3 zNodeVertex = glm::vec3(0, 0, zNodeLength);

	glm::vec3 startVertex = octreeNodeAABB.min;
	glm::vec3 toMaxVertex = glm::vec3(xNodeLength, yNodeLength, zNodeLength);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				glm::vec3 min = startVertex +
					xNodeVertex * static_cast<float>(k) +
					yNodeVertex * static_cast<float>(j) +
					zNodeVertex * static_cast<float>(i);

				auto partOctreeNode = std::make_shared<OctreeNode>();

				AABB partAABB = {min, min + toMaxVertex};
				const Objects& partObjects = intersectedObject(partAABB, octreeNode->node.objects);

				partOctreeNode->node = Node(partObjects, partAABB);

				octreeNode->childrens.push_back(std::move(partOctreeNode));
			}
		}
	}

	for (const auto& child : octreeNode->childrens)
	{
		divideOctreeNode(child.get());
	}
}

void Octree::recursiveProccessOctree(OctreeNode* octreeNode, const FrustumPlanes& planes)
{
	if (!isAABBVisible(planes, octreeNode->node.aabb))
	{
		return;
	}

	if (octreeNode->childrens.empty())
	{
		markVisibleOctreeNode(octreeNode, planes);
		return;
	}

	for (const auto& octreeChild : octreeNode->childrens)
	{
		recursiveProccessOctree(octreeChild.get(), planes);
	}
}

void Octree::markVisibleOctreeNode(OctreeNode* octreeNode, const FrustumPlanes& planes)
{
	for (auto& object : octreeNode->node.objects)
	{
		if(isAABBVisible(planes, object->getAABB()))
		{
			object->setIsInFrustumView(true);
		}
	}
}

} // namespace Cooling