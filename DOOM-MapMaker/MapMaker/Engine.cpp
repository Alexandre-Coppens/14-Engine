#include <iostream>
#include <algorithm>
#include "Engine.h"
#include "Terrain.h"
#include "DrawScreen.h"

using std::cout;
using std::to_string;

//int currentTexture{ 0 };
Actor* hoveredActor = nullptr;

Engine::Engine() 
{
}

Engine::~Engine()
{
	delete tileMenu;
	delete currentTexture;
	
	tileMenu = nullptr;
	currentTexture = nullptr;
}

void Engine::Start()
{
	tileMenu = new UI_TilesMenu{};
	currentTexture = new UI_CurrentTexture{};
	
	assets = AssetList::GetInstance();
	Terrain::gridMeterInPixels = 50.0f;
	Terrain::gridSubdivision = 5;
	Terrain::wallDrawSize = 5.0f;
	tileMenu->SetTexture(AssetList::GetNameAtPosition(0));
	scroll = { GetScreenWidth() * 0.5f ,GetScreenHeight() * 0.5f };
}

void Engine::Update() {
	vector<Actor*> goList = Actor::GetAllActors();
	for (Actor* go : goList) {
		if (go->enabled) go->Update();
		if (go->needToDestroy) {
			delete go;
		}
	}

	for (Actor* actor : Actor::GetAllActors())
	{
		if (actor->enabled) actor->Update();
	}
	
	//Move
	if (IsMouseButtonDown(2)) {
		scroll = Vector2Add(scroll, GetMouseDelta());
	}
	if(IsKeyDown(KEY_W)){
		scroll = Vector2Add(scroll, Vector2Scale(Vector2{0.0f, 500.0f}, GetFrameTime()));
	}
	if(IsKeyDown(KEY_S)){
		scroll = Vector2Add(scroll, Vector2Scale(Vector2{0.0f, 500.0f}, -GetFrameTime()));
	}
	if(IsKeyDown(KEY_A)){
		scroll = Vector2Add(scroll, Vector2Scale(Vector2{500.0f, 0.0f}, GetFrameTime()));
	}
	if(IsKeyDown(KEY_D)){
		scroll = Vector2Add(scroll, Vector2Scale(Vector2{500.0f, 0.0f}, -GetFrameTime()));
	}

	//Tiles placement
	float subgrid = Terrain::gridMeterInPixels / Terrain::gridSubdivision;
	Vector2 mPos{ round(round(-scroll.x + GetMouseX()) / subgrid) * subgrid, round(round(-scroll.y + GetMouseY()) / subgrid) * subgrid };
	
	//Check is an actor is hovered
	bool isHoveringActor = false;
	hoveredActor = nullptr;
	for (std::vector<Actor*> actorLayer : *Actor::GetAllActorsLayered())
	{
		for (Actor* actor : actorLayer)
		{
			if (!actor->enabled) continue;
			if (actor->IsCursorInBounds())
			{
				actor->hovered = true;
				hoveredActor = actor;
				isHoveringActor = true;
				break;
			}
			actor->hovered = false;
		}
	}
	
	if (!isHoveringActor)
	{
		Terrain::ISCursorOnSomething(mPos);
	}
	
	if(IsMouseButtonPressed(0))
	{		
		if (!isHoveringActor || hoveredActor != tileMenu) tileMenu->enabled = false;
		if (isHoveringActor)
		{
			hoveredActor->Clicked();
		}
		//If close to a already existing vertex
		else if (Terrain::nearIndice != -1 && Terrain::nearGizmo == Vertex)
		{
			if (selectedVertex == -1) selectedVertex = Terrain::nearIndice;
			else
			{
				//Check if the wall already exist
				bool isAlreadyUsed = false;
				for (Terrain::Wall wall : Terrain::wallList)
				{
					if (wall.start == selectedVertex && wall.end == Terrain::nearIndice || wall.start == Terrain::nearIndice && wall.end == selectedVertex) isAlreadyUsed = true;
				}
				
				if (!isAlreadyUsed)
				{
					Terrain::Wall wall;
					wall.start = selectedVertex;
					wall.end = Terrain::nearIndice;
					wall.dictionaryTexture = Terrain::CheckInDictionary(tileMenu->GetTexture());
					Terrain::AddNewWall(wall);
					selectedVertex = wall.end;
				}
				else
				{
					selectedVertex = Terrain::nearIndice;
				}
			}
		}
		//If clicking on a wall
		else if (Terrain::nearGizmo == Edge)
		{
			cout << "nope \n";
		}
		//If no vertexes has been selected
		else if (selectedVertex == -1)
		{
			selectedVertex = Terrain::AddNewVertex(mPos);
		}
		//Else, New Vertex Created and wall placed
		else
		{
			Terrain::Wall wall;
			wall.start = selectedVertex;
			wall.end = Terrain::AddNewVertex(mPos);
			wall.dictionaryTexture = Terrain::CheckInDictionary(tileMenu->GetTexture());
			Terrain::AddNewWall(wall);
			selectedVertex = wall.end;
		}
	}
	
	if(IsMouseButtonPressed(1))
	{
		if (Terrain::nearIndice != -1)
		{
			switch (Terrain::nearGizmo)
			{
			case Vertex:
				Terrain::wallVertices.erase(Terrain::nearIndice);
				
				
				Terrain::wallList.erase(
					std::remove_if(
						Terrain::wallList.begin(),
						Terrain::wallList.end(),
						[](const Terrain::Wall& w){
									return w.start == Terrain::nearIndice || w.end == Terrain::nearIndice;
							}
						),
				Terrain::wallList.end()
				);
				
				if (Terrain::nearIndice == selectedVertex) selectedVertex = -1;
				Terrain::nearIndice = -1;
				break;
			
			case Edge:
				Terrain::wallList.erase(Terrain::wallList.begin() + Terrain::nearIndice);
				Terrain::nearIndice = -1;
				break;
			}
		}
		else selectedVertex = -1;
	}

	//Change textures
	// if (GetMouseWheelMove()>0 && !tileMenu.GetOpen()) {
	// 	if (currentTexture == 0)currentTexture = AssetList::SpriteList.size() - 1;
	// 	else currentTexture--;
	// }
	// if (GetMouseWheelMove() < 0 && !tileMenu.GetOpen()) {
	// 	if (currentTexture == AssetList::SpriteList.size() - 1)currentTexture = 0;
	// 	else currentTexture++;
	// }

	//Save / Load
	if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S))Terrain::SaveMap();
	if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O))Terrain::LoadMap();
	if (IsKeyPressed(KEY_ESCAPE)) selectedVertex = -1;
}

