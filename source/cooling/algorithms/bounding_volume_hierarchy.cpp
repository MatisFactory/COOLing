#include <cooling/algorithms/bounding_volume_hierarchy.hpp>

#include <cooling/profiler/profiler.hpp>
#include <cooling/utils/visibility_tests.hpp>

#include <algorithm>

namespace
{
	constexpr size_t MIN_COUNT_OBJECT_IN_NODE = 2000;
}

namespace Cooling
{
void BoundingVolumeHierarchy::init(const Objects& objects, const AABB& sceneAABB)
{
	m_root = buildTree(objects);
}

void BoundingVolumeHierarchy::cullObjects(const FrustumPlanes& planes)
{
	traverse(&m_root, planes);
}

BVHNode BoundingVolumeHierarchy::buildTree(const Objects& objects) const
{
	BVHNode root;
	root.node.objects = objects;
	root.node.aabb = computeSceneAABB(objects);
	divideNode(root);
	return root;
}

void BoundingVolumeHierarchy::divideNode(BVHNode& parent) const
{
	if (parent.node.objects.size() < MIN_COUNT_OBJECT_IN_NODE)
	{
		return;
	}

	AXIS longestAxis = findLongestAxis(parent.node.aabb);
	switch (longestAxis)
	{
		case AXIS::X:
			std::sort(parent.node.objects.begin(), parent.node.objects.end(), sortXAxis);
			break;
		case AXIS::Y:
			std::sort(parent.node.objects.begin(), parent.node.objects.end(), sortYAxis);
			break;
		case AXIS::Z:
			std::sort(parent.node.objects.begin(), parent.node.objects.end(), sortZAxis);
			break;
	}

	const Objects& leftObjects = {parent.node.objects.begin(), parent.node.objects.begin() + parent.node.objects.size()/2};
	const Objects& rightObjects = { parent.node.objects.begin() + parent.node.objects.size() / 2, parent.node.objects.end()};

	Node left = {leftObjects, computeSceneAABB(leftObjects)};
	Node right = {rightObjects, computeSceneAABB(rightObjects)};

	parent.left = std::make_unique<BVHNode>(left);
	parent.right = std::make_unique<BVHNode>(right);

	divideNode(*parent.left.get());
	divideNode(*parent.right.get());
}

AABB BoundingVolumeHierarchy::computeSceneAABB(const Objects& objects) const
{
	assert(!objects.empty());
	AABB aabb = objects.front()->getAABB();
	for (auto& item : objects)
	{
		aabb.min.x = std::min(item->getAABB().min.x, aabb.min.x);
		aabb.min.y = std::min(item->getAABB().min.y, aabb.min.y);
		aabb.min.z = std::min(item->getAABB().min.z, aabb.min.z);
		aabb.max.x = std::max(item->getAABB().max.x, aabb.max.x);;
		aabb.max.y = std::max(item->getAABB().max.y, aabb.max.y);;
		aabb.max.z = std::max(item->getAABB().max.z, aabb.max.z);;
	}
	return aabb;
}

void BoundingVolumeHierarchy::traverse(BVHNode* node, const FrustumPlanes& planes)
{
	if (!node)
	{
		return;
	}

	if (!isAABBVisible(planes, node->node.aabb))
	{
		return;
	}

	if (!node->left && !node->right)
	{
		for (auto& object : node->node.objects)
		{
			if (isAABBVisible(planes, object->getAABB()))
			{
				object->setIsInFrustumView(true);
			}
		}
	}

	traverse(node->left.get(), planes);
	traverse(node->right.get(), planes);
}

AXIS findLongestAxis(const AABB& aabb)
{
	float x = abs(aabb.min.x - aabb.max.x);
	float y = abs(aabb.min.y - aabb.max.y);
	float z = abs(aabb.min.z - aabb.max.z);
	if (x > y && x > z)
	{
		return AXIS::X;
	}
	if (y > x && y > z)
	{
		return AXIS::Y;
	}
	return AXIS::Z;
}

bool sortXAxis(const ObjectPtr& a, const ObjectPtr& b)
{
	return a->getAABB().min.x + a->getAABB().max.x < b->getAABB().min.x + b->getAABB().max.x;
}

bool sortYAxis(const ObjectPtr& a, const ObjectPtr& b)
{
	return a->getAABB().min.y + a->getAABB().max.y < b->getAABB().min.y + b->getAABB().max.y;
}

bool sortZAxis(const ObjectPtr& a, const ObjectPtr& b)
{
	return a->getAABB().min.z + a->getAABB().max.z < b->getAABB().min.z + b->getAABB().max.z;
}

} // namespace Cooling