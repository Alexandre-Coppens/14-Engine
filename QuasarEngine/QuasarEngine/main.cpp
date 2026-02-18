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

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

int main(int argc, char* argv[])
{
	Scene_Pong pong = Scene_Pong("Pong Scene");
	Scene_GameOver gameover = Scene_GameOver("Game Over");
	Scene_Test test = Scene_Test("Scene Test");

	std::vector<Scene*> SceneSdlList;
	SceneSdlList.push_back(&pong);
	SceneSdlList.push_back(&gameover);

	std::vector<Scene*> SceneGlList;
	SceneGlList.push_back(&test);

	Game* game;
	if (true)
	{
		game = new Game("Open Gl", SceneGlList, RendererType::OPENGL);
	}
	else
	{
		game = new Game("Pong", SceneSdlList, RendererType::SDL);
	}
	
	game->Initialize();
	game->Loop();
	game->Close();

	delete game;
	game = nullptr;

	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}