#pragma once

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include <string>
#include <vector>
#include "AssetsList.h"
#include "Actors/UI_ActionMenu.h"
#include "Actors/UI_ActorMenu.h"

#include "Actors/UI_TilesMenu.h"
#include "Actors/UI_CurrentTexture.h"
#include "Actors/UI_ModeSelector.h"

using std::string;
using std::vector;

class Engine {
private:
	AssetList* assets{};
	
	UI_TilesMenu* tileMenu;
	UI_ActorMenu* actorMenu;
	UI_CurrentTexture* currentTexture;
	UI_ModeSelector* modeSelector;
	UI_ActionMenu* actionMenu;
	
	Vector2 scroll{};
	Vector2 scrollSpeed{ 150, 150};
	
	Gizmo actionGizmo;
	int actionIndice {-1};

	int currentFloor{ 0 };
	
public:
	static Engine* instance;
	
	UI_TilesMenu* GetTileMenu() {return tileMenu;}
	UI_ActorMenu* GetActorMenu() {return actorMenu;}
	
	CurrentMode GetCurrentMode() {return modeSelector->currentMode;}
	int GetCurrentFloor() {return currentFloor;}
	
private:

public:
	Engine();
	~Engine();
	void Start();
	void Update();
	void ChangeItem(string name, string value);
	void Draw();

	void RemoveItem();
	void ChangeCurrentTexture();
};
