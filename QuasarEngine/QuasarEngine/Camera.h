#ifndef CAMERA_H
#define CAMERA_H

#include "CommonLib.h"
#include "Component.h"

class Transform3D;
class Camera : public Component
{
private:
    Transform3D* mLocalTransform;
    
public:
    Transform3D* getLocalTransform() const {return mLocalTransform;}
    
public:
    Camera(Actor* _pOwner);
    ~Camera() override;

    void OnStart() override;
    void Update(const float _deltaTime) override;
    void UpdateCameraView() const;
};

#endif // CAMERA_H
