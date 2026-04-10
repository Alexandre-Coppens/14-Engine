#pragma once
#include "DoomBaseActor.h"
#include "Engine/3D/cModel.h"

class BoxCollider;
class Target : public DoomBaseActor
{
private:
    Model* mModel            {nullptr};
    BoxCollider* mCollider   {nullptr};

    int mMaxLife { 3 };
    int mLife    { 0 };

    float mResurectTime { 3.0f };
    float mResurecting  { 0.0f };
    
public:
    Model* getModel() const {return mModel;}

private:
    void GetDown();
    void GetUp();
    
public:
    Target();
    ~Target() override;

    virtual void Initialize()               override;
    virtual void Start()					override;
    virtual void Update(float _deltaTime)	override;
    virtual void Destroy()					override;

    void Interact() override;
    void Shoot()    override;
};
