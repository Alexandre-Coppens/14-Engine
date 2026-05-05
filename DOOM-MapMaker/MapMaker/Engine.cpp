#include <iostream>
#include <algorithm>
#include "Engine.h"
#include "Terrain.h"
#include "DrawScreen.h"

using std::cout;
using std::to_string;

Engine* Engine::instance;


//int currentTexture{ 0 };
Actor* hoveredActor = nullptr;
float subgrid;
Vector2 mPos;
bool isHoveringActor;

Engine::Engine() 
{
	if (instance == nullptr) instance = this;
	else
	{
		delete this;
	}
}

Engine::~Engine()
{
	delete tileMenu;
	delete actorMenu;
	delete currentTexture;
	delete modeSelector;
	delete actionMenu;
	
	tileMenu = nullptr;
	currentTexture = nullptr;
}

void Engine::Start()
{
	tileMenu = new UI_TilesMenu{};
	actorMenu = new UI_ActorMenu{};
	currentTexture = new UI_CurrentTexture{};
	modeSelector = new UI_ModeSelector{};
	actionMenu = new UI_ActionMenu{};
	
	actionMenu->enabled = false;
	
	assets = AssetList::GetInstance();
	Terrain::gridMeterInPixels = 50.0f;
	Terrain::gridSubdivision = 5;
	Terrain::wallDrawSize = 5.0f;
	tileMenu->SetTexture(AssetList::GetNameAtPosition(0));
	scroll = { GetScreenWidth() * 0.5f ,GetScreenHeight() * 0.5f };
	
	Terrain::floorList.push_back(Terrain::Floor());
}

void Engine::Update() 
{
	vector<Actor*> goList = Actor::GetAllActors();
	for (Actor* go : goList) 
	{
		if (go->enabled) go->Update();
		if (go->needToDestroy) {
			delete go;
		}
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
	subgrid = Terrain::gridMeterInPixels / Terrain::gridSubdivision;
	mPos = Vector2{round(round(-scroll.x + GetMouseX()) / subgrid) * subgrid, round(round( - scroll.y + GetMouseY()) / subgrid) * subgrid };
	
	//Check is an actor is hovered
	isHoveringActor = false;
	hoveredActor = nullptr;
	for (Actor* actor : Actor::GetAllActors())
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
	
	if (!isHoveringActor)
	{
		Terrain::ISCursorOnSomething(mPos);
	}
	
	if(IsMouseButtonPressed(0))
	{	
		//Check if an Actor is behind
		if (!isHoveringActor || hoveredActor != tileMenu) tileMenu->enabled = false;
		if (isHoveringActor)
		{
			selectedVertex = -1;
			hoveredActor->Clicked();
		}
		//Check if the action Menu is open
		else if (actionMenu->enabled) 
			actionMenu->SetDisable();
		//If close to a already existing vertex
		else
		{
			switch (modeSelector->currentMode)
			{
			case CurrentMode::Walls:
				if (Terrain::nearIndice != -1 && Terrain::nearGizmo == Vertex)
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
				break;
				
			case CurrentMode::Floors:
				if (Terrain::nearIndice != -1 && Terrain::nearGizmo == Vertex)
				{
					//Check if a floor is selected else create new
					if (currentFloor == -1)
					{
						currentFloor = static_cast<int>(Terrain::floorList.size());
						Terrain::floorList.push_back(Terrain::Floor());
					}
					//Check if the vertex is already on the floor list
					if (not(std::find(Terrain::floorList[currentFloor].vertices.begin(), Terrain::floorList[currentFloor].vertices.end(), Terrain::nearIndice) != Terrain::floorList[currentFloor].vertices.end()))
					{
						Terrain::floorList[currentFloor].vertices.push_back(Terrain::nearIndice);
						Terrain::floorList[currentFloor].computed = false;
					}
					selectedVertex = Terrain::nearIndice;
				}
				if (Terrain::nearGizmo == Floors)
				{
					if (currentFloor != -1)
					{
						currentTexture->Clicked();
					}
					currentFloor = Terrain::nearIndice;
				}
				if (Terrain::nearIndice == -1)
				{
					currentFloor = -1;
				}
				break;
			case CurrentMode::Actors:
				if (Terrain::nearIndice != -1 && Terrain::nearGizmo == Actors)
				{

				}
				else
				{
					Terrain::Actor actor;
					actor.name = actorMenu->GetActor();
					actor.location = mPos;
					Terrain::actorList.push_back(actor);
				}
				if (Terrain::nearIndice == -1)
				{
					currentFloor = -1;
				}
				break;
			}
		}
	}
	
	if(IsMouseButtonPressed(1))
	{
		if (Terrain::nearIndice != -1)
		{
			actionGizmo = Terrain::nearGizmo;
			actionIndice = Terrain::nearIndice;
			if(Terrain::nearGizmo == Vertex)
			{
				actionMenu->SetEnable(Vertex, actionIndice, GetMousePosition());
			}
			else if(Terrain::nearGizmo == Edge)
			{
				actionMenu->SetEnable(Edge, actionIndice, GetMousePosition());
			}
			else if(Terrain::nearGizmo == Floors)
			{
				actionMenu->SetEnable(Floors, actionIndice, GetMousePosition());
			}
			else if(Terrain::nearGizmo == Actors)
			{
				actionMenu->SetEnable(Actors, actionIndice, GetMousePosition());
			}
		}
		else
		{
			actionMenu->SetDisable();
			selectedVertex = -1;
		}
	}
	
	//Save / Load
	if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S))Terrain::SaveMap();
	if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O))Terrain::LoadMap();
	if (IsKeyPressed(KEY_ESCAPE)) selectedVertex = -1;
}

