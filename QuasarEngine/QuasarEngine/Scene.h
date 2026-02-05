#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <map>

class IRenderer;
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
	static Scene* sActiveScene;

	IRenderer* getRenderer()	const	{ return pRenderer; }
	std::string  getSceneName()	const	{ return mName; }
	Game*		 getGame()		const	{ return pGame; }

	void setRenderer(IRenderer* _pRenderer) { pRenderer = _pRenderer; }

private:
	void KillActors();

public:
	Scene(std::string _name = "Scene");
	virtual void Start();
	virtual void EarlyUpdate();
	virtual void Update(float _deltaTime);
	virtual void LateUpdate();
	virtual void Close();

	virtual void Load(Game* _pGame);
	virtual void UnLoad();

	virtual Actor* AddActor(Actor* _actor);
	virtual void DeleteActor(Actor* _actor);
};

#endif