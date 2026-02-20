#include "Camera.h"

#include "Actor.h"
#include "Log.h"
#include "MathLib.h"
#include "Scene.h"
#include "CameraManager.h"
#include "cTransform3D.h"

//TODO: Set the camera as a component and create a camera manager
Camera::Camera(Actor* _pOwner):
    Component(_pOwner, 0)
{
    mName = "Camera";
}

Camera::~Camera()
{
    delete mLocalTransform;
    mLocalTransform = nullptr;
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
    Vector3 target = mLocalTransform->getLocation() + mLocalTransform->Forward() * 100.f;
    Vector3 up = Vector3UnitZ(); // TODO: Change this when gravity so up = -gravity
    Log::Info(ToString(camPosition));
    Matrix4Row view = Mat4RowCreateLookAt(camPosition, target, up);
    pOwner->getScene()->getRendererGl()->setViewMatrix(view);
}
