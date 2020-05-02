#include <cooling/object.hpp>

namespace Cooling
{
UniqueIndex Object::s_currentFreeIndex = 0;

Object::Object(const AABB& aabb)
{
	m_index = s_currentFreeIndex++;
	m_aabb = aabb;
}

Cooling::AABB Object::getAABB() const
{
	return m_aabb;
}

Cooling::UniqueIndex Object::getID() const
{
	return m_index;
}

} // namespace Cooling