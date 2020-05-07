#pragma once

#include <cooling/export/cooling_dll.hpp>

#include <chrono>
#include <ctime>
#include <string>

namespace Cooling
{
class COOLING_DLL Profiler
{
public:
	Profiler(const std::string& name = "");
	~Profiler();
private:
	std::string m_name;
	std::chrono::time_point<std::chrono::system_clock> m_startTime;
};
} // namespace Cooling