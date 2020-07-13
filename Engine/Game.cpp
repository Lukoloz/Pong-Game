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
	walls(0.0f,0.0f,(float)(Graphics::ScreenWidth-1),(float)(Graphics::ScreenHeight-1)),
	ball(Ball(Vec2(400.0f, 300.0f), Vec2(300.0f, 200.0f), Colors::White)),
	leftPaddle(RectF::GetRectCenter(Vec2(30.0f, 300.0f), 8.0f, 50.0f), Colors::White),
	rightPaddle(RectF::GetRectCenter(Vec2(770.0f, 300.0f), 8.0f, 50.0f), Colors::White),
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
	leftPaddle.DoBallCollision(ball);

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
	rightPaddle.DoBallCollision(ball);

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
}

void Game::ComposeFrame()
{
	SpriteCodex::DrawNumber(gfx, Vec2(300, 50), Colors::LightGray, leftScore);
	SpriteCodex::DrawNumber(gfx, Vec2(500, 50), Colors::LightGray, rightScore);
	ball.Draw(gfx);
	leftPaddle.Draw(gfx);
	rightPaddle.Draw(gfx);
}
