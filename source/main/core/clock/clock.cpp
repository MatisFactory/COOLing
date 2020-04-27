#include <core/clock/clock.hpp>

Clock::Clock()
{
	m_startTime = std::chrono::system_clock::now();
}

void Clock::computeDeltaTime()
{
	auto finish = std::chrono::system_clock::now();
	m_deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(finish - m_startTime).count();
	m_startTime = finish;
}

float Clock::getDeltaTime() const
{
	return m_deltaTime;
}

float Clock::getFramerate() const
{
	return 1.f/m_deltaTime;
}

