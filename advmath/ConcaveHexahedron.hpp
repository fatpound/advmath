#pragma once

#include "Vec3.hpp"
#include "IndexedLineList.hpp"
#include "IndexedTriangleList.hpp"

#include <vector>

class ConcaveHexahedron
{
public:
    ConcaveHexahedron(float size)
    {
        const float side = size / 2.0f;
        vertices.emplace_back( 0.0f,  side,  0.0f);
        vertices.emplace_back(-side, -side,  0.0f);
        vertices.emplace_back( side, -side,  0.0f);
        vertices.emplace_back( 0.0f,  0.0f,  side);
        vertices.emplace_back( 0.0f,  0.0f, -side);
    }


public:
    IndexedLineList GetLines() const
    {
        return IndexedLineList{
            vertices,{
                0,1, 1,3, 3,2, 2,0,
                3,0, 3,4, 1,4, 2,4, 4,0
            }
        };
    }
    IndexedTriangleList<Vef3> GetTriangles() const
    {
        return IndexedTriangleList<Vef3>{
            vertices,
            {
                1,0,3, 3,0,2,
                1,4,0, 4,2,0,
                3,4,1, 4,3,2
            }
        };
    }


private:
    std::vector<Vef3> vertices;
};