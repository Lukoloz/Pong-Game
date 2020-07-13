#include "Ball.h"
#include <random>

Ball::Ball(const Vec2& pos_in, const Vec2& dir_in, const Color c_in)
	:
	speedReset(240.0f),
	speed(240.0f),
	posReset(pos_in),
	pos(pos_in),
	dir(dir_in.GetNormalized()),
	c(c_in)
{
}

void Ball::Reset()
{
	speed = speedReset;
	pos = posReset;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> yDist(-1.0f * Ball::maxDirY, Ball::maxDirY);
	std::uniform_int_distribution<int> negpos(0, 1);

	dir.y = yDist(rng);
	dir.x = sqrt(1 - dir.y * dir.y);
	if (negpos(rng) == 1) dir.x *= -1.0f;
}

void Ball::Update(const float dt)
{
	pos += GetVel() * dt;
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
	return dir * speed;
}

Vec2 Ball::GetDir() const
{
	return dir;
}

void Ball::SetPos(const Vec2& pos_in)
{
	pos = pos_in;
}

void Ball::ChangeDirection(const Vec2& vel_in)
{
	if (abs(vel_in.GetNormalized().x) > 0.5f)
	{
		dir = vel_in.GetNormalized();
	}
}

void Ball::ChangeDirectionY(float dy)
{
	if (abs(dir.y + dy) < Ball::maxDirY)
	{
		float posneg;
		if (dir.x < 0) posneg = -1.0f;
		else posneg = 1.0f;
		dir = Vec2(sqrt(1 - (dir.y + dy) * (dir.y + dy)) * posneg, dir.y + dy);
	}
}

Ball::BounceState Ball::DoWallCollision(const RectF& walls)
{
	RectF rect = RectF::GetRectCenter(pos, rad, rad);
	BounceState state = BounceState::Nevermind;

	if (rect.left < walls.left)
	{
		pos.x = walls.left + rad;
		ReboundX();
		state = BounceState::Left;
	}
	else if (rect.right > walls.right)
	{
		pos.x = walls.right - rad;
		ReboundX();
		state = BounceState::Right;
	}

	if (rect.top < walls.top)
	{
		pos.y = walls.top + rad;
		ReboundY();
		state = BounceState::Horizontal;
	}
	else if (rect.bottom > walls.bottom)
	{
		pos.y = walls.bottom - rad;
		ReboundY();
		state = BounceState::Horizontal;
	}

	return state;
}

void Ball::ReboundX()
{
	dir.x *= -1;
}

void Ball::ReboundY()
{
	dir.y *= -1;
}

void Ball::SpeedUp()
{
	speed *= 1.05f;
}

void Ball::Draw(Graphics& gfx)
{
	SpriteCodex::DrawBall(gfx, pos, c);
}
