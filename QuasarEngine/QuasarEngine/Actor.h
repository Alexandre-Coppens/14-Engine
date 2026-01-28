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
	std::string mName;
	Scene* pScene;
	ActorState mState;
	Transform2D mTransform;
	std::map<std::string, Component*> mComponentList;

public:
	std::string  getName()		const	{ return mName; }
	Scene*		 getScene()		const	{ return pScene;  }
	ActorState	 getState()		const	{ return mState;  }
	Transform2D* getTransform()			{ return &mTransform;  }
	
	Component* GetComponent(std::string c) {
		if (mComponentList.find(c) != mComponentList.end()) return mComponentList[c];
		return nullptr;
	}

	void SetActive(bool _b) { if (_b) mState = ActorState::Active; else mState = ActorState::Paused; }

public:
	Actor();
	~Actor();

	virtual	void	Start();
	virtual	void	Update(float _deltaTime);
	virtual	void	Destroy();

	virtual void AddComponent(Component* _c);
	virtual void RemoveComponent(std::string _c);
};

#endif // !ACTOR_H