#pragma once
#include "DoomBaseActor.h"
#include "Engine/Actor.h"
#include "Engine/3D/cModel.h"

class Door;
class BoxCollider;
class Camera;
class Switch : public DoomBaseActor
{
private:
	Model* mModel            {nullptr};
	BoxCollider* mCollider   {nullptr};
    
	Door* referencedDoor     {nullptr};

	bool isOpen				 {false};
    
public:
	Model* getModel() const {return mModel;}

private:
public:
	Switch(Door* _reference);
	~Switch() override;

	virtual void Initialize()               override;
	virtual void Start()					override;
	virtual void Update(float _deltaTime)	override;
	virtual void Destroy()					override;
    
	void Interact() override;

};