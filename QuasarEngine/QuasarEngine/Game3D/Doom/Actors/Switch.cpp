#include "Switch.h"

#include "Engine/3D/cBoxCollider.h"
#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Time.h"
#include "Game3D/Doom/Actors/Door.h"

Switch::Switch(Door* _reference):
	DoomBaseActor(), referencedDoor(_reference)
{
	Initialize();
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
	mModel->AddTexture(Assets::GetTexture(PNG_Switch_Off));
	mTransform3D->setScale(Vector3{0.1f, 0.1f, 0.05f});
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
	if (isOpen) return;
	isOpen = true;
	referencedDoor->Unlock();
	referencedDoor->Interact();
	mModel->setTexture(Assets::GetTexture(PNG_Switch_On));
	DoomBaseActor::Interact();
}

