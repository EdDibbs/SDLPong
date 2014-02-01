#pragma once
#include <SDL.h>
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int PLAYER_MOVE_SPEED = 5;
enum KEYS{ KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };



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

	SDL_Event m_Event;

	Uint32 m_uiTicks;

	SDL_Rect m_PaddlePlayer;
	SDL_Rect m_PaddleComp;

	bool m_Keys[4]; //needs to be updated if entries are added to enum KEYS
	int m_iFlag;
	bool m_bRunning;
};