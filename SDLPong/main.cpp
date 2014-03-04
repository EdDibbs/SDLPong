#include <iostream>
#include <SDL.h>
#include "cGameEngine.h"
#include <stdlib.h>
#include <time.h>


int main(int argc, char **argv){

	int returnFlag = 0;
	srand((unsigned int) time(NULL));

	cGameEngine* engine = new cGameEngine();

	while (engine->Running())
	{
		engine->HandleInput();
		engine->Update();
		engine->Render();
	}


	returnFlag = engine->GetReturnFlag();
	return returnFlag;
}