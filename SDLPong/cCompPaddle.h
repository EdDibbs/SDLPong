#pragma once
#include <SDL.h>
class cBall;

//The computer controlled paddle
class cCompPaddle
{
public:
	cCompPaddle();
	~cCompPaddle() {}

	void Update(cBall* Ball); //pass the ball object to the comp and it'll decide how to move
	SDL_Rect GetRect() { return m_Rect; }
	void SetX(int x) { m_Rect.x = x; }
	void SetY(int y) { m_Rect.y = y; }
private:
	SDL_Rect m_Rect;
};
