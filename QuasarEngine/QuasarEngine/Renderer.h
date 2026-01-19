#pragma once
#include "Rectangle.h"
#include "Window.h"

class Renderer
{
private:
	SDL_Renderer* pSDLRenderer;


public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator= (const Renderer&) = delete;

	bool Initialize(Window& _pWindow);
	void BeginDraw();
	void EndDraw();
	void Close();

	void DrawRect(Rectangle& _pRect);
};