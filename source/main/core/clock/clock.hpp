#include <chrono>
#include <ctime>

class Clock
{
public:
	Clock();
	void computeDeltaTime();
	float getDeltaTime() const;
	float getFramerate() const;
private:
	std::chrono::time_point<std::chrono::system_clock> m_startTime;
	float m_deltaTime;
};