#include <iostream>
#include <string>
#include "Engine.h"
#include "AssetsList.h"

using std::string;
Engine engine;

int main()
{
    InitWindow(1280, 720, "Raylib");
    SetTargetFPS(60);
	SetExitKey(KEY_NULL);

    InitAudioDevice();

	AssetList::LoadRessources();
	engine.Start();

	srand(time(NULL));
    while (!WindowShouldClose()){
        UpdateMusicStream(AssetList::music);
		engine.Update();
		engine.Draw();
	}

    UnloadMusicStream(AssetList::music);
    CloseAudioDevice();
    CloseWindow();
}