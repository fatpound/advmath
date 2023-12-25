#pragma once

#include "Vec3.hpp"
#include "IndexedLineList.hpp"
#include "IndexedTriangleList.hpp"
#include "TextureVertex.hpp"

#include <vector>
#include <stdexcept>

class CubeSkinned
{
public:
    CubeSkinned(float size)
    {
        const float side = size / 2.0f;
        const auto ConvertTexCoord = [](float u, float v)
        {
            return Vef2{ (u + 1.0f) / 3.0f,v / 4.0f };
        };

        vertices.emplace_back(-side, -side, -side); // 0
        tc.emplace_back(ConvertTexCoord(1.0f, 0.0f));

        vertices.emplace_back( side, -side, -side); // 1
        tc.emplace_back(ConvertTexCoord(0.0f, 0.0f));

        vertices.emplace_back(-side,  side, -side); // 2
        tc.emplace_back(ConvertTexCoord(1.0f, 1.0f));

        vertices.emplace_back( side,  side, -side); // 3
        tc.emplace_back(ConvertTexCoord(0.0f, 1.0f));

        vertices.emplace_back(-side, -side,  side); // 4
        tc.emplace_back(ConvertTexCoord(1.0f, 3.0f));

        vertices.emplace_back( side, -side,  side); // 5
        tc.emplace_back(ConvertTexCoord(0.0f, 3.0f));

        vertices.emplace_back(-side,  side,  side); // 6
        tc.emplace_back(ConvertTexCoord(1.0f, 2.0f));

        vertices.emplace_back( side,  side,  side); // 7
        tc.emplace_back(ConvertTexCoord(0.0f, 2.0f));

        vertices.emplace_back(-side, -side, -side); // 8
        tc.emplace_back(ConvertTexCoord(1.0f, 4.0f));

        vertices.emplace_back( side, -side, -side); // 9
        tc.emplace_back(ConvertTexCoord(0.0f, 4.0f));

        vertices.emplace_back(-side, -side, -side); // 10
        tc.emplace_back(ConvertTexCoord(2.0f, 1.0f));

        vertices.emplace_back(-side, -side,  side); // 11
        tc.emplace_back(ConvertTexCoord(2.0f, 2.0f));

        vertices.emplace_back( side, -side, -side); // 12
        tc.emplace_back(ConvertTexCoord(-1.0f, 1.0f));

        vertices.emplace_back( side, -side,  side); // 13
        tc.emplace_back(ConvertTexCoord(-1.0f, 2.0f));
    }


public:
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
            tverts.emplace_back(vertices[i], tc[i]);
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
    std::vector<Vef2> tc;
};