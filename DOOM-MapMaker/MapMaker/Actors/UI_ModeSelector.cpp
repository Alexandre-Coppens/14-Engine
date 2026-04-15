#include "UI_ModeSelector.h"

#include "MapMaker/DrawScreen.h"

UI_ModeSelector::UI_ModeSelector():
	Actor(
		true, 
		"UI_ModeSelector", 
		Vector2{0.5f, 0.0f}, 
		Vector2{0.0f, 40}, 
		Vector2{200, 40},
		&AssetList::SpriteList["Unknown"], 
		3)
{
	optionsSize = Vector2{size.x / selections.size(), size.y};
}

UI_ModeSelector::~UI_ModeSelector()
{
}

void UI_ModeSelector::Draw(Vector2 Scroll)
{
	if (!enabled) return;
	for (int i = 0; i < selections.size(); i++)
	{
		std::vector<Color> colors;
		if (static_cast<int>(currentMode) == i) colors = std::vector<Color>{ BLACK, DARKGRAY, WHITE };
		else if (hoveredOn == i && hovered) colors = std::vector<Color>{ BLUE, GRAY, BLACK };
		else colors = std::vector<Color>{ DARKGRAY, GRAY, BLACK };
		
		DrawRectangle(rect.x + i * optionsSize.x, rect.y, optionsSize.x, optionsSize.y, colors[0]);
		DrawRectangle(rect.x + i * optionsSize.x + 4, rect.y + 4, optionsSize.x - 8, optionsSize.y - 8, colors[1]);
		DrawText(selections[i].c_str(), rect.x + i * optionsSize.x + 6, rect.y + 6, optionsSize.y - 12, colors[2]);
	}
}

void UI_ModeSelector::Update()
{
	if (hovered)
	{
		hoveredOn = static_cast<int>(floorf((GetMouseX() - rect.x) / optionsSize.x));
	}
}

void UI_ModeSelector::Clicked()
{
	selectedVertex =-1;
	switch (hoveredOn)
	{
		case 0:
			currentMode = CurrentMode::Walls;
			break;
		
		case 1:
			currentMode = CurrentMode::Floors;
			break;
	}
}
