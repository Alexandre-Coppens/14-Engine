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
	bool mIsRunning;
	Window* pWindow;
	std::string mTitle;

	Renderer* pRenderer;

	std::vector<Scene*> mScenes;
	Uint8 mCurrentScene{ 0 };
	float mLastUpdate{ 0 };

public:
	bool getIsRunning() const { return mIsRunning; }

private:
public:
	Game(std::string _title, std::vector<Scene*> _scenes);
	~Game();

	void Initialize();
	void Loop();
	void Render();
	void Close();
};

#endif