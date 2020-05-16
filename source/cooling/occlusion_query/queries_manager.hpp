#pragma once

#include <cooling/export/cooling_dll.hpp>
#include <cooling/utils/aabb.hpp>
#include <cooling/object.hpp>
#include <cooling/occlusion_query/query.hpp>

#include <gl/glew.h>

#include <vector>
#include <functional>

namespace Cooling
{
class COOLING_DLL QueriesManager
{
public:
	QueriesManager(std::function<void(AABB)> drawedFunction, Objects& objects);
	~QueriesManager() = default;

	void runQueries();
	// should be invoked after frustum culling
	void applyResult();
private:
	Objects& m_objects;
	std::vector<ObjectPtr> m_hardToDrawObjects;
	std::vector<QueryPtr> m_queries;
	std::function<void(AABB)> m_drawedFunction;
};
} // namespace Cooling