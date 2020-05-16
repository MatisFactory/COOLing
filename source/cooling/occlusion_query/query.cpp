#include <cooling/occlusion_query/query.hpp>

namespace Cooling
{

Query::Query(const ObjectPtr& object)
	: m_object(object)
{
	/*GLuint id = 0;*/
	m_id = 0;
	glGenQueries(1, &m_id);
}

Query::~Query()
{
	glDeleteQueries(1, &m_id);
}

void Query::addQueryTask(std::function<void(AABB)> drawBoxFunction, const AABB& aabb)
{
	glColorMask(false, false, false, false);
	glDepthMask(GL_FALSE);
	
	glBeginQuery(GL_SAMPLES_PASSED, m_id);
	
	glEnable(GL_DEPTH_TEST);

	drawBoxFunction(aabb);

	glEndQuery(GL_SAMPLES_PASSED);

	glColorMask(true, true, true, true);
	glDepthMask(GL_TRUE);
}

void Query::applyVisibility() const
{
	GLint countVisiblePoint = 0;
	glGetQueryObjectiv(m_id, GL_QUERY_RESULT, &countVisiblePoint);

	m_object->setOccludedResult(countVisiblePoint > 0);
}

} // namespace Cooling