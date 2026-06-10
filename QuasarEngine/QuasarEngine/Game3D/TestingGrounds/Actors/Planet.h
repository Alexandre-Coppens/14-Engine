#pragma once
#include "Engine/Actor.h"
#include "Engine/3D/cModel.h"
#include "Engine/3D/cPhysicBody.h"

class Camera;
class Planet : public Actor
{
private:
    Model* mModel            {nullptr};
    PhysicBody* mPhysicBody  {nullptr};
    
    GENERATED_MESHES mMesh;
    GENERATED_SHADER_PROGRAMS mShader;
    GENERATED_TEXTURE mTexture;
    float mConstantRotation {0.0f};

public:
    Model* getModel() const {return mModel;}

private:
public:
    Planet( GENERATED_MESHES _mesh, GENERATED_SHADER_PROGRAMS _shader, GENERATED_TEXTURE _texture, float _constantRotation);
    ~Planet() override;

    void Initialize()               override;
    void Start()					override;
    void Update(float _deltaTime)	override;
    void Destroy()					override;
};
