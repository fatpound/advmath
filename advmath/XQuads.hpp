#pragma once

#include "Vec3.hpp"
#include "IndexedLineList.hpp"
#include "IndexedTriangleList.hpp"

#include <vector>

class XQuads
{
public:
    XQuads(float size)
    {
        const float side = size / 2.0f;
        vertices.emplace_back(-side, -side, -side);
        vertices.emplace_back( side, -side, -side);
        vertices.emplace_back(-side,  side, -side);
        vertices.emplace_back( side,  side, -side);
        vertices.emplace_back(-side, -side,  side);
        vertices.emplace_back( side, -side,  side);
        vertices.emplace_back(-side,  side,  side);
        vertices.emplace_back( side,  side,  side);
    }


public:
    IndexedLineList GetLines() const
    {
        return IndexedLineList{
            vertices,{
                0,4, 4,7, 7,3, 3,0,
                1,5, 5,6, 6,2, 2,1
            }
        };
    }
    IndexedTriangleList<Vef3> GetTriangles() const
    {
        return IndexedTriangleList<Vef3>{
            vertices,{
                0,4,3, 4,7,3,
                2,6,1, 6,5,1 }
        };
    }


private:
    std::vector<Vef3> vertices;
};