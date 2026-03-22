#include "Window.h"

#include "Engine/Utilitaries/DebugMemoryLeakCatcher.h"
#include "Engine/Utilitaries/Log.h"

Vector2 Window::windowSize{800, 800};

Window::Window(const Uint16 _width, const Uint16 _height, const std::string _name):
	pSdlWindow(nullptr), mWindowName(_name)
{
	DEBUGAddClass("Window");
	windowSize = Vector2{ static_cast<float>(_width), static_cast<float>(_height)};
}

bool Window::Open()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		Log::Error(LogType::Video, "Unable to initialize video");
		return false;
	}
	pSdlWindow = SDL_CreateWindow(mWindowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y), SDL_WINDOW_OPENGL);
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
	DEBUGRemoveClass("Window");
}