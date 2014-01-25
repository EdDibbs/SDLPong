#include <iostream>
#include "cGameEngine.h"
#include "SDLFunctions.h"

cGameEngine::cGameEngine()
{
	std::cout << "cGameEngine constructing..." << std::endl;
	m_iFlag = 0;

	//initilize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
		Quit(1);
	}

	m_MainWindow = SDL_CreateWindow("SDLPong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, NULL);
	if (!m_MainWindow)
	{
		logSDLError(std::cout, "SDL_CreateWindow");
		Quit(2);
	}

	m_Renderer = SDL_CreateRenderer(m_MainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
	if (!m_Renderer)
	{
		logSDLError(std::cout, "SDL_CreateRenderer");
		Quit(3);
	}


	m_bRunning = true;
}

cGameEngine::~cGameEngine()
{
	std::cout << "cGameEngine destructing..." << std::endl;
}

cGameEngine::cGameEngine(const cGameEngine &other)
{
	//copy over our pointers.
	m_MainWindow = other.m_MainWindow;
	m_Renderer = other.m_Renderer;
}

cGameEngine& cGameEngine::operator=(const cGameEngine& rhs)
{
	//copy over our pointers.
	m_MainWindow = rhs.m_MainWindow;
	m_Renderer = rhs.m_Renderer;

	return *this;
}

void cGameEngine::HandleInput()
{
	if (!m_bRunning) return;

}

void cGameEngine::Update()
{
	if (!m_bRunning) return;

	//timer ticks and stuff
	m_uiTicks = SDL_GetTicks();
	if (m_uiTicks >= 5 * 1000)
		Quit(0);
}

void cGameEngine::Render()
{
	if (!m_bRunning) return;

	//clear the backbuffer
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);

	SDL_Rect Rectangle;
	Rectangle.h = 100;
	Rectangle.w = 100;
	Rectangle.x = m_uiTicks / 10;
	Rectangle.y = 100;

	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 255, 255);
	SDL_RenderDrawRect(m_Renderer, &Rectangle);



	//render the backbuffer
	SDL_RenderPresent(m_Renderer);
}

void cGameEngine::Quit(int Flag)
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_MainWindow);


	m_iFlag = Flag;
	m_bRunning = false;
}
