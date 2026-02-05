#include <iostream>
#include <SDL.h>
#include <glew.h>

#include "CommonLib.h"
#include "MathLib.h"

#include "Game.h"
#include "Scene.h"

#include "Scene_Pong.h"
#include "Scene_GameOver.h"
#include "Scene_Test.h"
#include "IRenderer.h"

using namespace std;

int main(int argc, char* argv[])
{
	//Scene_Pong pong = Scene_Pong("Pong Scene");
	//Scene_GameOver gameover = Scene_GameOver("Game Over");
	Scene_Test test = Scene_Test("Scene Test");

	std::vector<Scene*> SceneList;
	//SceneList.push_back(&pong);
	//SceneList.push_back(&gameover);
	SceneList.push_back(&test);

	Game* game = new Game("Open Gl", SceneList, RendererType::OPENGL);
	game->Initialize();

	delete game;
	game = nullptr;

	return 0;
}