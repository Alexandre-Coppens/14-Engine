#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "Engine/Render/Window.h"
#include "Engine/Render/IRenderer.h"

#include "Engine/Scene.h"

class Scene;
class Game
{
private:
	Window*	   mWindow   { nullptr };
	IRenderer* mRenderer { nullptr };

	std::string mTitle	 { "Game" };
	
	std::vector<Scene*> mScenes;
	Uint8 mCurrentScene { 0 };
	int mChangeSceneTo  {-1 };

	float mLastUpdate   { 0 };

public:

private:
	inline void ChangeScene()
	{
		mScenes[mCurrentScene]->Close();
		mCurrentScene = static_cast<Uint8>(mChangeSceneTo);
		mScenes[mCurrentScene]->setRenderer(mRenderer);
		mScenes[mCurrentScene]->Open(this);
		mChangeSceneTo = -1;
	}
	
public:
	Game(std::string _title, std::vector<Scene*> _scenes, RendererType _rendererType);
	~Game();

	void Initialize();
	void Loop();
	void Render();
	void Close();

    template<typename T>
    inline void SetScene() {
        int target = -1;
        for (int i = 0; i < mScenes.size(); i++)
        {
            if (dynamic_cast<T*>(mScenes[i]) != nullptr)
            {
                target = i;
                break;
            }
        }
        mChangeSceneTo = target;
    }
};

#endif