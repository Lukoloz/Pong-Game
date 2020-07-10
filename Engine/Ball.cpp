#include "Ball.h"

Ball::Ball(const Vec2& pos_in, const Vec2& vel_in)
	:
	pos(pos_in),
	vel(vel_in)
{
}

void Ball::Update(const float dt)
{
	pos += vel * dt;
}

RectF Ball::GetRect() const
{
	return RectF::GetRectCenter(pos, rad, rad);
}

Vec2 Ball::GetPos() const
{
	return pos;
}

Vec2 Ball::GetVel() const
{
	return vel;
}

void Ball::SetPos(const Vec2& pos_in)
{
	pos = pos_in;
}

void Ball::ChangeDirection(const Vec2& vel_in)
{
	vel = vel_in.GetNormalized() * vel.GetLength();
}

bool Ball::DoWallCollision(const RectF& walls)
{
	RectF rect = RectF::GetRectCenter(pos, rad, rad);
	bool collided = false;

	if (rect.left < walls.left)
	{
		pos.x = walls.left + rad;
		ReboundX();
		collided = true;
	}
	else if (rect.right > walls.right)
	{
		pos.x = walls.right - rad;
		ReboundX();
		collided = true;
	}
	if (rect.top < walls.top)
	{
		pos.y = walls.top + rad;
		ReboundY();
		collided = true;
	}
	else if (rect.bottom > walls.bottom)
	{
		pos.y = walls.bottom - rad;
		ReboundY();
		collided = true;
	}

	return collided;
}

void Ball::ReboundX()
{
	vel.x *= -1;
}

void Ball::ReboundY()
{
	vel.y *= -1;
}

void Ball::Draw(Graphics& gfx)
{
	SpriteCodex::DrawBall(pos, gfx);
}
