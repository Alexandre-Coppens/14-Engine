#include "Switch.h"

#include "Engine/3D/cBoxCollider.h"
#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Time.h"
#include "Game3D/Doom/Actors/Door.h"

Switch::Switch(Door* _reference):
	DoomBaseActor(), referencedDoor(_reference)
{
}

Switch::~Switch() = default;

void Switch::Initialize()
{
	mModel = dynamic_cast<Model*>(AddComponent(new Model(this, "BasicModel")));
	mCollider = dynamic_cast<BoxCollider*>(AddComponent(new BoxCollider(this)));
	DoomBaseActor::Initialize();
}

void Switch::Start()
{
	referencedDoor->Lock();
	mModel->setMesh(Assets::GetMesh(OBJ_Plane));
	mModel->AddTexture(Assets::GetTexture(PNG_Door));
	mTransform3D->addRotationY(-90.0f);
	DoomBaseActor::Start();
}

void Switch::Update(float _deltaTime)
{
	DoomBaseActor::Update(_deltaTime);
}

void Switch::Destroy()
{
	DoomBaseActor::Destroy();
}

void Switch::Interact()
{
	referencedDoor->Unlock();
	referencedDoor->Interact();
	DoomBaseActor::Interact();
}

