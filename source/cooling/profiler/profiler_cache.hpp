#include <cooling/export/cooling_dll.hpp>

namespace Cooling
{
class COOLING_DLL ProfilerCache
{
public:
	ProfilerCache(const ProfilerCache&) = delete;
	ProfilerCache(ProfilerCache&&) = delete;

	static ProfilerCache& instance()
	{
		static ProfilerCache instance;
		return instance;
	}

	int getDrawTime() const { return m_drawTime; }
	void setDrawTime(int value) { m_drawTime = value; }

	int getCullingTime() const { return m_cullingTime; }
	void setCullingTime(int value) { m_cullingTime = value; }

private:
	ProfilerCache() = default;
	size_t m_drawTime = 2;
	size_t m_cullingTime = 3;
};
} // namespace Cooling