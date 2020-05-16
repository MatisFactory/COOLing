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
	if (m_isOccluded == std::nullopt)
	{
		return m_isInFrustumView;
	}

	return m_isInFrustumView && m_isOccluded.value();
}

bool Object::isInFrustumView() const
{
	return m_isInFrustumView;
}

void Object::setIsInFrustumView(bool value)
{
	m_isInFrustumView = value;
}

void Object::setOccludedResult(std::optional<bool> value)
{
	m_isOccluded = value;
}

} // namespace Cooling