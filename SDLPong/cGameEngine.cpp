#include <iostream>
#include "cGameEngine.h"
#include "SDLFunctions.h"




cGameEngine::cGameEngine()
{
	std::cout << "cGameEngine constructing..." << std::endl;
	m_iFlag = 0;
	m_bRunning = true;

	//initilize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
		Quit(1);
	}

	m_MainWindow = SDL_CreateWindow("SDLPong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, NULL);
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


	m_PaddlePlayer.h = 40;
	m_PaddlePlayer.w = 10;
	m_PaddlePlayer.x = 10;
	m_PaddlePlayer.y = 0 + 5;

	m_PaddleComp.h = 40;
	m_PaddleComp.w = 10;
	m_PaddleComp.x = WINDOW_WIDTH - m_PaddleComp.w - 10;
	m_PaddleComp.y = 0 + 5;


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

	while (SDL_PollEvent(&m_Event))
	{
		if (m_Event.type == SDL_QUIT)
		{
			Quit(0);
			return;
		}

		else if (m_Event.type == SDL_KEYDOWN || m_Event.type == SDL_KEYUP)
		{
			bool KeyDown = false;
			if (m_Event.type == SDL_KEYDOWN)
				KeyDown = true;


			switch (m_Event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				Quit(0);
				break;
			case SDLK_UP:
				m_Keys[KEY_UP] = KeyDown;
				break;
			case SDLK_DOWN:
				m_Keys[KEY_DOWN] = KeyDown;
				break;
			}
		}
	}
}

void cGameEngine::Update()
{
	if (!m_bRunning) return;
	//timer ticks and stuff
	m_uiTicks = SDL_GetTicks();


	if (m_Keys[KEY_UP])
	{
		m_PaddlePlayer.y -= PLAYER_MOVE_SPEED;
	}
	if (m_Keys[KEY_DOWN])
	{
		m_PaddlePlayer.y += PLAYER_MOVE_SPEED;
	}



	if (m_PaddlePlayer.y < 0)
		m_PaddlePlayer.y = 0;
	else if (m_PaddlePlayer.y + m_PaddlePlayer.h >= WINDOW_HEIGHT)
		m_PaddlePlayer.y = WINDOW_HEIGHT - m_PaddlePlayer.h;

}

void cGameEngine::Render()
{
	if (!m_bRunning) return;

	//clear the backbuffer
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);

	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 255, 255);
	SDL_RenderDrawRect(m_Renderer, &m_PaddleComp);
	SDL_RenderDrawRect(m_Renderer, &m_PaddlePlayer);




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
