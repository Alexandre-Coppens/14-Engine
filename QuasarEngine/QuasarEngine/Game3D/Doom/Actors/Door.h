#pragma once
#include "Engine/Actor.h"
#include "Engine/3D/cModel.h"

class BoxCollider;
class Camera;
class Door : public Actor
{
private:
    Model* mModel            {nullptr};
    BoxCollider* mCollider   {nullptr};

    float openHeight    {1.0f};
    float currentHeight {0.0f};
    float speed         {1.0f};
    
    bool isOpen      {false};
    bool needOpening {false};
    bool needClosing {false};
    
public:
    Model* getModel() const {return mModel;}

private:
public:
    Door();
    ~Door() override;

    void Initialize()               override;
    void Start()					override;
    void Update(float _deltaTime)	override;
    void Destroy()					override;

    void Interact();
    void Open();
    void Close();
};
