#include <iostream>
#include <SDL.h>
#include <glew.h>

#include "Engine/Game.h"
#include "Engine/Scene.h"

#include "Engine/Render/IRenderer.h"

#include "Game2D/Scenes/Scene_Pong.h"
#include "Game2D/Scenes/Scene_GameOver.h"
#include "Game3D/Scenes/Scene_Test.h"

using namespace std;

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

//TODO Go around all the code to try to remove all the unused includes

int main(int argc, char* argv[])
{
	//Scene_Pong pong = Scene_Pong("Pong Scene");
	//Scene_GameOver gameover = Scene_GameOver("Game Over");

	std::vector<Scene*> SceneSdlList;
	//SceneSdlList.push_back(&pong);
	//SceneSdlList.push_back(&gameover);

	std::vector<Scene*> SceneGlList{
		new Scene_Test("Scene Test")
	};


	Game* game;
	if (true)
	{
		game = new Game("Open Gl", SceneGlList, RendererType::OPENGL);
	}
	else
	{
		//game = new Game("Pong", SceneSdlList, RendererType::SDL);
	}
	
	game->Initialize();
	game->Loop();
	game->Close();

	delete game;
	game = nullptr;

	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	//TODO: Remove Memory Leaks Left

	return 0;
}