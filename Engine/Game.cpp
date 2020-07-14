/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	menu({ Graphics::ScreenWidth / 2, Graphics::ScreenHeight / 2 }),
	walls(0.0f,0.0f,(float)(Graphics::ScreenWidth-1),(float)(Graphics::ScreenHeight-1)),
	ball(Ball(Vec2(400.0f, 300.0f), Vec2(300.0f, 200.0f), Colors::White)),
	leftPaddle(RectF::RectFromCenter(Vec2(30.0f, 300.0f), 8.0f, 50.0f), Colors::White),
	rightPaddle(RectF::RectFromCenter(Vec2(770.0f, 300.0f), 8.0f, 50.0f), Colors::White),
	leftSound(L"Sounds\\ping.wav"),
	rightSound(L"Sounds\\pong.wav"),
	leftScore(0),
	rightScore(0)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	// fps stuff
	{
		//gfx.DrawCircle(400, 300, 290, Colors::Blue);
		int fps = 1.0f / dt;
		SpriteCodex::DrawNumber(gfx, Vec2(20, 30), Colors::White, fps / 10);
		SpriteCodex::DrawNumber(gfx, Vec2(55, 30), Colors::White, fps % 10);
	}

	switch (state)
	{
	case State::Menu:
	{
		switch (menu.Check(wnd.mouse.Read()))
		{
		case SelectionMenu::Gamemode::Offline:
			state = State::Offline;
			ball.Reset();
			leftPaddle.Reset();
			rightPaddle.Reset();
			leftScore = 0;
			rightScore = 0;
			break;
		case SelectionMenu::Gamemode::Online:
			//state = State::Online;
			break;
		default:
			break;
		}
		break;
	}
	case State::Offline:
	{
		if (wnd.kbd.KeyIsPressed('Q'))
		{
			state = State::Menu;
		}

		ball.Update(dt);

		Paddle::State kbdState = Paddle::State::IDLE;
		if (wnd.kbd.KeyIsPressed('W'))
		{
			kbdState = Paddle::State::UP;
		}
		else if (wnd.kbd.KeyIsPressed('S'))
		{
			kbdState = Paddle::State::DOWN;
		}
		leftPaddle.Update(kbdState, dt);
		leftPaddle.DoWallCollision(walls);
		if (leftPaddle.DoBallCollision(ball))
		{
			leftSound.Play();
		}

		kbdState = Paddle::State::IDLE;
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			kbdState = Paddle::State::UP;
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			kbdState = Paddle::State::DOWN;
		}
		rightPaddle.Update(kbdState, dt);
		rightPaddle.DoWallCollision(walls);
		if (rightPaddle.DoBallCollision(ball))
		{
		rightSound.Play();
		}

		Ball::BounceState bounceState = ball.DoWallCollision(walls);
		if (bounceState == Ball::BounceState::Left)
		{
			rightScore++;
			ball.Reset();
			leftPaddle.Reset();
			rightPaddle.Reset();
			if (rightScore >= winningScore)
			{
				leftScore = 0;
				rightScore = 0;
			}
			Sleep(200);
		}
		else if (bounceState == Ball::BounceState::Right)
		{
			leftScore++;
			ball.Reset();
			leftPaddle.Reset();
			rightPaddle.Reset();
			if (leftScore >= winningScore)
			{
				leftScore = 0;
				rightScore = 0;
			}
			Sleep(200);
		}
		break;
	}
	case State::Online:
	{
		break;
	}
	}
}

void Game::ComposeFrame()
{
	switch (state)
	{
	case State::Menu:
	{
		menu.Draw(gfx);
		break;
	}
	case State::Offline:
	{
		SpriteCodex::DrawNumber(gfx, Vec2(300, 50), Colors::Gray, leftScore);
		SpriteCodex::DrawNumber(gfx, Vec2(500, 50), Colors::Gray, rightScore);
		ball.Draw(gfx);
		leftPaddle.Draw(gfx);
		rightPaddle.Draw(gfx);
		break;
	}
	case State::Online:
	{
		break;
	}
	}

}
