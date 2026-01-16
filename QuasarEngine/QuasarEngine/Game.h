#pragma once
#include <string>
#include "CommonLib.h"

#include "Window.h"

class Game
{
private:
	bool bIsRunning;
	Window* pWindow;
	std::string sTitle;
public:
	bool* GetIsRunning() { return &bIsRunning; }

private:
public:
	Game(std::string _sTitle);
	~Game();

	void Initialize();
	void Loop();
	void Render();
	void Update();
	void CheckInputs();
	void Close();
	
};