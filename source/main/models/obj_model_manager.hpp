#pragma once

#include <main/models/obj_model.hpp>
#include <main/core/drawers/obj_model_drawer.hpp>
#include <main/core/shader/shader.hpp>

#include <cooling/object.hpp>

#include <glm/glm.hpp>

#include <vector>
#include <unordered_map>

struct ObjModelInfo
{
	ObjModelInfo(const std::vector<glm::mat4>& transforms, const Shader& shader, const ObjModelDrawer& drawer)
		: transforms(transforms), shader(shader), drawer(drawer) {}
	ObjModelInfo() : shader("", ""), drawer() {}

	std::vector<glm::mat4> transforms;
	Shader shader;
	ObjModelDrawer drawer;
	std::vector<Cooling::UniqueIndex> uids;
};

class ObjModelManager
{
public:
	ObjModelManager();

	void draw();
private:
	void addToCullingManager();
private:
	std::unordered_map<ObjModel, ObjModelInfo, ModelHasher> m_objModels;
};