#pragma once

#include "Vec3.hpp"
#include "IndexedLineList.hpp"
#include "IndexedTriangleList.hpp"
#include "TextureVertex.hpp"

#include <vector>
#include <stdexcept>

class CubeFolded
{
public:
    CubeFolded(float size)
    {
        const float side = size / 2.0f;
        vertices.emplace_back(-side, -side, -side); // 0
        texCoords.emplace_back(1.0f, 0.0f);

        vertices.emplace_back( side, -side, -side); // 1
        texCoords.emplace_back(0.0f, 0.0f);

        vertices.emplace_back(-side,  side, -side); // 2
        texCoords.emplace_back(1.0f, 1.0f);

        vertices.emplace_back( side,  side, -side); // 3
        texCoords.emplace_back(0.0f, 1.0f);

        vertices.emplace_back(-side, -side,  side); // 4
        texCoords.emplace_back(1.0f, 1.0f);

        vertices.emplace_back( side, -side,  side); // 5
        texCoords.emplace_back(0.0f, 1.0f);

        vertices.emplace_back(-side,  side,  side); // 6
        texCoords.emplace_back(1.0f, 0.0f);

        vertices.emplace_back( side,  side,  side); // 7
        texCoords.emplace_back(0.0f, 0.0f);

        vertices.emplace_back(-side, -side, -side); // 8
        texCoords.emplace_back(1.0f, 0.0f);

        vertices.emplace_back( side, -side, -side); // 9
        texCoords.emplace_back(0.0f, 0.0f);

        vertices.emplace_back(-side, -side, -side); // 10
        texCoords.emplace_back(0.0f, 1.0f);

        vertices.emplace_back(-side, -side,  side); // 11
        texCoords.emplace_back(0.0f, 0.0f);

        vertices.emplace_back( side, -side, -side); // 12
        texCoords.emplace_back(1.0f, 1.0f);

        vertices.emplace_back( side, -side,  side); // 13
        texCoords.emplace_back(1.0f, 0.0f);
    }
    IndexedLineList GetLines() const
    {
        throw std::runtime_error("Incomplete function CubeFolded::GetLines!");
        //return{
        //	vertices,{
        //		0,1,  1,3,  3,2,  2,0,
        //		0,4,  1,5,	3,7,  2,6,
        //		4,5,  5,7,	7,6,  6,4 }
        //};
    }
    IndexedTriangleList<Vef3> GetTriangles() const
    {
        return IndexedTriangleList<Vef3>{
            vertices,
            {
                0,2,1, 2,3,1,
                4,8,5, 5,8,9,
                2,6,3, 3,6,7,
                4,5,7, 4,7,6,
                2,10,11, 2,11,6,
                12,3,7, 12,7,13
            }
        };
    }
    IndexedTriangleList<TextureVertex> GetTrianglesTex() const
    {
        std::vector<TextureVertex> tverts;
        tverts.reserve(vertices.size());

        for (size_t i = 0; i < vertices.size(); i++)
        {
            tverts.emplace_back(vertices[i], texCoords[i]);
        }

        return IndexedTriangleList<TextureVertex>{
            std::move(tverts),
            {
                0,2,1, 2,3,1,
                4,8,5, 5,8,9,
                2,6,3, 3,6,7,
                4,5,7, 4,7,6,
                2,10,11, 2,11,6,
                12,3,7, 12,7,13
            }
        };
    }


private:
    std::vector<Vef3> vertices;
    std::vector<Vef2> texCoords;
};