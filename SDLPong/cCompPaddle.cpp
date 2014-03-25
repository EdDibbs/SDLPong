#include "cCompPaddle.h"
#include "Globals.h"
#include "cBall.h"
#include <random>

cCompPaddle::cCompPaddle()
{
	//m_PaddlePlayer.h = 40;
	//m_PaddlePlayer.w = 10;
	//m_PaddlePlayer.x = 10;
	//m_PaddlePlayer.y = TOP_OF_PLAYING_FIELD + 5;

	m_Rect.h = PongGlobals::PADDLE_HEIGHT;
	m_Rect.w = PongGlobals::PADDLE_WIDTH;
	m_Rect.x = PongGlobals::WINDOW_WIDTH - 10 - m_Rect.w;
	m_Rect.y = PongGlobals::TOP_OF_PLAYING_FIELD + 10;


}


void cCompPaddle::Update(cBall* Ball)
{
	SDL_Rect BallRect = Ball->GetRect();
	//int BallXVel = Ball->GetXVel() * Ball->GetXDir();
	//int BallYVel = Ball->GetYVel() * Ball->GetYDir();

	if (BallRect.x < PongGlobals::WINDOW_WIDTH / 5) return;	//don't bother moving if the ball is on player side

	int PaddleSpeed = PongGlobals::PLAYER_MOVE_SPEED - 1;
	if (rand() % 10 != 0) //don't move occasionally
		if (m_Rect.y > BallRect.y) m_Rect.y -= PaddleSpeed;
		else if (m_Rect.y + m_Rect.h < BallRect.y) m_Rect.y += PaddleSpeed;


}

