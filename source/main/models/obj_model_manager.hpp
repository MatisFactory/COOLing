#pragma once

#include <main/models/obj_model.hpp>
#include <main/core/drawers/obj_model_drawer.hpp>
#include <main/core/shader/shader.hpp>

#include <cooling/object.hpp>
#include <cooling/utils/aabb.hpp>

#include <glm/glm.hpp>

#include <vector>
#include <unordered_map>

struct ObjModelInfo
{
	ObjModelInfo(const std::vector<glm::mat4>& transforms, const Shader& shader,
		const ObjModelDrawer& drawer, const glm::vec3& color = { 0.5, 0.7, 1.0 }, bool hardToDraw = false)
		: transforms(transforms), shader(shader), drawer(drawer), color(color), hardToDraw(hardToDraw) {}
	ObjModelInfo() = default;

	std::vector<glm::mat4> transforms;
	glm::vec3 color;
	Shader shader;
	ObjModelDrawer drawer;
	std::vector<Cooling::UniqueIndex> uids;
	bool hardToDraw;
};

class ObjModelManager
{
public:
	ObjModelManager();

	void draw();

	bool enabledOcclusionQueries() const;
	void setEnabledOcclusionQueris(bool value);

	bool showSceneAABB() const;
	void showSceneAABB(bool value);

	size_t countDrawed() const;
private:
	void loadAirplanes();
	void loadCubes();
	void loadModel(const std::string& filename, size_t count, const glm::vec3& scale = glm::vec3(1.f), const glm::vec3& color = glm::vec4(1.f), bool hardToDraw = true);
	void addToCullingManager();
	// used to draw fake box in occlusion query
	void drawBox(const Cooling::AABB& aabb, bool wireframe = false);
private:
	std::unordered_map<ObjModel, ObjModelInfo, ModelHasher> m_objModels;
	Shader m_shader;
	bool m_occlusionQueryEnabled = false;
	bool m_showSceneAABB = false;
	size_t m_countDrawed = 0;
};