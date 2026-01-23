#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <map>

class Renderer;
class Actor;

class Scene
{
private:
protected:
	std::string sName;
	Renderer* pRenderer;

	std::vector<Actor*> vActorList;
	std::vector<Actor*> vAddActorList;
	std::vector<Actor*> vDestroyActorList;

public:
	static Scene* ActiveScene;

	std::string GetSceneName() const { return sName; }
	Renderer* GetRenderer() { return pRenderer; }
	void SetRenderer(Renderer* _pRenderer) { pRenderer = _pRenderer; }

private:
	void KillActors();

public:
	Scene(std::string _sName = "Scene");
	virtual void Start();
	virtual void EarlyUpdate();
	virtual void Update(float deltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void Close();

	virtual void Load();
	virtual void UnLoad();

	virtual void AddActor(Actor* actor);
	virtual void DeleteActor(Actor* actor);
};

#endif