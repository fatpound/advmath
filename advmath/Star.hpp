#pragma once

#include "Vec2.hpp"

#include <vector>
#include <numbers>

class Star
{
public:
	static std::vector<Vef2> Make(float outerRadius, float innerRadius, size_t nFlares = 5)
	{
		std::vector<Vef2> star;

        const size_t vertexCount = nFlares * 2;
		star.reserve(vertexCount);

		const float theta = 2.0f * std::numbers::pi_v<float> / static_cast<float>(vertexCount);

		for (size_t i = 0; i < vertexCount; ++i)
		{
			const float radius = 
                i % 2 == 0
                ? outerRadius
                : innerRadius
                ;
            
			star.emplace_back(
                radius * std::cos( static_cast<float>(i) * theta ),
                radius * std::sin( static_cast<float>(i) * theta )
			);
		}

		return star;
	}
};