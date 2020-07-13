#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
#include "SpriteCodex.h"

class Ball
{
public:
	enum class BounceState
	{
		Nevermind,
		Horizontal,
		Left,
		Right
	};
public:
	Ball(const Vec2& pos_in, const Vec2& dir_in, const Color c_in);
	void Reset();
	void Update(const float dt);
	RectF GetRect() const;
	Vec2 GetPos() const;
	Vec2 GetVel() const;
	Vec2 GetDir() const;
	void SetPos(const Vec2& pos_in);
	void ChangeDirection(const Vec2& vel_in);
	void ChangeDirectionY(float dy);
	BounceState DoWallCollision(const RectF& walls);
	void ReboundX();
	void ReboundY();
	void SpeedUp();
	void Draw(Graphics& gfx);
private:
	static constexpr float maxDirY = 0.8f;
	const float rad = 7.0f;
	const float speedReset;
	float speed;
	Color c;
	const Vec2 posReset;
	Vec2 pos;
	Vec2 dir;
};