#pragma once
#include "MapMaker/Actor.h"
#include "MapMaker/Terrain.h"

class UI_WrittingBox;
class UI_ActionMenu : public Actor
{
public:
	UI_ActionMenu();
	~UI_ActionMenu();
	
	Gizmo gizmo;
	Vector2 location;

	Terrain::Wall* wall;
	Terrain::Floor* floor;
	Terrain::Actor* actor;
	
	std::vector<UI_WrittingBox*> actors;
	
	string object;
	int items = 2;
	
	bool isHoveringDelete;
	
	void Draw(Vector2 Scroll);
	void SetEnable(Gizmo _gizmo, int _indice, Vector2 _location);
	void SetDisable();
	void Update();
	void Clicked();
};
