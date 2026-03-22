#pragma once
#include <SDL.h>
#include <string>
#include "Engine/Utilitaries/CommonLib.h"

class Window
{
private:
	static Vector2 windowSize;
	
	SDL_Window* pSdlWindow;
	std::string mWindowName;
	
public:
	SDL_Window* GetSdlWindow() const { return pSdlWindow; }
	static Vector2 GetSize() { return windowSize; }

private:
public:
	Window(Uint16 _width, Uint16 _height, std::string _name);
	Window(const Window&) = delete;
	Window& operator= (const Window&) = delete;

	bool Open();
	void Close();
};