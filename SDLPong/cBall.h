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
	const SDL_Rect GetRect() { return m_Rect; }
	void Set(int xPos, int yPos) { m_Rect.x = xPos, m_Rect.y = yPos; }

private:
	int m_iXvelocity, m_iYvelocity;
	int m_iXdir, m_iYdir;
	SDL_Rect m_Rect;


};