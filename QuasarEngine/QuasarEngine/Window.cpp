#include "Window.h"
#include "Log.h"
#include "Game.h"

Window::Window(Uint16 _u16Width, Uint16 _u16Height, std::string _sName):
	pSdlWindow(nullptr), v2WindowSize(Vector2{(float)_u16Width, (float)_u16Height}), sWindowName(_sName)
{
}

bool Window::Open()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		Log::Error(LogType::Video, "Unable to initialize video");
		return false;
	}
	pSdlWindow = SDL_CreateWindow(sWindowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(v2WindowSize.x), static_cast<int>(v2WindowSize.y), SDL_WINDOW_OPENGL);
	if (!pSdlWindow)
	{
		Log::Error(LogType::System, "Failed to create window");
		return false;
	}
	return true;
}

void Window::Close()
{
	SDL_DestroyWindow(pSdlWindow);
}