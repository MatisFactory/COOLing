#pragma once

#include <cooling/export/cooling_dll.hpp>

#include <cooling/algorithms/algorithm.hpp>

#include <memory>
#include <vector>

namespace Cooling
{
struct OctreeNode;

using OctreeChildrens = std::vector<std::shared_ptr<OctreeNode>>;

struct COOLING_DLL OctreeNode
{
	OctreeNode() = default;
	OctreeNode(const Node& node, const OctreeChildrens& childrens) : node(node), childrens(childrens) {};

	Node node;
	OctreeChildrens childrens;
};

class COOLING_DLL Octree : public Algorithm
{
public:
	void init(const Objects& objects, const AABB& sceneAABB) override;
	void cullObjects(const FrustumPlanes& planes) override;
private:
	void divideOctreeNode(OctreeNode* octreeNode);
	void recursiveProccessOctree(OctreeNode* octreeNode, const FrustumPlanes& planes);
	void markVisibleOctreeNode(OctreeNode* octreeNode, const FrustumPlanes& planes);
private:
	OctreeNode m_root;
};
} // namespace Cooling