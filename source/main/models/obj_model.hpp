#pragma once

#include <main/third_party/OBJ_Loader.h>

#include <cooling/utils/aabb.hpp>

#include <glm/glm.hpp>

#include <vector>
#include <string>

class ObjModel
{
public:
	ObjModel(const std::string& filename);

	bool loadModel();

	std::vector<glm::vec3> getVertices() const;
	std::vector<glm::vec3> getUniqueVertices() const;

	Cooling::AABB getAABB() const;
private:
	std::string m_filename;
	objl::Loader m_loader;

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_uniqueVetices;

	Cooling::AABB m_aabb;
};