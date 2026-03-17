#pragma once

#include <vector>
#include "Raylib.h"
#include "raymath.h"
#include "AssetsList.h"
#include "Actor.h"
#include "Terrain.h"

using std::vector;

static int selectedVertex {-1};
static void DrawScreen(Vector2* scroll);

//Draw the terrain and the gameObjects on screen
static void DrawScreen(Vector2* scroll){
	for (auto vertex : Terrain::wallVertices)
	{
		DrawCircle(vertex.second.x + scroll->x, vertex.second.y + scroll->y, 5.0f, BLACK);
	}
	for (Terrain::Wall wall : Terrain::wallList)
	{
		Texture2D* sprite = &AssetList::SpriteList[Terrain::dictionary[wall.dictionaryTexture]];
		DrawTexturePro(*sprite, 
					   Rectangle{0, 0, static_cast<float>(sprite->width), static_cast<float>(sprite->height)},
					   Rectangle{Terrain::wallVertices[wall.start].x + scroll->x, Terrain::wallVertices[wall.start].y + scroll->y, Vector2Distance(Terrain::wallVertices[wall.start], Terrain::wallVertices[wall.end]), Terrain::wallDrawSize},
					   Vector2{0.0f, Terrain::wallDrawSize * 0.5f},
					   Vector2LineAngle(Terrain::wallVertices[wall.start], Terrain::wallVertices[wall.end]) * RAD2DEG,
					   WHITE);
	}
	if (selectedVertex != -1)
	{
		DrawCircle(Terrain::wallVertices[selectedVertex].x + scroll->x, Terrain::wallVertices[selectedVertex].y + scroll->y, 7.0f, RED);
	}
};