#include "cTransform3D.h"
#include "Engine/Actor.h"

Transform3D::Transform3D(Actor* _pOwner, Space _space) :
    Component(_pOwner, 0), mSpace(_space)
{
    mName = "Transform3D";
}

Transform3D::~Transform3D()
{
}

void Transform3D::OnStart()
{
}

void Transform3D::Update(float _deltaTime)
{
    ComputeWorldTransform();
}

void Transform3D::Destroy()
{
    Component::Destroy();
}

void Transform3D::ComputeWorldTransform()
{
    if (!mNeedsUpdate) return;
    mWorldScale = Vector3One();
    mWorldRotation = Vector3Zero();
    mWorldLocation = Vector3Zero();
    if (mSpace == LOCAL)
    { //pOwner is not found
        mWorldScale *= pOwner->getTransform3D()->getScale();
        mWorldRotation += pOwner->getTransform3D()->getRotation();
        mWorldLocation += pOwner->getTransform3D()->getLocation();
    }
    mWorldScale *= getScale();
    mWorldRotation += getRotation();
    mWorldLocation += getLocation();
    //mWorldLocation *= 0.2f;
    mRotation.x = Fmod(mRotation.x, 360.0f);
    mWorldRotation.x = Fmod(mWorldRotation.x, 360.0f);
    computeRotations();

    mWorldTransform = Mat4RowCreateScale(mWorldScale);
    mWorldTransform *= Mat4RowCreateFromQuaternion(mWorldQRotation);
    mWorldTransform *= Mat4RowCreateTranslation(mWorldLocation);
    mNeedsUpdate = false;

    if (mSpace == WORLD)
    {
        if (pOwner == nullptr) return;
        const std::vector<Component*> components = pOwner->getComponentList();
        if (components.empty()) return;
        for (Component* c : components)
        {
            c->RecalculateTransform();
        }
    }
}
