#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "CommonLib.h"

#include "Window.h"
#include "Renderer.h"

class Scene;

class Game
{
private:
	bool bIsRunning;
	Window* pWindow;
	std::string sTitle;

	Renderer* pRenderer;

	std::vector<Scene*> vScenes;
	Uint8 u8CurrentScene{ 0 };
	float fLastUpdate{ 0 };

public:
	bool* GetIsRunning() { return &bIsRunning; }

private:
public:
	Game(std::string _sTitle, std::vector<Scene*> _vScenes);
	~Game();

	void Initialize();
	void Loop();
	void Render();
	void Close();
};

#endif