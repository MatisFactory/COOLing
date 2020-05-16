#pragma once

#include <cooling/utils/aabb.hpp>
#include <glm/glm.hpp>

// scene size in plane XZ = [-SCENE_WIDTH; SCENE_WIDTH]
// scene size by Y-axis = [-SCENE_HEIGHT; SCENE_HEIGHT]
constexpr float SCENE_WIDTH = 3000.f;
constexpr float SCENE_HEIGHT = 200.f;

const Cooling::AABB SCENE_AABB = Cooling::AABB(glm::vec3(-SCENE_WIDTH, -SCENE_HEIGHT, -SCENE_WIDTH),
	glm::vec3(SCENE_WIDTH, SCENE_HEIGHT, SCENE_WIDTH));