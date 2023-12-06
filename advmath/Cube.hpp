#pragma once

#include "IndexedLineList.hpp"
#include "IndexedTriangleList.hpp"

class Cube
{
public:
	Cube(float size)
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
			vertices,
			{
				0,1,  1,3,  3,2,  2,0,
				0,4,  1,5,	3,7,  2,6,
				4,5,  5,7,	7,6,  6,4
			}
		};
	}
	IndexedTriangleList GetTriangles() const
	{
		return IndexedTriangleList{
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


private:
	std::vector<Vef3> vertices;
};