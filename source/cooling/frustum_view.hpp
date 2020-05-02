#pragma once

#include <cooling/export/cooling_dll.hpp>

#include <glm/glm.hpp>

namespace Cooling
{
using Plane = glm::vec4;

struct COOLING_DLL FrustumPlanes
{
	Plane left;
	Plane right;
	Plane bottom;
	Plane top;
	Plane near;
	Plane far;
};

class COOLING_DLL FrustumView
{
public:
	FrustumView(const glm::mat4& viewProjection);

	void setViewProjection(const glm::mat4& viewProjection);
	FrustumPlanes getFrustumPlanes() const;
private:
	void updateFrustumView();
private:
	glm::mat4 m_viewProjection;
	FrustumPlanes m_planes;
};
} // namespace Cooling