#pragma once

#include "Vec3.hpp"

#include <cassert>

#include <vector>

template <class T>
class IndexedTriangleList
{
public:
    IndexedTriangleList(std::vector<T> in_verts, std::vector<size_t> in_indices)
        :
        vertices(std::move(in_verts)),
        indices(std::move(in_indices))
    {
        assert(vertices.size() > 2);
        assert(indices.size() % 3 == 0);
    }


public:
    std::vector<T> vertices;
    std::vector<size_t> indices;
};