#include "Paddle.h"

Paddle::Paddle(const RectF& rect_in, const Color c_in)
	:
	sound(L"Sounds\\arkpad.wav"),
	speed(240.0f),
	vel(0.0f, 0.0f),
	rect(rect_in),
	c(c_in)
{
}

void Paddle::Update(const Keyboard& kbd, const float dt)
{
	vel = { 0.0f,0.0f };
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		vel.x = -speed;
		rect.left -= speed * dt;
		rect.right -= speed * dt;
	}
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		vel.x = speed;
		rect.left += speed * dt;
		rect.right += speed * dt;
	}
}

bool Paddle::DoWallCollision(const RectF& walls)
{
	bool collided = false;
	if (rect.left < walls.left)
	{
		float delta = walls.left - rect.left;
		rect.left += delta;
		rect.right += delta;
		collided = true;
	}
	else if (rect.right > walls.right)
	{
		float delta = walls.right - rect.right;
		rect.left += delta;
		rect.right += delta;
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
			ball.ChangeDirection(difVel);
			ball.ReboundX();
			ball.SetPos(Vec2(ball.GetPos().x - deltaX, ball.GetPos().y));
		}
		else
		{
			ball.ChangeDirection(difVel);
			ball.ReboundY();
			ball.SetPos(Vec2(ball.GetPos().x, ball.GetPos().y - deltaY));
		}

		SoundPlay();
		return true;
	}
	return false;
}

void Paddle::Draw(Graphics& gfx) const
{
	gfx.DrawRect(rect, c);
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
}

void Paddle::SoundPlay()
{
	sound.Play();
}
