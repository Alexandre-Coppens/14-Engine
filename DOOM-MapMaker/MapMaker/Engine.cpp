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
	delete currentTexture;
	delete modeSelector;
	
	tileMenu = nullptr;
	currentTexture = nullptr;
}

void Engine::Start()
{
	tileMenu = new UI_TilesMenu{};
	currentTexture = new UI_CurrentTexture{};
	modeSelector = new UI_ModeSelector{};
	
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
			selectedVertex = -1;
			hoveredActor->Clicked();
		}
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
			}
		}
	}
	
	if(IsMouseButtonPressed(1))
	{
		switch (modeSelector->currentMode)
		{
		case CurrentMode::Walls:
			if (Terrain::nearIndice != -1)
			{
				if(Terrain::nearGizmo == Vertex)
				{
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
				}
				else if(Terrain::nearGizmo == Edge)
				{
					Terrain::wallList.erase(Terrain::wallList.begin() + Terrain::nearIndice);
					Terrain::nearIndice = -1;
				}
			}
			else selectedVertex = -1;
			break;
			
		case CurrentMode::Floors:
			if(Terrain::nearGizmo == Vertex)
			{
				std::vector<int>& floorVertices = Terrain::floorList[currentFloor].vertices;
				auto find = std::find(floorVertices.begin(), floorVertices.end(), Terrain::nearIndice);
				if (find != floorVertices.end()) Terrain::floorList[currentFloor].vertices.erase(find);
				Terrain::nearIndice = -1;
				Terrain::floorList[currentFloor].computed = false;
			}
			else if(Terrain::nearGizmo == Floors)
			{
				Terrain::floorList.erase(Terrain::floorList.begin() + currentFloor);
				Terrain::nearGizmo = None;
				currentFloor = -1;
			}
			else
			{
				currentFloor = -1;
				selectedVertex = -1;
			}
			break;
		}
	}
	
	//Save / Load
	if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S))Terrain::SaveMap();
	if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O))Terrain::LoadMap();
	if (IsKeyPressed(KEY_ESCAPE)) selectedVertex = -1;
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
		Terrain::floorList[currentFloor].dictionaryTexture = Terrain::CheckInDictionary(tileMenu->GetTexture());;
	}
}
