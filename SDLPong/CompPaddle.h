#pragma once
#include <SDL.h>
class cBall;

//The computer controlled paddle
class CompPaddle
{
public:
	CompPaddle();
	~CompPaddle() {}

	void Update(cBall* Ball); //pass the ball object to the comp and it'll decide how to move

private:
	SDL_Rect m_Rect;
};
