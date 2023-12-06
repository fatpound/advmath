#pragma once

#include "Vec3.hpp"

#include <vector>

struct IndexedTriangleList
{
	std::vector<Vef3> vertices;
	std::vector<size_t> indices;
};