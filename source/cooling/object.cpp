#include <cooling/object.hpp>

namespace Cooling
{
UniqueIndex Object::s_currentFreeIndex = 0;

Object::Object(const AABB& aabb, bool hardToDraw)
{
	m_index = s_currentFreeIndex++;
	m_aabb = aabb;
	m_hardToDraw = hardToDraw;
}

Cooling::AABB Object::getAABB() const
{
	return m_aabb;
}

Cooling::UniqueIndex Object::getID() const
{
	return m_index;
}

bool Object::hardToDraw() const
{
	return m_hardToDraw;
}

bool Object::isVisible() const
{
	return m_isVisible;
}

void Object::setVisible(bool value)
{
	m_isVisible = value;
}

void Object::setANDVisible(bool value)
{
	m_isVisible &= value;
}

} // namespace Cooling