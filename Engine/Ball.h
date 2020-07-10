#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
#include "SpriteCodex.h"

class Ball
{
public:
	Ball(const Vec2& pos_in, const Vec2& vel_in);
	void Update(const float dt);
	RectF GetRect() const;
	Vec2 GetPos() const;
	Vec2 GetVel() const;
	void SetPos(const Vec2& pos_in);
	void ChangeDirection(const Vec2& vel_in);
	bool DoWallCollision(const RectF& walls);
	void ReboundX();
	void ReboundY();
	void Draw(Graphics& gfx);
private:
	const float rad = 7.0f;
	Vec2 pos;
	Vec2 vel;
};