void Engine::ChangeItem(string name, string value)
{
	value = "0" + value;
	switch (actionGizmo)
	{
	case Edge:
		if (name == "Height") Terrain::wallList[actionIndice].location.z = stof(value);
		if (name == "Scale.Up") Terrain::wallList[actionIndice].size.z = stof(value);
		break;
		
	case Floors:
		if (name == "Floor Height") Terrain::floorList[actionIndice].floor = stof(value);
		if (name == "Ceiling Height") Terrain::floorList[actionIndice].ceiling = stof(value);
		break;
		
	case Actors:
		if (name == "Height") Terrain::actorList[actionIndice].heigth = stof(value);
		if (name == "Rotation") Terrain::actorList[actionIndice].rotation = stof(value);
		if (name == "Bonus Text") Terrain::actorList[actionIndice].bonus = value;
		break;
	}
}

void Engine::RemoveItem()
{
	switch (actionGizmo)
	{
	case Vertex:
		Terrain::wallVertices.erase(actionIndice);
		Terrain::wallList.erase(
			std::remove_if(
				Terrain::wallList.begin(),
				Terrain::wallList.end(),
				[this](const Terrain::Wall& w){
					return w.start == actionIndice || w.end == actionIndice;
				}
			),
			Terrain::wallList.end()
		);
	
		if (actionIndice == selectedVertex) selectedVertex = -1;
		Terrain::nearIndice = -1;
		break;
		
	case Edge:
		Terrain::wallList.erase(Terrain::wallList.begin() + actionIndice);
		Terrain::nearIndice = -1;
		break;
		
	case Floors:
		Terrain::floorList.erase(Terrain::floorList.begin() + currentFloor);
		Terrain::nearGizmo = None;
		currentFloor = -1;
		break;
		
	case Actors:
		Terrain::actorList.erase(Terrain::actorList.begin() + actionIndice);
		Terrain::nearGizmo = None;
		Terrain::nearIndice = -1;
		break;
	}
}

void Engine::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	//Draw Grid (yes, this many grids)
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
	
	//Draw Terrain
	DrawScreen(&scroll);
	
	//Draw Actors
	auto actors = Actor::GetAllActorsLayered();
	for (int i = 0; i < actors->size(); i++)
	{
		for (int j = 0; j < actors->at(i).size(); j++)
		{
			if (actors->at(i)[j] == nullptr) continue;
			actors->at(i)[j]->Draw(scroll);
		}
	}
	
	//Draw Infos
	DrawText(("X. " + to_string((scroll.x - GetMouseX()) / Terrain::gridMeterInPixels)).c_str(), 10, 10, 20, GRAY);
	DrawText(("Y. " + to_string((scroll.y - GetMouseY()) / Terrain::gridMeterInPixels)).c_str(), 10, 30, 20, GRAY);
	DrawText(("Current Sprite:  " + tileMenu->GetTexture()).c_str(), 10, 50, 20, ORANGE);

	if (GetFrameTime() != 0)
	{
		DrawText(TextFormat("CURRENT FPS: %i", static_cast<int>(1.0f / GetFrameTime())), 10, GetScreenHeight() - 30, 20, BLACK);
	}
	
	//Center of world
	DrawRectangle(static_cast<int>(scroll.x - 5.0f), static_cast<int>(scroll.y - 5.0f), 10, 10, BLACK);
	EndDrawing();
}

void Engine::ChangeCurrentTexture()
{
	if (currentFloor != -1)
	{
		Terrain::floorList[currentFloor].dictionaryTexture = Terrain::CheckInDictionary(tileMenu->GetTexture());
	}
}
