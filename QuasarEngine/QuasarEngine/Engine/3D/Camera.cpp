#include "Camera.h"

#include "Engine/Utilitaries/MathLib.h"
#include "Engine/Utilitaries/CameraManager.h"

#include "Engine/Actor.h"
#include "Engine/Scene.h"
#include "Engine/3D/cTransform3D.h"

//TODO: Set the camera as a component and create a camera manager
Camera::Camera(Actor* _pOwner):
    Component(_pOwner, 0)
{
    mName = "Camera";
}

Camera::~Camera()
{
}

void Camera::OnStart()
{
    Component::OnStart();
    mLocalTransform = new Transform3D();
    CameraManager::AddCamera(this);
}

void Camera::Update(const float _deltaTime)
{
}

void Camera::UpdateCameraView() const
{
    Vector3 camPosition = pOwner->getTransform3D()->getLocation() + mLocalTransform->getLocation();
    Vector3 target = camPosition + mLocalTransform->Forward() * 100.f;
    Vector3 up = Vector3UnitZ(); // TODO: Change this when gravity so up = -gravity
    Matrix4Row view = Mat4RowCreateLookAt(camPosition, target, up);
    pOwner->getScene()->getRendererGl()->setViewMatrix(view);
}
void Camera::OnEnd()
{
    Component::OnEnd();
    CameraManager::RemoveCamera(this);
    
    delete mLocalTransform;
    mLocalTransform = nullptr;
}