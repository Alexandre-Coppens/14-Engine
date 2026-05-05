#pragma once

#include "Engine/Actor.h"

class Camera;
class PhysicBody;
class BoxCollider;
class ActorCamera : public Actor
{
private:
	Camera* mCamera;
	BoxCollider* mCollider   {nullptr};
	PhysicBody* mPhysicBody  {nullptr};
	
	float mSpeed {2.0f};
public:

private:
public:
	ActorCamera();
	~ActorCamera() override;

	void Start()					override;
	void Update(float _deltaTime)	override;
	void Destroy()					override;
};
