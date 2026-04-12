#pragma once
#include "DoomBaseActor.h"
#include "Engine/Actor.h"
#include "Engine/3D/cModel.h"

class BoxCollider;
class Camera;
class Door : public DoomBaseActor
{
private:
    Model* mModel            {nullptr};
    BoxCollider* mCollider   {nullptr};
    
    bool isLocked       {false};
    
    float startHeight   {0.0f};
    float openHeight    {1.0f};
    float currentHeight {0.0f};
    float speed         {1.0f};
    
    float openTimer     {3.0f};
    float currentTimer  {3.0f};
    
    bool needOpening {false};
    bool needClosing {false};
    bool needWaiting {false};
    
public:
    Model* getModel() const {return mModel;}

private:
public:
    Door();
    ~Door() override;

    virtual void Initialize()               override;
    virtual void Start()					override;
    virtual void Update(float _deltaTime)	override;
    virtual void Destroy()					override;

    void Lock()   {isLocked = true; }
    void Unlock() {isLocked = false;}
    
    void Interact() override;
    void Open();
    void Wait();
    void Close();
};
