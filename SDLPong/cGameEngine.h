#pragma once
#include <SDL.h>
#include "cBall.h"
#include "Globals.h"
#include "cCompPaddle.h"

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

	SDL_Rect m_PaddlePlayer; //the player's paddle on the left
	cCompPaddle m_PaddleComp; //the computer's paddle
	cBall m_Ball; //the game ball

	bool m_Keys[4]; //needs to be updated if entries are added to enum KEYS
	int m_iFlag;
	bool m_bRunning;
};