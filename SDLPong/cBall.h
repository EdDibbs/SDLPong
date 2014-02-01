#pragma once
#include <SDL.h>

class cBall
{
public:
	cBall();	//constructor
	~cBall();	//destructor
	cBall(const cBall &other);	//copy constructor

	void Bounce(bool xAxis); //true if bounce occured on X movement
	void Update();
	SDL_Rect GetRect() { return m_Rect; }


private:
	int m_iXvelocity, m_iYvelocity;
	SDL_Rect m_Rect;


};