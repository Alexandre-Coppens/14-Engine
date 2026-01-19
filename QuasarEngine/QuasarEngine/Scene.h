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

public:
	std::string GetSceneName() const { return sName; }
	void SetRenderer(Renderer* _pRenderer) { pRenderer = _pRenderer; }

private:
public:
	Scene(std::string _sName = "Scene");
	virtual void Start();
	virtual void EarlyUpdate();
	virtual void Update(float deltaTime);
	virtual void LateUpdate();
	virtual void Render();
	virtual void Close();
};

#endif