#include <cooling/profiler/profiler.hpp>
#include <iostream>

namespace Cooling
{
Profiler::Profiler(const std::string& name /*= ""*/)
	: m_name(name)
	, m_startTime(std::chrono::system_clock::now())
{
}

Profiler::~Profiler()
{
	auto finish = std::chrono::system_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(finish - m_startTime).count();
	//std::cout << m_name << " duration is " << time << " microsecond\n";
}

} // namespace Cooling