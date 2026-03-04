#include "cSphereCollider.h"

#include <glew.h>

#include "Engine/3D/Mesh.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/VertexArray.h"
#include "Engine/Utilitaries/Assets.h"

#include "Engine/Actor.h"

SphereCollider::SphereCollider(Actor* _pOwner):
	Collider3D(_pOwner)
{
	mColliderType = SPHERE;
	mDebugMesh = Assets::GetMesh("Sphere");
}
SphereCollider::~SphereCollider()
{
	Collider3D::~Collider3D();
	mDebugMesh = nullptr;
}

//TODO: Make it affect scale
//Return a Vec4 that contains xyz = Location, w = radius
Vector4 SphereCollider::GetSphere()
{
	Vector3 pos = pOwner->getTransform3D()->getLocation();
	return Vector4(pos.x, pos.y, pos.z, mRadius);
}

void SphereCollider::DrawDebug()
{
	Matrix4Row wt;
	wt =  Mat4RowCreateScale(Vector3{mRadius});
	wt *= Mat4RowCreateFromQuaternion(Quaternion::QuatIdentity());
	wt *= Mat4RowCreateTranslation(pOwner->getTransform3D()->getLocation());
	
	Assets::GetShader("Simple")->SetMatrix4Row("uWorldTransform", wt);
	Assets::GetShader("Simple")->SetVector4f("uColor", Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	
	mDebugMesh->getVertexArray()->SetActive();
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glDrawArrays(GL_TRIANGLES, 0, mDebugMesh->getVertexArray()->GetVerticesCount());
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}