#ifndef ACTOR_H
#define ACTOR_H

#include <map>
#include <string>
#include <vector>

#include "cTransform2D.h"
#include "cTransform3D.h"

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
	Transform2D mTransform2D;
	Transform3D mTransform3D;
	std::vector<Component*> mComponentList;

public:
	std::string  getName()		const	{ return mName; }
	Scene*		 getScene()		const	{ return pScene;  }
	ActorState	 getState()		const	{ return mState;  }
	Transform2D* getTransform2D()			{ return &mTransform2D;  }
	Transform3D* getTransform3D()			{ return &mTransform3D;  }
	
	template<typename T>
	T* GetComponent() {
		for (auto it = mComponentList.begin(); it != mComponentList.end(); it++)
		{
			T* component = dynamic_cast<T*>(*it);
			if (component != nullptr) return component;
		}
		return nullptr;
	}

	template<typename T>
	std::vector<T*> GetComponents() {
		std::vector<T*> list;
		for (auto it = mComponentList.begin(); it != mComponentList.end(); it++)
		{
			T* component = dynamic_cast<T*>(*it);
			if (component != nullptr)
				list.push_back(component);
		}
		return list;
	}

	void SetActive(bool _b) { if (_b) mState = ActorState::Active; else mState = ActorState::Paused; }

public:
	Actor();
	~Actor();

	virtual	void	Start();
	virtual	void	Update(float _deltaTime);
	virtual	void	Destroy();

	virtual void AddComponent(Component* _c);
	void RemoveComponents();
};

#endif // !ACTOR_H