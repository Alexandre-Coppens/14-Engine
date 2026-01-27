#pragma once
#include <SDL.h>
#include <string>
#include "CommonLib.h"

class Window
{
private:
	SDL_Window* pSdlWindow;
	Vector2 mWindowSize;
	std::string mWindowName;
public:
	SDL_Window* GetSdlWindow() const { return pSdlWindow; }
	Vector2 GetSize() const { return mWindowSize; }

private:
public:
	Window(Uint16 _width, Uint16 _height, std::string _name);
	Window(const Window&) = delete;
	Window& operator= (const Window&) = delete;

	bool Open();
	void Close();
	void Update();
};