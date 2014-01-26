#pragma once
#include <SDL.h>
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;


class cGameEngine
{
public:
	cGameEngine(); //constructor
	~cGameEngine(); //destructor
	cGameEngine(const cGameEngine &other); //copy constructor
	cGameEngine& operator=(const cGameEngine& rhs); //assignment operator

	bool Initialize();
	bool Running() { return m_bRunning; }
	void HandleInput();
	void Update();
	void Render();


	void Quit(int Flag);
	int GetReturnFlag(){ return m_iFlag; }

private:
	SDL_Renderer* m_Renderer;
	SDL_Window* m_MainWindow;

	Uint32 m_uiTicks;

	SDL_Rect m_PaddlePlayer;
	SDL_Rect m_PaddleComp;

	int m_iFlag;
	bool m_bRunning;
};