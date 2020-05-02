#pragma once

#include <main/core/shader/shader.hpp>
#include <main/models/cube.hpp>

#include <glm/glm.hpp>

#include <vector>

namespace
{
	constexpr size_t COUNT_OF_CUBES = 500;
}

class CubeManager
{
public:
	CubeManager(uint32_t count = COUNT_OF_CUBES);

	void draw();
private:
	void setupViewProjection();
private:
	Shader m_shader;
	std::vector<Cube> m_cubes;
	GLint m_transformLocation;
};