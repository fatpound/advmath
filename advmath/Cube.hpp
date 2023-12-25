#pragma once

#include "IndexedLineList.hpp"
#include "IndexedTriangleList.hpp"
#include "TextureVertex.hpp"

class Cube
{
public:
    Cube(float size, float texdim = 1.0f)
    {
        const float side = size / 2.0f;
        vertices.emplace_back(-side, -side, -side); // 0
        texCoords.emplace_back(0.0f, texdim);

        vertices.emplace_back( side, -side, -side); // 1
        texCoords.emplace_back(texdim, texdim);

        vertices.emplace_back(-side,  side, -side); // 2
        texCoords.emplace_back(0.0f, 0.0f);

        vertices.emplace_back( side,  side, -side); // 3
        texCoords.emplace_back(texdim, 0.0f);

        vertices.emplace_back(-side, -side,  side); // 4
        texCoords.emplace_back(texdim, texdim);

        vertices.emplace_back( side, -side,  side); // 5
        texCoords.emplace_back(0.0f, texdim);

        vertices.emplace_back(-side,  side,  side); // 6
        texCoords.emplace_back(texdim, 0.0f);

        vertices.emplace_back( side,  side,  side); // 7
        texCoords.emplace_back(0.0f, 0.0f);
    }


public:
    IndexedLineList GetLines() const
    {
        return IndexedLineList{
            vertices,
            {
                0,1,  1,3,  3,2,  2,0,
                0,4,  1,5,	3,7,  2,6,
                4,5,  5,7,	7,6,  6,4
            }
        };
    }
    IndexedTriangleList<Vef3> GetTriangles() const
    {
        return IndexedTriangleList<Vef3>{
            vertices,
            {
                0,2,1,  2,3,1,
                1,3,5,  3,7,5,
                2,6,3,  3,6,7,
                4,5,7,  4,7,6,
                0,4,2,  2,4,6,
                0,1,4,  1,5,4
            }
        };
    }
    IndexedTriangleList<TextureVertex> GetTrianglesTextured() const
    {
        std::vector<TextureVertex> tverts;

        tverts.reserve(vertices.size());

        for (size_t i = 0ui64; i < vertices.size(); ++i)
        {
            tverts.emplace_back(vertices[i], texCoords[i]);
        }

        return IndexedTriangleList<TextureVertex>{
            std::move(tverts),
            {
                0,2,1,  2,3,1,
                1,3,5,  3,7,5,
                2,6,3,  3,6,7,
                4,5,7,  4,7,6,
                0,4,2,  2,4,6,
                0,1,4,  1,5,4
            }
        };
    }


private:
    std::vector<Vef3> vertices;
    std::vector<Vef2> texCoords;
};