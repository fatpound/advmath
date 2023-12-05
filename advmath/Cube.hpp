#pragma once

#include "IndexedLineList.hpp"

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


private:
	std::vector<Vef3> vertices;
};