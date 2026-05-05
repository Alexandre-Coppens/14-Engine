#include "UI_ActionMenu.h"

#include <iostream>
#include <ostream>
#include <sstream>

#include "UI_WrittingBox.h"
#include "MapMaker/Engine.h"
#include "MapMaker/Terrain.h"

std::string to_string_trim(float value) {
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

UI_ActionMenu::UI_ActionMenu():
	Actor(
		true, 
		"UI_ActionMenu", 
		Vector2{1.0f, 0.0f}, 
		Vector2{-100, 100}, 
		Vector2{100, 40},
		&AssetList::SpriteList["Unknown"], 
		3)
{
	for (int i = 0; i < 4; i++)
	{
		actors.push_back(new UI_WrittingBox());
	}
}

UI_ActionMenu::~UI_ActionMenu()
{
}

void UI_ActionMenu::Draw(Vector2 Scroll)
{
	if (!enabled) return;
	DrawRectangleRec(rect, BLACK);
	
	DrawText(object.c_str(), location.x + 10, location.y - rect.height * 0.5f + 10, 30, RED);
	
	for (int i = 0; i < items - 2; i++)
	{
		actors[i]->Draw();
	}
	
	//Draw Delete button
	DrawRectangleRounded( Rectangle{location.x + 10.0f, location.y + 5.0f + (20.0f * (items - 2)), 30, 30}, 0.15f, 0, isHoveringDelete?RAYWHITE : DARKGRAY);
	DrawRectangleRounded( Rectangle{location.x + 15.0f, location.y + 10.0f + (20.0f * (items - 2)), 20, 20}, 0.15f, 0, isHoveringDelete?BLUE : RED);
	DrawText("x", location.x + 17.5f, location.y + 5.0f + (20.0f * (items - 2)), 30, isHoveringDelete?RAYWHITE : DARKGRAY);
}

void UI_ActionMenu::SetEnable(Gizmo _gizmo, int _indice, Vector2 _location)
{
	SetDisable();
	gizmo = _gizmo;
	location = _location;
	
	enabled = true;
	switch (gizmo)
	{
	case None:
		object = "None";
		items = 0;
		break;
	case Vertex:
		object = "Vertex";
		items = 2;
		break;
	case Edge:
		object = "Edge";
		items = 4;
		break;
	case Floors:
		object = "Floors";
		items = 4;
		break;
	case Actors:
		object = "Actors";
		items = 5;
		break;
	}
	rect = Rectangle{location.x, location.y - items * 20.0f, std::max(static_cast<float>(TextLength(object.c_str())) * 20 + 20, 110.0f)  , items * 40.0f};
	
	for (int i = 0; i < items - 2; i++)
	{
		actors[i]->enabled = true;
		actors[i]->location = Vector2{location.x, location.y - rect.height * 0.5f + (40.0f * (i + 1))};
	}
	
	switch (gizmo)
	{
	case Edge:
		actors[0]->name = "Height";
		actors[0]->type = WrittingBoxType::Float;
		actors[0]->contentString = to_string_trim(Terrain::wallList[_indice].location.z);
		actors[1]->name = "Scale.Up";
		actors[1]->type = WrittingBoxType::Float;
		actors[1]->contentString = to_string_trim(Terrain::wallList[_indice].size.z);
		break;
	case Floors:
		actors[0]->name = "Floor Height";
		actors[0]->type = WrittingBoxType::Float;
		actors[0]->contentString = to_string_trim(Terrain::floorList[_indice].floor);
		actors[1]->name = "Ceiling Height";
		actors[1]->type = WrittingBoxType::Float;
		actors[1]->contentString = to_string_trim(Terrain::floorList[_indice].ceiling);
		break;
	case Actors:
		actors[0]->name = "Height";
		actors[0]->type = WrittingBoxType::Float;
		actors[0]->contentString = to_string_trim(Terrain::actorList[_indice].heigth);
		actors[1]->name = "Rotation";
		actors[1]->type = WrittingBoxType::Float;
		actors[1]->contentString = to_string_trim(Terrain::actorList[_indice].rotation);
		actors[2]->name = "Bonus Text";
		actors[2]->type = WrittingBoxType::String;
		actors[2]->contentString = Terrain::actorList[_indice].bonus;
		break;
	}
}

void UI_ActionMenu::SetDisable()
{
	enabled = false;
	for (UI_WrittingBox* box : actors) box->enabled = false;
}

void UI_ActionMenu::Update()
{
	if (!enabled) return;
	for (int i = 0; i < items - 2; i++)
	{
		actors[i]->Update();
	}
	
	if (CheckCollisionPointRec(GetMousePosition(), Rectangle{location.x + 10.0f, location.y + 5.0f + (20.0f * (items - 2)), 30, 30})) isHoveringDelete = true;
	else isHoveringDelete = false;
}

void UI_ActionMenu::Clicked()
{
	if (isHoveringDelete)
	{
		Engine::instance->RemoveItem();
		enabled = false;
	}
}