#include <iostream>
#include <SDL.h>
//#include <glew.h>

#include "CommonLib.h"
#include "MathLib.h"

#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
	Game* game = new Game("my first game");

	while (game->GetIsRunning())
	{
		game->Loop();
	}

	game->Close();
	delete game;

	return 0;
}