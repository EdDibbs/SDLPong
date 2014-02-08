#include "cBall.h"
#include "Globals.h"

cBall::cBall()
{

	m_iXvelocity = 3;
	m_iYvelocity = 5;

	m_Rect.h = 10;
	m_Rect.w = 10;
	m_Rect.x = 0;
	m_Rect.y = 0;

}

cBall::~cBall()
{
	m_Rect.h = 5;
	m_Rect.w = 5;
	m_Rect.x = 0;
	m_Rect.y = 0;
	m_iXvelocity = 0;
	m_iYvelocity = 0;
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
		m_iXvelocity *= -1; //TODO: add some randomness here
	}
	else
	{
		m_iYvelocity *= -1;
	}
}

void cBall::Update()
{
	m_Rect.x += m_iXvelocity;
	m_Rect.y += m_iYvelocity;
	
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

	if (m_Rect.y < 0) //if we go off the top of the screen
	{
		m_Rect.y = 0;
		Bounce(false);
	}
	else if (m_Rect.y + m_Rect.h > WINDOW_HEIGHT) //if we go off on the bottom of the screen
	{
		m_Rect.y = WINDOW_HEIGHT - m_Rect.h;
		Bounce(false);
	}
}