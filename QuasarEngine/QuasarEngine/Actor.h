#ifndef ACTOR_H
#define ACTOR_H

#include <map>
#include <string>

#include "cTransform2D.h"

enum class ActorState
{
	Active,
	Paused,
	Destroyed
};

class Scene;
class Component;

class Actor
{
protected:
	std::string sName;
	Scene* pScene;
	ActorState eState;
	Transform2D transform;
	std::map<std::string, Component*> vComponentList;

public:
	Scene* GetScene()			const	{ return pScene; }
	ActorState GetState()		const	{ return eState;  }
	Transform2D* GetTransform()			{ return &transform;  }
	
	Component* GetComponent(std::string c) {
		if (vComponentList.find(c) == vComponentList.end()) return vComponentList[c];
		return nullptr;
	}

	void SetActive(bool b) { if (b) eState = ActorState::Active; else eState = ActorState::Paused; }

public:
	Actor(Scene* _pScene);
	~Actor();

	virtual	void	Start();
	virtual	void	Update(float deltaTime);
	virtual	void	Destroy();

	virtual void AddComponent(Component* c);
	virtual void RemoveComponent(std::string c);
};

#endif // !ACTOR_H