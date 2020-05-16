#include <cooling/occlusion_query/queries_manager.hpp>

namespace Cooling
{

QueriesManager::QueriesManager(std::function<void(AABB)> drawedFunction, Objects& objects)
	: m_drawedFunction(std::move(drawedFunction))
	, m_objects(objects)
{
	glfwInit();
	glewInit();
	for (auto& object : m_objects)
	{
		if (object->hardToDraw())
		{
			m_hardToDrawObjects.push_back(object);
		}
	}
}

void QueriesManager::runQueries()
{
	size_t i = 0;
	m_queries.resize(m_hardToDrawObjects.size());
	for (const auto& object : m_hardToDrawObjects)
	{
		m_queries[i] = std::make_shared<Query>();
		m_queries[i]->addQueryTask(m_drawedFunction, object->getAABB());
		i++;
	}
}

void QueriesManager::applyResult()
{
	size_t i = 0;
	for (const auto& query : m_queries)
	{
		m_hardToDrawObjects[i++]->setANDVisible(query->isVisible());
	}
}

} // namespace Cooling