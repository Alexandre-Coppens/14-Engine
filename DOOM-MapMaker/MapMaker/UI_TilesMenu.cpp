#include "UI_TilesMenu.h"

UI_TilesMenu::UI_TilesMenu(){
}

UI_TilesMenu::~UI_TilesMenu(){
}

void UI_TilesMenu::Update(){
	if (open)
	{
		if (GetMouseWheelMove()>0) {
			scroll -= 600.0f * GetFrameTime();
			scroll = std::max(0.0f, scroll);
		}
		if (GetMouseWheelMove() < 0) {
			scroll += 600.0f * GetFrameTime();
		}
	}
}

void UI_TilesMenu::Draw(){
	if (open)
	{
		DrawRectangleRec(rectangle, GRAY);
		int i = 0;
		for (auto texture : AssetList::SpriteList)
		{
			int x = 10 + (60 * (i % 4));
			int y = 250 + (60 * (i / 4)) - scroll;
			if (y > 210 && y < 460)
			{
				if (currentTextureName == texture.first)
				{
					DrawRectangleRec(Rectangle{ x - 5.0f, y - 30.0f, 60, 60 }, SKYBLUE);
				}
				Texture* sprite = &texture.second;
				DrawTexturePro(*sprite,
					Rectangle{ 0, 0, (float)sprite->width, (float)sprite->height },
					Rectangle{ x + 25.0f, y + 0.25f, 50, 50 },
					Vector2{ 25,25 },
					0.0f,
					WHITE);
			}
			i++;
		}
	}
}

void UI_TilesMenu::OpenTilesTab(){
	open = !open;
	rectangle = Rectangle{ 0, GetScreenHeight() * 0.250f, 250, GetScreenHeight() * 0.500f};
}
