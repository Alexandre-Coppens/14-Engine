#include "cBoxCollider.h"

#include <glew.h>

#include "Engine/3D/Mesh.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/VertexArray.h"
#include "Engine/Utilitaries/Assets.h"

BoxCollider::BoxCollider(Actor* _pOwner):
	Collider3D(_pOwner)
{
	mColliderType = BOX;
	mDebugMesh = Assets::GetMesh("Cube");
}

BoxCollider::~BoxCollider()
{
	Collider3D::~Collider3D();
	mDebugMesh = nullptr;
}

void BoxCollider::DrawDebug()
{
	Matrix4Row wt;
	wt =  Mat4RowCreateScale(mSize);
	wt *= Mat4RowCreateFromQuaternion(Quaternion::QuatIdentity());
	wt *= Mat4RowCreateTranslation(getCenter());
	
	Assets::GetShader("Simple")->SetMatrix4Row("uWorldTransform", wt);
	Assets::GetShader("Simple")->SetVector4f("uColor", Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	
	mDebugMesh->getVertexArray()->SetActive();
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glDrawArrays(GL_TRIANGLES, 0, mDebugMesh->getVertexArray()->GetVerticesCount());
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}