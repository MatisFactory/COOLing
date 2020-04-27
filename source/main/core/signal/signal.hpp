#include <unordered_map>
#include <functional>
#include <cassert>
#include <vector>

using Connection = uint64_t;

template<class... Args>
class Signal
{
	using Callback = std::function<void(Args...)>;
public:
	void operator()(Args... args)
	{
		for (const auto&[_, callback] : m_connections)
		{
			callback(args...);
		}
	}
	Connection connect(Callback callback)
	{
		m_connections[m_uid] = std::move(callback);
		return m_uid++;
	}
	void disconnect(Connection connection)
	{
		auto it = m_connections.find(connection);
		assert(it != m_connections.end());

		m_connections.erase(it);
	}
private:
	uint64_t m_uid = 0;
	std::unordered_map<Connection, Callback> m_connections;
};