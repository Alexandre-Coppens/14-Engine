#include "UI_CurrentTexture.h"

#include "MapMaker/UI_TilesMenu.h"

UI_CurrentTexture::UI_CurrentTexture():
	Actor(
		true, 
		"UI_CurrentTexture", 
		Vector2{1.0f, 0.0f}, 
		Vector2{-100, 100}, 
		Vector2{80, 80},
		&AssetList::SpriteList["Unknown"], 
		3)
{
}

UI_CurrentTexture::~UI_CurrentTexture()
{
}

void UI_CurrentTexture::Draw(Vector2 Scroll)
{
	if (!enabled) return;
	if (hovered)
	{
		Rectangle hoverRect = Rectangle{rect.x - 5, rect.y - 5, rect.width + 10, rect.height + 10};
		DrawRectangleRec(hoverRect, SKYBLUE);
	}
	DrawTexturePro(*sprite,
					Rectangle{ 0, 0, (float)sprite->width, (float)sprite->height },
					rect,
					Vector2Zero(),
					0.0f,
					WHITE);
}

void UI_CurrentTexture::Update()
{
}

void UI_CurrentTexture::Clicked()
{
	dynamic_cast<UI_TilesMenu*>(GetActorWithName("UI_Texture"))->enabled = true;
}
