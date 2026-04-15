#pragma once

#include <vector>
#include "Raylib.h"
#include "raymath.h"
#include "AssetsList.h"
#include "Actor.h"
#include "Terrain.h"
#include "Engine.h"

using std::vector;

static int selectedVertex {-1};
static void DrawScreen(Vector2* scroll);

//Draw the terrain and the gameObjects on screen
static void DrawScreen(Vector2* scroll){
	//Draw Floors
	for (int i = 0; i < Terrain::floorList.size(); i++)
	{
		Terrain::Floor& floor = Terrain::floorList[i];
		if (!floor.computed) Terrain::ComputeFloor(floor);
		Texture2D* sprite = &AssetList::SpriteList[Terrain::dictionary[floor.dictionaryTexture]];
		//Transform vertices location to scrolled
		if (floor.verticesLocation.size() > 3)
		{
			std::vector<Vector2> verticesScrolled;
			verticesScrolled.reserve(floor.vertices.size());
			for (auto vertex : floor.verticesLocation)
			{
				verticesScrolled.push_back(Vector2Add(vertex, *scroll));
			}
			//Add the second one again to close the triangle strip
			verticesScrolled.push_back(verticesScrolled[1]);
			DrawTriangleFan(&(verticesScrolled[0]), (int)verticesScrolled.size(), BROWN);
			
			for (int i = 1; i < static_cast<int>(verticesScrolled.size()) - 1; i++)
			{
				DrawLineV(verticesScrolled[i], verticesScrolled[i + 1], GRAY);
			}
		}
		if (Engine::instance->GetCurrentMode() == CurrentMode::Floors)
		{
			if (Terrain::nearGizmo == Floors)
			{
				if (Terrain::nearIndice == i)
				{
					DrawRectangleRec(Rectangle{floor.center.x + scroll->x - 27.0f, floor.center.y + scroll->y - 27.0f, 54.0f, 54.0f}, BLUE);
				}
			}
		}
		DrawTexturePro(*sprite, 
					   Rectangle{0, 0, static_cast<float>(sprite->width), static_cast<float>(sprite->height)},
					   Rectangle{floor.center.x + scroll->x, floor.center.y + scroll->y, 50.0f, 50.0f},
					   Vector2{25.0f, 25.0f},
					   0.0f,
					   WHITE);
	}
	//Draw Walls
	for (Terrain::Wall& wall : Terrain::wallList)
	{
		if (!wall.computed) Terrain::ComputeWall(wall);
		Texture2D* sprite = &AssetList::SpriteList[Terrain::dictionary[wall.dictionaryTexture]];
		//Draw Wall
		DrawTexturePro(*sprite, 
					   Rectangle{0, 0, static_cast<float>(sprite->width), static_cast<float>(sprite->height)},
					   Rectangle{Terrain::wallVertices[wall.start].x + scroll->x, Terrain::wallVertices[wall.start].y + scroll->y, Vector2Distance(Terrain::wallVertices[wall.start], Terrain::wallVertices[wall.end]), Terrain::wallDrawSize},
					   Vector2{0.0f, Terrain::wallDrawSize * 0.5f},
					   wall.rotation.z,
					   WHITE);
		
		//Draw Forward
		Vector2 center = Vector2Add(Vector2Scale(Vector2Subtract(Terrain::wallVertices[wall.end], Terrain::wallVertices[wall.start]), 0.5f), Terrain::wallVertices[wall.start]);
		DrawTexturePro(*sprite, 
					   Rectangle{0, 0, static_cast<float>(sprite->width), static_cast<float>(sprite->height)},
					   Rectangle{center.x + scroll->x, center.y + scroll->y, 15.0f, 5.0f},
					   Vector2{0.0f, Terrain::wallDrawSize * 0.5f},
					   wall.rotation.z + 90,
					   WHITE);
	}
	//Draw Points
	for (auto vertex : Terrain::wallVertices)
	{
		Color color = BLACK;
		if (Engine::instance->GetCurrentMode() == CurrentMode::Floors)
		{
			if (Engine::instance->GetCurrentFloor() != -1)
			{
				Terrain::Floor currentFloor = Terrain::floorList[Engine::instance->GetCurrentFloor()]; 
				if (std::find(currentFloor.vertices.begin(), currentFloor.vertices.end(), vertex.first) != currentFloor.vertices.end()){
					color = GREEN;
				}
			}
		}
		DrawCircle(static_cast<int>(vertex.second.x + scroll->x), static_cast<int>(vertex.second.y + scroll->y), 5.0f, color);
	}
	//Show Object under the cursor
	if (Terrain::nearIndice != -1)
	{
		switch (Terrain::nearGizmo)
		{
		case Vertex:
			DrawCircle(static_cast<int>(Terrain::wallVertices[Terrain::nearIndice].x + scroll->x), static_cast<int>(Terrain::wallVertices[Terrain::nearIndice].y + scroll->y), 7.0f, BLUE);
			break;
			
		case Edge:
			DrawRectanglePro(
					Rectangle{Terrain::wallVertices[Terrain::wallList[Terrain::nearIndice].start].x + scroll->x, Terrain::wallVertices[Terrain::wallList[Terrain::nearIndice].start].y + scroll->y, Vector2Distance(Terrain::wallVertices[Terrain::wallList[Terrain::nearIndice].start], Terrain::wallVertices[Terrain::wallList[Terrain::nearIndice].end]), Terrain::wallDrawSize},
					Vector2{0.0f, Terrain::wallDrawSize * 0.5f},
					Vector2LineAngle(Terrain::wallVertices[Terrain::wallList[Terrain::nearIndice].start], Terrain::wallVertices[Terrain::wallList[Terrain::nearIndice].end]) * RAD2DEG,
					BLUE);
			break;
		}
	}
	//Show selected object
	if (selectedVertex != -1)
	{
		DrawCircle(static_cast<int>(Terrain::wallVertices[selectedVertex].x + scroll->x), static_cast<int>(Terrain::wallVertices[selectedVertex].y + scroll->y), 7.0f, RED);
	}
};