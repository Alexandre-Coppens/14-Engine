#include "ActorCamera.h"

#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Camera.h"

ActorCamera::ActorCamera() :
	Actor()
{
	mName = "Player";
}

ActorCamera::~ActorCamera()
{
}

void ActorCamera::Start()
{
	mCamera = dynamic_cast<Camera*>(AddComponent(new Camera(this)));
	Actor::Start();
}

void ActorCamera::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
}

void ActorCamera::Destroy()
{
	Actor::Destroy();
}
