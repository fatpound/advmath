#pragma once

#include "Entity.hpp"

#include <numbers>

class Star : public Entity
{
public:
    Star(Vef2 pos, float outerRadius, float innerRatio, size_t flareCount, Color color)
        :
        Entity(Make(outerRadius, outerRadius * innerRatio), pos, color),
        radius(outerRadius)
    {

    }


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

    float GetRadius() const
    {
        return radius;
    }


private:
    float radius;
};