void Engine::Draw() {
	BeginDrawing();
	ClearBackground(RAYWHITE);

	rlPushMatrix();
	rlTranslatef(0 + scroll.x, 25 * Terrain::gridMeterInPixels + scroll.y, 0);
	rlRotatef(90, 1, 0, 0);
	DrawGrid(1000, Terrain::gridMeterInPixels);
	rlPopMatrix();
	
	rlPushMatrix();
	rlTranslatef(1 + scroll.x, 1 + 25 * Terrain::gridMeterInPixels + scroll.y, 0);
	rlRotatef(90, 1, 0, 0);
	DrawGrid(1000, Terrain::gridMeterInPixels);
	rlPopMatrix();
	
	rlPushMatrix();
	rlTranslatef(-1 + scroll.x, -1 + 25 * Terrain::gridMeterInPixels + scroll.y, 0);
	rlRotatef(90, 1, 0, 0);
	DrawGrid(1000, Terrain::gridMeterInPixels);
	rlPopMatrix();
	
	float subgrid = Terrain::gridMeterInPixels / Terrain::gridSubdivision;
	rlPushMatrix();
	rlTranslatef(0 + scroll.x, 25 * Terrain::gridMeterInPixels + scroll.y, 0);
	rlRotatef(90, 1, 0, 0);
	DrawGrid(1000 * Terrain::gridSubdivision, subgrid);
	rlPopMatrix();
	
	DrawScreen(&scroll);
	auto actors = Actor::GetAllActorsLayered();
	for (int i = 0; i < actors->size(); i++)
	{
		for (int j = 0; j < actors->at(i).size(); j++)
		{
			actors->at(i)[j]->Draw(scroll);
		}
	}
	
	DrawText(("X. " + to_string((scroll.x - GetMouseX()) / Terrain::gridMeterInPixels)).c_str(), 10, 10, 20, GRAY);
	DrawText(("Y. " + to_string((scroll.y - GetMouseY()) / Terrain::gridMeterInPixels)).c_str(), 10, 30, 20, GRAY);
	DrawText(("Current Sprite:  " + tileMenu->GetTexture()).c_str(), 10, 50, 20, ORANGE);

	if (GetFrameTime() != 0)
	{
		DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f / GetFrameTime())), 10, GetScreenHeight() - 30, 20, BLACK);
	}

	DrawRectangle(scroll.x - 5.0f, scroll.y - 5.0f, 10, 10, BLACK);
	EndDrawing();
}