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
	m_PaddlePlayer.y = TOP_OF_PLAYING_FIELD + 5;

	m_PaddleComp.h = 40;
	m_PaddleComp.w = 10;
	m_PaddleComp.x = WINDOW_WIDTH - m_PaddleComp.w - 10;
	m_PaddleComp.y = TOP_OF_PLAYING_FIELD + 5;


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
			case SDLK_b:
				if (!m_Event.key.repeat) m_Ball.Bounce(true);
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

	//limit the player paddle to the screen
	if (m_PaddlePlayer.y < TOP_OF_PLAYING_FIELD)
		m_PaddlePlayer.y = TOP_OF_PLAYING_FIELD;
	else if (m_PaddlePlayer.y + m_PaddlePlayer.h >= WINDOW_HEIGHT)
		m_PaddlePlayer.y = WINDOW_HEIGHT - m_PaddlePlayer.h;

	//check bounce off of paddles
	if ((SDL_HasIntersection(&m_PaddlePlayer, &m_Ball.GetRect()) == SDL_TRUE)
		&& m_Ball.GetXDir() == -1)
	{
		m_Ball.Bounce(true);
		std::cout << "Bounce." << std::endl;
		m_Ball.Set(m_PaddlePlayer.x + m_PaddlePlayer.w, m_Ball.GetRect().y);
	}
	else if ((SDL_HasIntersection(&m_PaddleComp, &m_Ball.GetRect()) == SDL_TRUE)
		&& m_Ball.GetXDir() == 1)
	{
		m_Ball.Bounce(true);
		std::cout << "Bounce." << std::endl;
		m_Ball.Set(m_PaddleComp.x - m_Ball.GetRect().x, m_Ball.GetRect().y);
	}

	m_Ball.Update();
	//get ball location
	//if ball is too far left, give point to comp
	//if ball is too far right, give point to player




}

void cGameEngine::Render()
{
	if (!m_bRunning) return;

	//clear the backbuffer
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);

	//draw the background
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(m_Renderer, 0, TOP_OF_PLAYING_FIELD, WINDOW_WIDTH, TOP_OF_PLAYING_FIELD);



	//draw the paddles
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 255, 255);
	SDL_RenderDrawRect(m_Renderer, &m_PaddleComp);
	SDL_RenderDrawRect(m_Renderer, &m_PaddlePlayer);

	SDL_SetRenderDrawColor(m_Renderer, 50, 205, 50, 255);
	SDL_RenderFillRect(m_Renderer, &m_Ball.GetRect());


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
