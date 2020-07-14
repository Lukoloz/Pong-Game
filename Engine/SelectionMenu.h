#pragma once
#include "RectF.h"
#include "Vec2.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Mouse.h"
#include "Sound.h"

class SelectionMenu
{
public:
	enum class Gamemode
	{
		Offline,
		Online,
		Count,
		Invalid
	};
private:
	class Box
	{
	public:
		Box() = default;
		Box(const SelectionMenu::Gamemode gm_in, const Vec2& pos_in);
		bool IsInside(const Vec2& screenPos) const;
		void SetHightlight();
		void ResetHightlight();
		bool IsHightlighted() const;
		Gamemode GetGamemode() const;
		void Draw(Graphics& gfx) const;
	private:
		static constexpr int highlightThickness = 6;
		static constexpr Color highlightColor = Colors::Yellow;
		Gamemode gamemode;
		RectF rect;
		bool isHighlighted = false;
	};
public:
	SelectionMenu(const Vec2& pos_in);	
	Gamemode Check(const Mouse::Event& e);
	void Draw(Graphics& gfx) const;
private:
	void ResetHightlights();
private:
	static constexpr float boxWidth = 500.0f;
	static constexpr float boxHeight = 100.0f;
	static constexpr float verticalSpacing = boxHeight * 1.5f;
	Sound sound;
	Box boxes[int(Gamemode::Count)];
};