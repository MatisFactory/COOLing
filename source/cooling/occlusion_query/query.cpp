#include <cooling/occlusion_query/query.hpp>

namespace Cooling
{

Query::Query()
{
	m_id = 0;
	glGenQueries(1, &m_id);
}

Query::~Query()
{
	glDeleteQueries(1, &m_id);
}

void Query::addQueryTask(std::function<void(AABB, bool)> drawBoxFunction, const AABB& aabb)
{
	glColorMask(false, false, false, false);
	glDepthMask(GL_FALSE);
	
	glBeginQuery(GL_SAMPLES_PASSED, m_id);
	
	glEnable(GL_DEPTH_TEST);

	drawBoxFunction(aabb, false);

	glEndQuery(GL_SAMPLES_PASSED);
}

bool Query::isVisible() const
{
	GLint countVisiblePoint = 0;
	glGetQueryObjectiv(m_id, GL_QUERY_RESULT, &countVisiblePoint);

	if (countVisiblePoint > 0)
	{
		return true;
	}

	return false;
}

} // namespace Cooling