#include "Component.h"

class Camera : public Component
{
private:
public:
private:
public:
    Camera(Actor* _pOwner);
    ~Camera() override;

    void Update(const float _deltaTime) override;
};
