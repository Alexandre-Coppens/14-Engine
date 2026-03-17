#include "UI_TilesMenu.h"

UI_TilesMenu::UI_TilesMenu(){
	interactibleBar = Rectangle{ 0, GetScreenHeight() * 0.375f, 30, GetScreenHeight() * 0.250f};
}

UI_TilesMenu::~UI_TilesMenu(){
}

void UI_TilesMenu::Update(){
}

void UI_TilesMenu::Draw(){
}

int UI_TilesMenu::Clicked(){
	if (GetMousePosition().x > interactibleBar.x && GetMousePosition().x < interactibleBar.x + interactibleBar.width &&
		GetMousePosition().y > interactibleBar.y && GetMousePosition().y < interactibleBar.y + interactibleBar.height) {
		open = !open;
	}
	return 0;
}

void UI_TilesMenu::OpenTilesTab(){
}
