#ifndef CAMERA_H
#define CAMERA_H

#include "Component.h"

class Camera : public Component
{
public:
    Camera(Actor* _pOwner);
    ~Camera() override;

    void Update(const float _deltaTime) override;
    void UpdateCameraView() const;
};

#endif // CAMERA_H
