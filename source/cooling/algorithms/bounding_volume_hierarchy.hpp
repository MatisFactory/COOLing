#pragma once

#include <cooling/export/cooling_dll.hpp>

#include <cooling/algorithms/algorithm.hpp>

#include <memory>

namespace Cooling
{
enum class AXIS
{
	X, Y, Z
};

AXIS findLongestAxis(const AABB& sceneAABB);

bool sortXAxis(const ObjectPtr& a, const ObjectPtr& b);
bool sortYAxis(const ObjectPtr& a, const ObjectPtr& b);
bool sortZAxis(const ObjectPtr& a, const ObjectPtr& b);

struct BVHNode
{
	BVHNode() {}
	BVHNode(const Node& node) : node(node) {}
	Node node;
	std::unique_ptr<BVHNode> left;
	std::unique_ptr<BVHNode> right;
};

class COOLING_DLL BoundingVolumeHierarchy : public Algorithm
{
public:
	BoundingVolumeHierarchy() = default;
	void init(const Objects& objects, const AABB& sceneAABB) override;
	void cullObjects(const FrustumPlanes& planes) override;
private:
	BVHNode buildTree(const Objects& objects) const;
	void divideNode(BVHNode& parent) const;
	AABB computeSceneAABB(const Objects& objects) const;
	void traverse(BVHNode* node, const FrustumPlanes& planes);
private:
	BVHNode m_root;
};
} // namespace Cooling
