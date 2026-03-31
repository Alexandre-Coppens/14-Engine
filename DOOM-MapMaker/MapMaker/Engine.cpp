#include <iostream>
#include <algorithm>
#include "Engine.h"
#include "Terrain.h"
#include "DrawScreen.h"


using std::cout;
using std::to_string;

//int currentTexture{ 0 };

Engine::Engine() {
}

void Engine::Start(){
	assets = AssetList::GetInstance();
	Terrain::gridMeterInPixels = 50.0f;
	Terrain::gridSubdivision = 5;
	Terrain::wallDrawSize = 5.0f;
	tileMenu.SetTexture(AssetList::GetNameAtPosition(0));
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

	tileMenu.Update();
	
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
	
	//TODO: check first if vertex behind
	Terrain::ISCursorOnSomething(mPos);
	
	if(IsMouseButtonPressed(0))
	{		
		if (GetMouseX() >= 460 && GetMouseX() <= 540 && GetMouseY() >= 10 && GetMouseY() <= 90)
		{
			tileMenu.OpenTilesTab();
		}
		else if (tileMenu.GetOpen())
		{
			tileMenu.Interact();
		}
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
					wall.dictionaryTexture = Terrain::CheckInDictionary(tileMenu.GetTexture());
					Terrain::AddNewWall(wall);
					selectedVertex = wall.end;
				}
				else
				{
					selectedVertex = Terrain::nearIndice;
				}
			}
		}
		else if (Terrain::nearGizmo == Edge)
		{
			cout << "nope \n";
		}
		else if (selectedVertex == -1)
		{
			selectedVertex = Terrain::AddNewVertex(mPos);
		}
		else
		{
			Terrain::Wall wall;
			wall.start = selectedVertex;
			wall.end = Terrain::AddNewVertex(mPos);
			wall.dictionaryTexture = Terrain::CheckInDictionary(tileMenu.GetTexture());
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
	if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S))Terrain::SaveMap("Output_Map");
	if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O))Terrain::LoadMap("Output_Map");
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
	tileMenu.Draw();
	
	DrawText(("X. " + to_string((scroll.x - GetMouseX()) / Terrain::gridMeterInPixels)).c_str(), 10, 10, 20, GRAY);
	DrawText(("Y. " + to_string((scroll.y - GetMouseY()) / Terrain::gridMeterInPixels)).c_str(), 10, 30, 20, GRAY);
	DrawText(("Current Sprite:  " + tileMenu.GetTexture()).c_str(), 10, 50, 20, ORANGE);

	Texture2D* sprite;
	if (tileMenu.GetTexture() == "") sprite = &AssetList::SpriteList[AssetList::GetNameAtPosition(0)];
	else sprite = &AssetList::SpriteList[tileMenu.GetTexture()];
	DrawTexturePro(*sprite,
		Rectangle{ 0, 0, (float)sprite->width, (float)sprite->height },
		Rectangle{ 500, 50, 80, 80 },
		Vector2{ 40,40 },
		0.0f,
		WHITE);

	if (GetFrameTime() != 0)
	{
		DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f / GetFrameTime())), 10, GetScreenHeight() - 30, 20, BLACK);
	}

	DrawRectangle(scroll.x - 5.0f, scroll.y - 5.0f, 10, 10, BLACK);
	EndDrawing();
}