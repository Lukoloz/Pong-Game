#pragma once
#include "RectF.h"
#include "Vec2.h"
#include "Colors.h"
#include "Keyboard.h"
#include "Graphics.h"
#include "Ball.h"
#include "Sound.h"

class Paddle
{
public:
	Paddle(const RectF& rect_in, const Color c_in);
	void Update(const Keyboard& kbd, const float dt);
	bool DoWallCollision(const RectF& walls);
	bool DoBallCollision(Ball& ball);
	void Draw(Graphics& gfx) const;
	void SoundPlay();
private:
	Sound sound;
	const float speed;
	Vec2 vel;
	RectF rect;
	Color c;
};