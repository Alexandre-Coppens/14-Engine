#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include "Engine/Utilitaries//Log.h"

#include "Engine/Render/IRenderer.h"
#include "Engine/Render/RendererGl.h"
#include "Engine/Render/RendererSdl.h"

class Actor;
class Game;
class Scene
{
private:
protected:
	std::string mName;
	IRenderer* pRenderer;
	Game* pGame;

	std::vector<Actor*> mActorList;
	std::vector<Actor*> mAddActorList;
	std::vector<Actor*> mDestroyActorList;

public:
	static Scene* ActiveScene;

	IRenderer* getRenderer()	const	{ return pRenderer; }
	std::string  getSceneName() const	{ return mName; }
	Game* getGame()				const	{ return pGame; }

	RendererSdl* getRendererSdl()	const {
		RendererSdl* ret = dynamic_cast<RendererSdl*>(pRenderer);
		if (ret == nullptr)
		{
			Log::Error(LogType::Error, "Renderer not of type SDL.");
		}
		return ret;
	}

	RendererGl* getRendererGl()	const {
		RendererGl* ret = dynamic_cast<RendererGl*>(pRenderer);
		if (ret == nullptr)
		{
			Log::Error(LogType::Error, "Renderer not of type OPENGL.");
		}
		return ret;
	}

	void setRenderer(IRenderer* _pRenderer) { pRenderer = _pRenderer; }

private:
	void KillActors();

public:
	Scene(std::string _name = "Scene");
	virtual ~Scene();

	virtual void Start();
	virtual void EarlyUpdate();
	virtual void Update(float _deltaTime);
	virtual void LateUpdate();
	virtual void Close();

	virtual void Load(Game* _pGame);
	virtual void UnLoad();

	virtual Actor* AddActor(Actor* _actor);
	void InitNewActors();
	virtual void DeleteActor(Actor* _actor);
};

#endif