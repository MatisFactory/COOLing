#pragma once

#include <cooling/export/cooling_dll.hpp>
#include <cooling/utils/aabb.hpp>

#include <glm/glm.hpp>

#include <stdint.h>

namespace Cooling
{
using UniqueIndex = uint32_t;

class COOLING_DLL Object
{
	static UniqueIndex s_currentFreeIndex;
public:
	Object() = default;
	Object(const AABB& aabb);
	AABB getAABB() const;
	UniqueIndex getID() const;
private:
	UniqueIndex m_index;
	AABB m_aabb;
};
} // namespace Cooling