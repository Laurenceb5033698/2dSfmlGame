#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE HPrevInstance, PSTR pScmdline, int iCmdshow) 
{

	{
		Game game;
		game.init();
		game.run();
		//game.release(); //?
	}
	return 0;
}

