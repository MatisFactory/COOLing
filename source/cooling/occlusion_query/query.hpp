#pragma once

#include <cooling/export/cooling_dll.hpp>
#include <cooling/utils/aabb.hpp>

#include <gl/glew.h>

#include <functional>

namespace Cooling
{
class COOLING_DLL Query
{
public:
	Query();
	~Query();

	void addQueryTask(std::function<void(AABB, bool)> drawBoxFunction, const AABB&);
	bool isVisible() const;
private:
	GLuint m_id;
};
} // namespace Cooling