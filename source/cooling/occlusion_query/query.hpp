#pragma once

#include <gl/glew.h>

#include <glm/glm.hpp>

#include <glfw/glfw3.h>

#include <cooling/export/cooling_dll.hpp>
#include <cooling/utils/aabb.hpp>

//#include <gl/GL.h>

#include <functional>
#include <memory>

namespace Cooling
{
class Query;
using QueryPtr = std::shared_ptr<Query>;

class COOLING_DLL Query
{
public:
	Query();
	~Query();

	void addQueryTask(std::function<void(AABB)> drawBoxFunction, const AABB&);
	bool isVisible() const;
private:
	GLuint m_id;
};
} // namespace Cooling