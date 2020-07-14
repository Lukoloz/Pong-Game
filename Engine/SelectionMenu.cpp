#include "SelectionMenu.h"

SelectionMenu::Box::Box(const Gamemode gm_in, const Vec2& pos_in)
	:
	gamemode(gm_in),
	rect(RectF::RectFromCenter(pos_in, boxWidth / 2, boxHeight / 2))
{
}

bool SelectionMenu::Box::IsInside(const Vec2& screenPos) const
{
	return rect.left <= screenPos.x && screenPos.x <= rect.right
		&& rect.top <= screenPos.y && screenPos.y <= rect.bottom;
}

void SelectionMenu::Box::SetHightlight()
{
	isHighlighted = true;
}

void SelectionMenu::Box::ResetHightlight()
{
	isHighlighted = false;
}

bool SelectionMenu::Box::IsHightlighted() const
{
	return isHighlighted;
}

SelectionMenu::Gamemode SelectionMenu::Box::GetGamemode() const
{
	return gamemode;
}

void SelectionMenu::Box::Draw(Graphics& gfx) const
{
	switch (gamemode)
	{
	case Gamemode::Offline:
		SpriteCodex::DrawOffline(gfx, rect.GetCenter(), Colors::White);
		break;
	case Gamemode::Online:
		SpriteCodex::DrawOnline(gfx, rect.GetCenter(), Colors::White);
		break;
	}
	if (IsHightlighted())
	{
		gfx.DrawFrame(rect, highlightThickness, highlightColor);
	}
}

SelectionMenu::SelectionMenu(const Vec2& pos_in)
	:
	sound(L"Sounds\\menu.wav")
{
	Vec2 center = pos_in;
	for (int i = 0; i < int(Gamemode::Count); i++)
	{
		boxes[i] = { Gamemode(i), center };
		center.y += verticalSpacing;
	}
}

SelectionMenu::Gamemode SelectionMenu::Check(const Mouse::Event& e)
{
	switch (e.GetType())
	{
	case Mouse::Event::Type::Move:
	{
		for (auto& b : boxes)
		{
			if (b.IsInside(e.GetPos()))
			{
				if (!b.IsHightlighted())
				{
					sound.Play();
					ResetHightlights();
					b.SetHightlight();
				}
				return Gamemode::Invalid;
			}
		}
		ResetHightlights();
		break;
	}
	case Mouse::Event::Type::LPress:
	{
		for (auto& b : boxes)
		{
			if (b.IsInside(e.GetPos()))
			{
				return b.GetGamemode();
			}
		}
		break;
	}
	}

	return Gamemode::Invalid;
}

void SelectionMenu::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawLogo(gfx, Vec2(Graphics::ScreenWidth / 2, 120), Colors::White);
	SpriteCodex::DrawMadeBy(gfx, Vec2(675, 570), Colors::White);
	for (auto& b : boxes)
	{
		b.Draw(gfx);
	}
	
}

void SelectionMenu::ResetHightlights()
{
	for (auto& b : boxes)
	{
		b.ResetHightlight();
	}
}
