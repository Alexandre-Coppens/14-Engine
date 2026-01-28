#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <map>

class RendererSdl;
class Actor;

class Scene
{
private:
protected:
	std::string mName;
	RendererSdl* pRenderer;

	std::vector<Actor*> mActorList;
	std::vector<Actor*> mAddActorList;
	std::vector<Actor*> mDestroyActorList;

public:
	static Scene* sActiveScene;

	RendererSdl*	getRenderer()	const	{ return pRenderer; }
	std::string getSceneName()	const	{ return mName; }
	
	void setRenderer(RendererSdl* _pRenderer) { pRenderer = _pRenderer; }

private:
	void KillActors();

public:
	Scene(std::string _name = "Scene");
	virtual void Start();
	virtual void EarlyUpdate();
	virtual void Update(float _deltaTime);
	virtual void LateUpdate();
	virtual void Close();

	virtual void Load();
	virtual void UnLoad();

	virtual void AddActor(Actor* _actor);
	virtual void DeleteActor(Actor* _actor);
};

#endif