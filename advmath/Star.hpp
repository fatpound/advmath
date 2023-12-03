#pragma once

#include "Entity.hpp"

#include <numbers>

class Star : public Entity
{
public:
	Star(Vef2 pos, float outerRadius, float innerRatio, size_t flareCount, Color in_baseColor, float in_rotationSpeed, float in_colorFrequencyFactor, float in_colorPhase)
		:
		Entity(Make(outerRadius, outerRadius* innerRatio), pos, baseColor),
		baseColor(in_baseColor),
        radius(outerRadius),
        rotationSpeed(in_rotationSpeed),
		colorFrequencyFactor(in_colorFrequencyFactor),
		colorPhase(in_colorPhase)
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

    void Update(float deltaTime)
    {
        totalTime += deltaTime;

        UpdateRotation();
		UpdateColor();
    }


private:
	void UpdateColor()
	{
		const int offset = static_cast<int>(127.0f * std::sin(colorFrequencyFactor * totalTime + colorPhase)) + 128;

		Color col;

		col.SetR(std::min(baseColor.GetR() + offset, 255));
		col.SetG(std::min(baseColor.GetG() + offset, 255));
		col.SetB(std::min(baseColor.GetB() + offset, 255));

		SetColor(col);
	}
    void UpdateRotation()
    {
        SetAngle(rotationSpeed * totalTime);
    }


private:
	Color baseColor;

    float radius;
    float rotationSpeed;

	float colorFrequencyFactor;
	float colorPhase;

    float totalTime = 0.0f;
};