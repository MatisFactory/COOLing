#include <cooling/occlusion_query/queries_manager.hpp>

namespace Cooling
{

QueriesManager::QueriesManager(std::function<void(AABB)> drawedFunction, Objects& objects)
	: m_drawedFunction(std::move(drawedFunction))
	, m_objects(objects)
{
	// TODO: reconsider it
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
	for (const auto& object : m_hardToDrawObjects)
	{
		if(object->isInFrustumView())
		{
			auto query = std::make_shared<Query>(object);
			query->addQueryTask(m_drawedFunction, object->getAABB());

			m_queries.push_back(std::move(query));
		}
	}
}

void QueriesManager::applyResult()
{
	for (const auto& query : m_queries)
	{
		query->applyVisibility();
	}

	m_queries.clear();
}

} // namespace Cooling