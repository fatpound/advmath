#include "RectF.hpp"

RectF::RectF(float in_left, float in_right, float in_top, float in_bottom)
	:
	left( in_left ),
	right( in_right ),
	top( in_top ),
	bottom( in_bottom )
{

}
RectF::RectF(const Vef2& topLeft, const Vef2& bottomRight)
	:
	RectF(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{

}
RectF::RectF(const Vef2& topLeft, float width, float height)
	:
    RectF(topLeft, topLeft + Vef2{ width, height })
{

}

RectF RectF::FromCenter(const Vef2& center, float halfWidth, float halfHeight)
{
	const Vef2 half(halfWidth,halfHeight);

	return RectF(center - half, center + half);
}
RectF RectF::GetExpanded(float offset) const
{
	return RectF(left - offset, right + offset, top - offset, bottom + offset);
}

Vef2 RectF::GetCenter() const
{
    return Vef2{ (left + right) / 2.0f, (top + bottom) / 2.0f };
}

bool RectF::IsOverlappingWith(const RectF& other) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}
bool RectF::IsContainedBy(const RectF& other) const
{
	return left >= other.left && right <= other.right &&
		top >= other.top && bottom <= other.bottom;
}