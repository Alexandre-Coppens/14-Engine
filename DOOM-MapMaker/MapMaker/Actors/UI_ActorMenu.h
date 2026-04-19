#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "MapMaker/Actor.h"

using std::string;
using std::vector;
using std::map;

class UI_ActorMenu : public Actor {
private:
	Rectangle rectangle{};
	float scroll = 0;
	string currentActorName {};

public:
	UI_ActorMenu();
	~UI_ActorMenu();

	void Draw(Vector2 Scroll);
	void Update();
	void Clicked();

	void OpenTilesTab();
	string GetActor() {return currentActorName;}
	void SetActor(string actorName) {currentActorName = actorName;}
};