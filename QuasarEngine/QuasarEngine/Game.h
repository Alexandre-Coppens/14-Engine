#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "CommonLib.h"

#include "Window.h"
#include "Scene.h"

#include "IRenderer.h"

class Scene;
class Game
{
private:
	Window* pWindow;
	std::string mTitle;

	IRenderer* pRenderer;

	std::vector<Scene*> mScenes;
	Uint8 mCurrentScene{ 0 };
	float mLastUpdate{ 0 };

public:

private:
public:
	Game(std::string _title, std::vector<Scene*> _scenes, RendererType _rendererType);
	~Game();

	void Initialize();
	void Loop();
	void Render();
	void Close();

    template<typename T>
    inline void ChangeScene() {
        int target = -1;
        for (int i = 0; i < mScenes.size(); i++)
        {
            if (dynamic_cast<T*>(mScenes[i]) != nullptr)
            {
                target = i;
                break;
            }
        }
        if (target == -1) return;

        mScenes[mCurrentScene]->Close();
        mScenes[mCurrentScene]->UnLoad();
        mCurrentScene = target;
        mScenes[mCurrentScene]->Load(this);
    }
};

#endif