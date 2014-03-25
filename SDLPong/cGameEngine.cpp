#include <iostream>
#include "cGameEngine.h"
#include "SDLFunctions.h"
#include <SDL_image.h>
#include <sstream>

cGameEngine::cGameEngine()
{
	std::cout << "cGameEngine constructing..." << std::endl;
	m_iFlag = 0;
	m_bRunning = true;
	m_iScorePlayer = 0;
	m_iScoreComp = 0;

	//initilize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
		Quit(1);
	}

	m_MainWindow = SDL_CreateWindow("SDLPong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, PongGlobals::WINDOW_WIDTH, PongGlobals::WINDOW_HEIGHT, NULL);
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
	
	for (int i = 0; i <= 9; i++)
	{
		std::string path;
		std::stringstream sstm;

		sstm << i << ".png";

		m_Numbers[i] = IMG_Load(".png");
	}

	m_PaddlePlayer.h = PongGlobals::PADDLE_HEIGHT;
	m_PaddlePlayer.w = PongGlobals::PADDLE_WIDTH;
	m_PaddlePlayer.x = 10;
	m_PaddlePlayer.y = PongGlobals::TOP_OF_PLAYING_FIELD + 5;


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

	m_Ball.Update();

	m_PaddleComp.Update(&m_Ball);

	if (m_Keys[KEY_UP])
	{
		m_PaddlePlayer.y -= PongGlobals::PLAYER_MOVE_SPEED;
	}
	if (m_Keys[KEY_DOWN])
	{
		m_PaddlePlayer.y += PongGlobals::PLAYER_MOVE_SPEED;
	}

	//limit the player paddle to the screen
	if (m_PaddlePlayer.y < PongGlobals::TOP_OF_PLAYING_FIELD)
		m_PaddlePlayer.y = PongGlobals::TOP_OF_PLAYING_FIELD;
	else if (m_PaddlePlayer.y + m_PaddlePlayer.h >= PongGlobals::WINDOW_HEIGHT)
		m_PaddlePlayer.y = PongGlobals::WINDOW_HEIGHT - m_PaddlePlayer.h;

	if (m_PaddleComp.GetRect().y < PongGlobals::TOP_OF_PLAYING_FIELD)
		m_PaddleComp.SetY(PongGlobals::TOP_OF_PLAYING_FIELD);
	else if (m_PaddleComp.GetRect().y + m_PaddleComp.GetRect().h >= PongGlobals::WINDOW_HEIGHT)
		m_PaddleComp.SetY(PongGlobals::WINDOW_HEIGHT - m_PaddleComp.GetRect().h);

	//get ball location
	//if ball is too far left, give point to comp
	if (m_Ball.GetRect().x < 0)
	{
		m_iScoreComp++;
		std::cout << "Computer scored! Current score: " << m_iScoreComp << std::endl;

		m_Ball.Bounce(true);
	}
	//if ball is too far right, give point to player
	else if (m_Ball.GetRect().x + m_Ball.GetRect().w > PongGlobals::WINDOW_WIDTH)
	{
		m_iScorePlayer++;
		std::cout << "Player scored! Current score:  " << m_iScorePlayer << std::endl;
		m_Ball.Bounce(true);
	}


	//check bounce off of paddles
	if ((SDL_HasIntersection(&m_PaddlePlayer, &m_Ball.GetRect()) == SDL_TRUE)
		&& m_Ball.GetXDir() == -1)
	{
		m_Ball.Bounce(true);
		std::cout << "Player Bounce." << std::endl;
		m_Ball.Set(m_PaddlePlayer.x + m_PaddlePlayer.w, m_Ball.GetRect().y);
	}
	else if ((SDL_HasIntersection(&m_PaddleComp.GetRect(), &m_Ball.GetRect()) == SDL_TRUE)
		&& m_Ball.GetXDir() == 1)
	{
		m_Ball.Bounce(true);
		std::cout << "Enemy Bounce." << std::endl;
		m_Ball.Set(m_PaddleComp.GetRect().x - m_Ball.GetRect().w, m_Ball.GetRect().y);
	}






}

void cGameEngine::Render()
{
	if (!m_bRunning) return;

	//clear the backbuffer
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);

	//draw the background
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(m_Renderer, 0, PongGlobals::TOP_OF_PLAYING_FIELD, PongGlobals::WINDOW_WIDTH, PongGlobals::TOP_OF_PLAYING_FIELD);



	//draw the paddles
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 255, 255);
	SDL_RenderDrawRect(m_Renderer, &m_PaddleComp.GetRect());
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
