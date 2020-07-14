#pragma once
#include "Vec2.h"
#include "Colors.h"

class RectF
{
public:
	RectF() = default;
	RectF(const float left_in, const float top_in, const float right_in, const float bottom_in);
	RectF(const Vec2 topLeft_in, const Vec2 bottomRight_in);
	RectF(const Vec2 topLeft_in, const float width_in, const float height_in);
	Vec2 GetCenter() const;
	static RectF RectFromCenter(const Vec2 center_in, const float halfWidth_in, const float halfHeight_in);
	bool IsOverlapping(const RectF& rect_in) const;
public:
	float left;
	float top;
	float right;
	float bottom;
};