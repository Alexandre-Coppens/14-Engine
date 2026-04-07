#pragma once
#include "MapMaker/Actor.h"

enum class CurrentMode
{
	Walls = 0,
	Floors = 1,
};

class UI_ModeSelector : public Actor
{
private:
	std::vector<std::string> selections {std::vector<std::string>{"Wall", "Floor"}};
	Vector2 optionsSize;
	
	int hoveredOn {0};
	
public:
	CurrentMode currentMode {CurrentMode::Walls};
	
public:
	UI_ModeSelector();
	~UI_ModeSelector();

	void Draw(Vector2 Scroll);
	void Update();
	void Clicked();
};