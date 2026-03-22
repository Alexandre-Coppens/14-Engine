#include "ActorCamera.h"

#include "Engine/Game.h"
#include "Engine/Utilitaries/Assets.h"

#include "Engine/3D/Camera.h"
#include "Engine/3D/cBoxCollider.h"
#include "Engine/3D/cPhysicBody.h"
#include "Engine/Utilitaries/Managers/Inputs.h"
#include "Game3D/TestingGrounds/Scenes/Scene_Cube.h"

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
	mPhysicBody = dynamic_cast<PhysicBody*>(AddComponent(new PhysicBody(this, BOX)));
	mCollider = dynamic_cast<BoxCollider*>(mPhysicBody->getReferencedCollider());
	
	mPhysicBody->setGravityEnabled(false);
	mCollider->setSize(1.0f);

	Actor::Start();
}

void ActorCamera::Update(const float _deltaTime)
{
	if (Inputs::GetKey(SDLK_z))
	{
		mTransform3D->addLocation(mCamera->getLocalTransform()->Forward() * mSpeed * _deltaTime);
	}

	if (Inputs::GetKey(SDLK_s))
	{
		mTransform3D->addLocation(mCamera->getLocalTransform()->Forward() * -mSpeed * _deltaTime);
	}

	if (Inputs::GetKey(SDLK_q))
	{
		mTransform3D->addLocation(mCamera->getLocalTransform()->Right() * -mSpeed * _deltaTime);
	}

	if (Inputs::GetKey(SDLK_d))
	{
		mTransform3D->addLocation(mCamera->getLocalTransform()->Right() * mSpeed * _deltaTime);
	}
    
	if (Inputs::GetKeyDown(SDLK_r))
	{
		getScene()->getGame()->SetScene<Scene_Cube>();
	}
    
	//Rotation is stocked in a vector before being transformed to quat via ZYX order
	const float pitch = Inputs::GetMouseDeltaY() * 10.0f * _deltaTime;
	const float yaw = Inputs::GetMouseDeltaX() * 10.0f * _deltaTime;
    
	mCamera->getLocalTransform()->addRotationZ(yaw);
	mCamera->getLocalTransform()->addRotationY(pitch);
	mCamera->getLocalTransform()->clampRotationY(-89.0f, 89.0f);
    
	Actor::Update(_deltaTime);
}

void ActorCamera::Destroy()
{
	Actor::Destroy();
}
