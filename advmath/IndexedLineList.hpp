#pragma once

#include "Vec3.hpp"

#include <vector>

struct IndexedLineList
{
	std::vector<Vef3> vertices;
	std::vector<size_t> indices;
};