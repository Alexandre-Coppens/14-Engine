#pragma once
#include "Engine/Render/IRenderer.h"

class ImguiManager
{
public:
	static void Initialize(IRenderer* _renderer, Window* _window);
	
	static void PullEvents(SDL_Event* _events);
	static void Update();
	static void Render();
	
	static void Close();
};
