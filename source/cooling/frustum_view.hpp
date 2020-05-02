#pragma once

#include <cooling/export/cooling_dll.hpp>

#include <glm/glm.hpp>

namespace Cooling
{
using Plane = glm::vec4;

struct COOLING_DLL FrustumPlanes
{
	Plane planes[6];

	Plane operator[](const uint32_t& index) const { return planes[index]; }
	Plane& operator[](const uint32_t& index) { return planes[index]; }
};

class COOLING_DLL FrustumView
{
public:
	FrustumView();

	void setViewProjection(const glm::mat4& viewProjection);
	FrustumPlanes getFrustumPlanes() const;

	void updateFrustumView();
private:
	glm::mat4 m_viewProjection;
	FrustumPlanes m_planes;
};
} // namespace Cooling