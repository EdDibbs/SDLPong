#include "cBall.h"
#include "Globals.h"
#include <stdlib.h>

cBall::cBall()
{

	m_iXvelocity = 3;
	m_iYvelocity = 5;
	m_iXdir = 1;
	m_iYdir = 1;

	m_Rect.h = 10;
	m_Rect.w = 10;
	m_Rect.x = 5;
	m_Rect.y = TOP_OF_PLAYING_FIELD + 5;

}

cBall::~cBall()
{
	m_Rect.h = 0;
	m_Rect.w = 0;
	m_Rect.x = 0;
	m_Rect.y = 0;
	m_iXvelocity = 0;
	m_iYvelocity = 0;
	m_iXdir = 0;
	m_iYdir = 0;

}

cBall::cBall(const cBall &other)
{
	m_Rect.x = other.m_Rect.x;
	m_Rect.y = other.m_Rect.y;
	m_iXvelocity = other.m_iXvelocity;
	m_iYvelocity = other.m_iYvelocity;
}


void cBall::Bounce(bool xAxis)
{
	
	if (xAxis)
	{
		m_iXdir *= -1;
		m_iXvelocity = 2 + rand() % 3; //TODO: add some randomness here
	}
	else
	{
		m_iYdir *= -1;
		m_iYvelocity = 2 + rand() % 3;
	}
}

void cBall::Update()
{
	m_Rect.x += (int)m_iXvelocity * m_iXdir;
	m_Rect.y += (int)m_iYvelocity * m_iYdir;
	
	if (m_Rect.x < 0)
	{
		m_Rect.x = 0;
		Bounce(true);
	}
	else if (m_Rect.x + m_Rect.w > WINDOW_WIDTH)
	{
		m_Rect.x = WINDOW_WIDTH - m_Rect.w;
		Bounce(true);
	}

	if (m_Rect.y < TOP_OF_PLAYING_FIELD) //if we go off the top of the screen
	{
		m_Rect.y = TOP_OF_PLAYING_FIELD;
		Bounce(false);
	}
	else if (m_Rect.y + m_Rect.h > WINDOW_HEIGHT) //if we go off on the bottom of the screen
	{
		m_Rect.y = WINDOW_HEIGHT - m_Rect.h;
		Bounce(false);
	}
}