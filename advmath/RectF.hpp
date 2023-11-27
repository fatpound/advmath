#pragma once

#include "Vec2.hpp"

class RectF
{
public:
	RectF() = default;

	RectF(float left_in, float right_in, float top_in, float bottom_in);
	RectF(const Vef2& topLeft, float width, float height);
	RectF(const Vef2& topLeft, const Vef2& bottomRight);


public:
	static RectF FromCenter(const Vef2& center, float halfWidth, float halfHeight);
	RectF GetExpanded(float offset) const;

	Vef2 GetCenter() const;

	bool IsOverlappingWith(const RectF& other) const;
	bool IsContainedBy(const RectF& other) const;


public:
	float left;
	float right;
	float top;
	float bottom;
};