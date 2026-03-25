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
	for (auto vertex : Terrain::wallVertices)
	{
		DrawCircle(vertex.second.x + scroll->x, vertex.second.y + scroll->y, 5.0f, BLACK);
	}
	if (Terrain::nearIndice != -1)
	{
		switch (Terrain::nearGizmo)
		{
		case Vertex:
			DrawCircle(Terrain::wallVertices[Terrain::nearIndice].x + scroll->x, Terrain::wallVertices[Terrain::nearIndice].y + scroll->y, 7.0f, BLUE);
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
	if (selectedVertex != -1)
	{
		DrawCircle(Terrain::wallVertices[selectedVertex].x + scroll->x, Terrain::wallVertices[selectedVertex].y + scroll->y, 7.0f, RED);
	}
};