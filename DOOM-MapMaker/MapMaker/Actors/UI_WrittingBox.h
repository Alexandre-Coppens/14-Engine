#pragma once
#include "MapMaker/Actor.h"
#include "MapMaker/Terrain.h"

enum class WrittingBoxType
{
	Int,
	Float,
	String,
};

class UI_WrittingBox
{
public:
	UI_WrittingBox();
	~UI_WrittingBox();
	
	bool enabled = false;
	Vector2 location;
	
	int maxCharacters = 10;
	
	string name = "";
	WrittingBoxType type = WrittingBoxType::Int;
	
	string contentString = "0";
	
	bool isHovering;
	
	void Draw();
	void Update();
	void Clicked();
};
