#pragma once

#include <cooling/export/cooling_dll.hpp>
#include <cooling/utils/aabb.hpp>
#include <cooling/object.hpp>
//#include <gl/GL.h>

#include <gl/glew.h>

#include <glm/glm.hpp>

#include <glfw/glfw3.h>


#include <functional>
#include <memory>

namespace Cooling
{
class Query;
using QueryPtr = std::shared_ptr<Query>;

class COOLING_DLL Query
{
public:
	Query(const ObjectPtr& object);
	~Query();

	void addQueryTask(std::function<void(AABB)> drawBoxFunction, const AABB&);
	void applyVisibility() const;
private:
	GLuint m_id;
	ObjectPtr m_object;
};
} // namespace Cooling