#pragma once

#include <main/core/shader/shader.hpp>
#include <main/models/cube.hpp>
#include <cooling/object.hpp>

#include <glm/glm.hpp>

#include <vector>

namespace
{
	constexpr size_t COUNT_OF_CUBES = 10000;
}

class CubeManager
{
public:
	CubeManager();
	void init(uint32_t count = COUNT_OF_CUBES);

	void draw();

	uint32_t countDrawedCube() const;
private:
	void setupViewProjection();
private:
	Shader m_shader;
	std::vector<Cube> m_cubes;
	std::vector<Cooling::UniqueIndex> m_cullingIndexes;
	GLint m_transformLocation;

	uint32_t m_countDrawedCube = 0;
};