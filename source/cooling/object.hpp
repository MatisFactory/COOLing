#pragma once

#include <cooling/export/cooling_dll.hpp>
#include <cooling/utils/aabb.hpp>

#include <glm/glm.hpp>

#include <vector>
#include <memory>
#include <optional>

#include <stdint.h>

namespace Cooling
{
using UniqueIndex = uint32_t;

class COOLING_DLL Object
{
	static UniqueIndex s_currentFreeIndex;
public:
	Object() = default;
	Object(const AABB& aabb, bool hardToDraw = false);
	AABB getAABB() const;
	UniqueIndex getID() const;

	bool hardToDraw() const;


	bool isVisible() const;
	bool isInFrustumView() const;
	void setIsInFrustumView(bool value);
	void setOccludedResult(std::optional<bool> value);
private:
	AABB m_aabb;
	UniqueIndex m_index = 0;
	bool m_hardToDraw = false;
	bool m_isInFrustumView = false;
	std::optional<bool> m_isOccluded = std::nullopt;
	
};

using ObjectPtr = std::shared_ptr<Object>;
using Objects = std::vector<ObjectPtr>;
} // namespace Cooling