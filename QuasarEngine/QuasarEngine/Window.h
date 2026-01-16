#pragma once
#include <SDL.h>
#include <string>
#include "CommonLib.h"

class Window
{
private:
	SDL_Window* pSdlWindow;
	Vector2 v2WindowSize;
	std::string sWindowName;
public:
	const inline SDL_Window* GetSdlWindow() { return pSdlWindow; }
	const inline Vector2 GetSize() { return v2WindowSize; }

private:
public:
	Window(Uint16 _u16Width, Uint16 _u16Height, std::string _sName);
	Window(const Window&) = delete;
	Window& operator= (const Window&) = delete;

	bool Open();
	void Close();
	void Update();
};