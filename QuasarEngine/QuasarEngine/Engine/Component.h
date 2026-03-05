#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Actor;
class Component
{
protected:
	bool mIsActive				 { true };
	Actor* pOwner				 { nullptr };
	uint8_t mUpdateOrder		 { 1 };

	std::string mName		  { "Component" };

public:
	std::string getName()		const { return mName; }
	Actor* getOwner()			const { return pOwner; }
	bool getIsActive()			const { return mIsActive; }
	uint8_t getUpdateOrder()	const { return mUpdateOrder; }

	void setActive(const bool _b) { mIsActive = _b; }

protected:
public:
	Component(Actor* _pOwner, uint8_t _updateOrder = 0);
	virtual ~Component();

	virtual void OnStart();
	virtual void OnActorStart();
	virtual void Update(float _deltaTime) = 0;
	virtual void OnEnd();
};

#endif