#include "cSphereCollider.h"

#include <glew.h>

#include "cModel.h"
#include "Engine/3D/Mesh.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/VertexArray.h"
#include "Engine/Utilitaries/Assets.h"

#include "Engine/Actor.h"

SphereCollider::SphereCollider(Actor* _pOwner):
	Collider3D(_pOwner)
{
	mColliderType = SPHERE;
	mDebugModel = new Model(pOwner, "Wireframe");
	mDebugModel->setMesh(Assets::GetMesh("Sphere"));
}

SphereCollider::~SphereCollider()
{
	Collider3D::~Collider3D();
}

Vector3 SphereCollider::getCenter()
{
	return pOwner->getTransform3D()->getLocation();
}

//TODO: Make it affect scale
//Return a Vec4 that contains xyz = Location, w = radius
Vector4 SphereCollider::GetSphere()
{
	Vector3 pos = pOwner->getTransform3D()->getLocation();
	return Vector4(pos.x, pos.y, pos.z, mRadius);
}