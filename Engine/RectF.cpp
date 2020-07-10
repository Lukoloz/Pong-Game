#include "RectF.h"

RectF::RectF(const float left_in, const float top_in, const float right_in, const float bottom_in)
	:
	left(left_in),
	top(top_in),
	right(right_in),
	bottom(bottom_in)
{
}

RectF::RectF(const Vec2 topLeft_in, const Vec2 bottomRight_in)
	:
	RectF(topLeft_in.x, topLeft_in.y, bottomRight_in.x, bottomRight_in.y)
{
}

RectF::RectF(const Vec2 topLeft_in, const float width_in, const float height_in)
	:
	RectF(topLeft_in, Vec2(topLeft_in.x + width_in, topLeft_in.y + height_in))
{
}

RectF RectF::GetRectCenter(const Vec2 center_in, const float halfWidth_in, const float halfHeight_in)
{
	return RectF(center_in.x - halfWidth_in, center_in.y - halfHeight_in,
		center_in.x + halfWidth_in, center_in.y + halfHeight_in);
}

bool RectF::IsOverlapping(const RectF& rect_in) const
{
	return left<rect_in.right&& right > rect_in.left
		&& top<rect_in.bottom&& bottom > rect_in.top;
}
