#pragma once

#include "Vec3.hpp"

#include <cassert>

#include <vector>

using fatpound::math::Vef3;

template<class T>
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

        cullFlags.resize(indices.size() / 3, false);
    }


public:
    std::vector<T> vertices;
    std::vector<size_t> indices;
    std::vector<bool> cullFlags;
};