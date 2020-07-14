#include "Paddle.h"

Paddle::Paddle(const RectF& rect_in, const Color c_in)
	:
	speedReset(240.0f),
	speed(240.0f),
	vel(0.0f, 0.0f),
	rectReset(rect_in),
	rect(rect_in),
	c(c_in)
{
}

void Paddle::Reset()
{
	speed = speedReset;
	rect = rectReset;
}

void Paddle::Update(const Paddle::State& state, const float dt)
{
	vel = { 0.0f,0.0f };
	switch (state)
	{
	case State::UP:
		vel.y = -speed;
		rect.top -= speed * dt;
		rect.bottom -= speed * dt;
		break;
	case State::DOWN:
		vel.y = speed;
		rect.top += speed * dt;
		rect.bottom += speed * dt;
		break;
	default:
		break;
	}
}

bool Paddle::DoWallCollision(const RectF& walls)
{
	bool collided = false;
	if (rect.top < walls.top)
	{
		float delta = walls.top - rect.top;
		rect.top += delta;
		rect.bottom += delta;
		collided = true;
	}
	else if (rect.bottom > walls.bottom)
	{
		float delta = walls.bottom - rect.bottom;
		rect.top += delta;
		rect.bottom += delta;
		collided = true;
	}
	return collided;
}

bool Paddle::DoBallCollision(Ball& ball)
{
	if (rect.IsOverlapping(ball.GetRect()))
	{
		RectF ballRect = ball.GetRect();
		Vec2 ballVel = ball.GetVel();
		Vec2 difVel = ballVel - (vel * 0.5f);
		float agoX = INFINITE;
		float deltaX;
		float agoY = INFINITE;
		float deltaY;

		if (difVel.x < 0.0f)
		{
			agoX = (ballRect.left - rect.right) / difVel.x;
			deltaX = ballRect.left - rect.right;
		}
		else if (difVel.x > 0.0f)
		{
			agoX = (ballRect.right - rect.left) / difVel.x;
			deltaX = ballRect.right - rect.left;
		}
		if (difVel.y < 0.0f)
		{
			agoY = (ballRect.top - rect.bottom) / difVel.y;
			deltaY = ballRect.top - rect.bottom;
		}
		else if (difVel.y > 0.0f)
		{
			agoY = (ballRect.bottom - rect.top) / difVel.y;
			deltaY = ballRect.bottom - rect.top;
		}

		if (agoX < agoY)
		{
			if (vel.y < 0)
			{
				ball.ChangeDirectionY(0.4f);
			}
			else if (vel.y > 0)
			{
				ball.ChangeDirectionY(-0.4f);
			}
			ball.ReboundX();
			ball.SetPos(Vec2(ball.GetPos().x - deltaX, ball.GetPos().y));
		}
		else
		{
			ball.ReboundY();
			ball.SetPos(Vec2(ball.GetPos().x, ball.GetPos().y - deltaY));
		}
		ball.SpeedUp();
		SpeedUp();
		return true;
	}
	return false;
}

bool Paddle::IsActive() const
{
	return isActive;
}

void Paddle::Activate()
{
	isActive = true;
}

void Paddle::Deactivate()
{
	isActive = false;
}

void Paddle::SpeedUp()
{
	speed *= 1.1f;
}

void Paddle::Draw(Graphics& gfx) const
{
	gfx.DrawRect(rect, c);
	/*
	// shadows
	gfx.DrawRect(RectF(rect.right - 4.0f, rect.top, rect.right, rect.bottom),
		Colors::MakeRGB(c.GetR() - 20u, c.GetG() - 20u, c.GetB() - 20u));
	gfx.DrawRect(RectF(rect.left, rect.bottom - 4.0f, rect.right, rect.bottom),
		Colors::MakeRGB(c.GetR() - 20u, c.GetG() - 20u, c.GetB() - 20u));
	// lights
	gfx.DrawRect(RectF(rect.left, rect.top, rect.left + 4.0f, rect.bottom),
		Colors::MakeRGB(c.GetR() + 20u, c.GetG() + 20u, c.GetB() + 20u));
	gfx.DrawRect(RectF(rect.left, rect.top, rect.right, rect.top + 4.0f),
		Colors::MakeRGB(c.GetR() + 20u, c.GetG() + 20u, c.GetB() + 20u));
	// shadows in corners
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < x; y++)
		{
			gfx.PutPixel(int(rect.right) - 4 + x, int(rect.top) + 3 - y,
				Colors::MakeRGB(c.GetR() - 20u, c.GetG() - 20u, c.GetB() - 20u));
			gfx.PutPixel(int(rect.left) + x, int(rect.bottom) - 1 - y,
				Colors::MakeRGB(c.GetR() - 20u, c.GetG() - 20u, c.GetB() - 20u));
		}
	}
	*/
}