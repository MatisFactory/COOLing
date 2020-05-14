#pragma once

#include <main/third_party/OBJ_Loader.h>

#include <cooling/utils/aabb.hpp>

#include <glm/glm.hpp>

#include <vector>
#include <string>

class ObjModel
{
	friend struct ModelHasher;
public:
	ObjModel(const std::string& filename);

	bool operator==(const ObjModel& model) const;

	bool loadModel(bool normalizeVertex = true);

	bool isLoaded() const;

	std::vector<glm::vec3> getVertices() const;
	Cooling::AABB getAABB() const;
private:
	void normalizeVertices();
private:
	std::string m_filename;
	objl::Loader m_loader;

	bool m_loaded;

	std::vector<glm::vec3> m_vertices;

	Cooling::AABB m_aabb;
};

struct ModelHasher
{
	size_t operator()(const ObjModel& model) const
	{
		const size_t coef = 2'946'901;
		std::hash<std::string> hasher;
		return hasher(model.m_filename);
	}
};