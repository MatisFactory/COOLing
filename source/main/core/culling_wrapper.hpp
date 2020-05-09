#pragma once

#include <cooling/culling_manager.hpp>

class CullingWrapper
{
public:
	
	CullingWrapper(const CullingWrapper&) = delete;
	CullingWrapper(CullingWrapper&&) = delete;

	static CullingWrapper& instance()
	{
		static CullingWrapper cullingWrapper;
		return cullingWrapper;
	}

	Cooling::CullingManager& cullingManager() { return m_cullingManager; }
private:
	CullingWrapper() = default;
private:
	Cooling::CullingManager m_cullingManager;
};