#pragma once
#include "RectF.h"
#include "Vec2.h"
#include "Colors.h"
#include "Keyboard.h"
#include "Graphics.h"
#include "Ball.h"

class Paddle
{
public:
	enum class State
	{
		UP,
		DOWN,
		IDLE
	};
public:
	Paddle(const RectF& rect_in, const Color c_in);
	void Reset();
	void Update(const State& state, const float dt);
	bool DoWallCollision(const RectF& walls);
	bool DoBallCollision(Ball& ball);
	void SpeedUp();
	void Draw(Graphics& gfx) const;
private:
	const float speedReset;
	float speed;
	Vec2 vel;
	const RectF rectReset;
	RectF rect;
	Color c;
};