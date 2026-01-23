#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Actor;

class Component
{
protected:
	bool bIsActive				{ true };
	Actor* pOwner				{ nullptr };
	uint8_t u8UpdateOrder		{ 0 };

	std::string sName			{ "Actor" };

public:
	void SetActive(bool _b) { bIsActive = _b; }
	bool GetIsActive() const { return bIsActive; }

	Actor*		GetOwner()			const { return pOwner; }
	uint8_t		GetUpdateOrder()	const { return u8UpdateOrder; }
	std::string	GetName()			const { return sName; }

protected:
public:
	Component(Actor* _pOwner, uint8_t _u8UpdateOrder = 0);
	virtual ~Component();

	virtual void OnStart();
	virtual void Update() = 0;
	virtual void OnEnd();
};

#endif