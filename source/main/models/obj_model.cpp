#include <main/models/obj_model.hpp>

ObjModel::ObjModel(const std::string& filename)
	: m_filename(filename)
	, m_loaded(false)
{
}

bool ObjModel::operator==(const ObjModel& model) const
{
	return m_filename == model.m_filename;
}

bool ObjModel::loadModel(bool normalize)
{
	if (m_loader.LoadFile(m_filename))
	{
		m_vertices = objl::veticesToVectorOfVec3(m_loader.LoadedVertices);

		if(normalize)
		{
			normalizeVertices();
		}

		m_aabb = Cooling::createAABBByVertex(m_vertices);

		m_loaded = true;
		return true;
	}
	else
	{
		return false;
	}
}

bool ObjModel::isLoaded() const
{
	return m_loaded;
}

std::vector<glm::vec3> ObjModel::getVertices() const
{
	return m_vertices;
}

Cooling::AABB ObjModel::getAABB() const
{
	return m_aabb;
}

void ObjModel::normalizeVertices()
{
	float max = 0.f;

	for (const auto& vertex : m_vertices)
	{
		if (abs(vertex.x) > max)
		{
			max = abs(vertex.x);
		}

		if (abs(vertex.y) > max)
		{
			max = abs(vertex.y);
		}

		if (abs(vertex.z) > max)
		{
			max = abs(vertex.z);
		}
	}

	for (auto& vertex : m_vertices)
	{
		vertex /= max; 
	}
}
