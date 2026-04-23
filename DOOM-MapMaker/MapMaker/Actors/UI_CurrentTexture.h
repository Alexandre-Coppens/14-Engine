#pragma once
#include "MapMaker/Actor.h"

class UI_CurrentTexture : public Actor
{
public:
	UI_CurrentTexture();
	~UI_CurrentTexture();

	void Draw(Vector2 Scroll);
	void Update();
	void Clicked();
};
