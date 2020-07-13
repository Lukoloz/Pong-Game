#pragma once
#include "Graphics.h"
#include "Colors.h"
#include "Vec2.h"
class SpriteCodex
{
public:
	static void DrawBall(Graphics& gfx, Vec2& pos, Color c);
	static void DrawNumber(Graphics& gfx, Vec2& pos, Color c, int n);
	static void Draw0(Graphics& gfx, Vec2& pos, Color c);
	static void Draw1(Graphics& gfx, Vec2& pos, Color c);
	static void Draw2(Graphics& gfx, Vec2& pos, Color c);
	static void Draw3(Graphics& gfx, Vec2& pos, Color c);
	static void Draw4(Graphics& gfx, Vec2& pos, Color c);
	static void Draw5(Graphics& gfx, Vec2& pos, Color c);
	static void Draw6(Graphics& gfx, Vec2& pos, Color c);
	static void Draw7(Graphics& gfx, Vec2& pos, Color c);
	static void Draw8(Graphics& gfx, Vec2& pos, Color c);
	static void Draw9(Graphics& gfx, Vec2& pos, Color c);
	static void DrawAllNumbers(Graphics& gfx, Vec2& pos, Color c);
	static void DrawOffline(Graphics& gfx, Vec2& pos, Color c);
};