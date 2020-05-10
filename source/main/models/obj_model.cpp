#include <main/models/obj_model.hpp>

ObjModel::ObjModel(const std::string& filename)
	: m_filename(filename)
{
}

bool ObjModel::loadModel()
{
	if (m_loader.LoadFile(m_filename))
	{
		m_vertices = objl::veticesToVectorOfVec3(m_loader.LoadedVertices);
		m_uniqueVetices = m_loader.LoadedUniqueVertices;

		m_aabb = Cooling::createAABBByVertex(m_uniqueVetices);

		return true;
	}
	else
	{
		return false;
	}
}

std::vector<glm::vec3> ObjModel::getVertices() const
{
	return m_vertices;
}

std::vector<glm::vec3> ObjModel::getUniqueVertices() const
{
	return m_uniqueVetices;
}

Cooling::AABB ObjModel::getAABB() const
{
	return m_aabb;
}
