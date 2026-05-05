#include "UI_TilesMenu.h"

#include "MapMaker/Engine.h"
#include "MapMaker/Actors/UI_CurrentTexture.h"

UI_TilesMenu::UI_TilesMenu():
	Actor(false, "UI_Texture", Vector2{0, 0.5f}, Vector2{125, 0}, Vector2{250, 400}, &AssetList::SpriteList["Unknown"], 3)
{
}

UI_TilesMenu::~UI_TilesMenu()
{
}

void UI_TilesMenu::Update()
{
	if (enabled)
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

void UI_TilesMenu::Draw(Vector2 Scroll)
{
	if (enabled)
	{
		DrawRectangleRec(rect, BLACK);
		int i = 0;
		for (auto texture : AssetList::SpriteList)
		{
			int x = 10 + (60 * (i % 4));
			int y = 170 + (60 * (i / 4)) - scroll;
			if (y > rect.y - 50 && y < rect.y + rect.height - 10)
			{
				if (currentTextureName == texture.first)
				{
					DrawRectangleRec(Rectangle{ x - 5.0f, Clamp(y - 5.0f, rect.y + 5.0f, GetScreenHeight()), 60, Clamp(std::min(rect.y + rect.height - y, y - rect.y + 50), 0 ,60)}, SKYBLUE);
				}
				Texture* sprite = &texture.second;
				DrawTexturePro(*sprite,
					Rectangle{ 0, 0, (float)sprite->width, (float)sprite->height },
					Rectangle{ (float)x, Clamp(y, rect.y + 10, GetScreenHeight()), 50, Clamp(std::min(rect.y + rect.height - y - 10, y - rect.y + 40), 0 ,50) },
					Vector2Zero(),
					0.0f,
					WHITE);
			}
			i++;
		}
	}
}

void UI_TilesMenu::Clicked()
{
	int i = 0;
	for (auto texture : AssetList::SpriteList)
	{
		int x = 10 + (60 * (i % 4));
		int y = 195 + (60 * (i / 4)) - scroll;
		if (GetMouseX() > x && GetMouseX() < x + 50 && GetMouseY() > y - 25 && GetMouseY() < y + 25)
		{
			currentTextureName = texture.first;
			dynamic_cast<UI_CurrentTexture*>(GetActorWithName("UI_CurrentTexture"))->sprite = &AssetList::SpriteList[texture.first];
			Engine::instance->ChangeCurrentTexture();
		}
		i++;
	}
}