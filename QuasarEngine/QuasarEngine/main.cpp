#include <iostream>
#include <SDL.h>
#include <glew.h>

#include "CommonLib.h"
#include "MathLib.h"

#include "Game.h"
#include "Scene.h"

#include "Scene_Pong.h"

using namespace std;

int main(int argc, char* argv[])
{
	Game* game = new Game("Pong Game", { new Scene_Pong("Pong Scene")});
	game->Initialize();

	delete game;
	game = nullptr;

	return 0;
}