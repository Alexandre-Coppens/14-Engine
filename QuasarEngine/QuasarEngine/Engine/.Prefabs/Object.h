#pragma once
#include "Engine/Utilitaries/Assets.h"

#include "Engine/Actor.h"
#include "Engine/3D/cModel.h"

class Collider3D;
class Object : public Actor
{
private:
    GENERATED_MESHES mMesh;
    GENERATED_TEXTURE mTexture;
    std::string mShaderName;
    
    Model* mModel            {nullptr};
    Collider3D* mCollider    {nullptr};

public:
    Model* getModel() const {return mModel;}

private:
public:
    Object(std::string _name, GENERATED_MESHES _model, GENERATED_TEXTURE _texture, std::string _shader);
    ~Object() override;
    
    void Initialize()               override;
    void Start()					override;
    void Update(float _deltaTime)	override;
    void Destroy()					override;
};
