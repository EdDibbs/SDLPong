#pragma once
#include <SDL.h>

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

	int m_iFlag;
	bool m_bRunning;
};