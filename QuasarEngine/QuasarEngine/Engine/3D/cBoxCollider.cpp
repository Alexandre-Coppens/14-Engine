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
	mpParentTransform = pOwner->getTransform3D();
}

BoxCollider::~BoxCollider()
{
	Collider3D::~Collider3D();
}

Vector3 BoxCollider::getCenter()
{
	return pOwner->getTransform3D()->getLocation() + mOffset;
}

std::vector<Vector3> BoxCollider::getWorldVertices()
{
	Vector3 center = getCenter();
	return std::vector<Vector3>
	{
		center + getForward() * mSize.x * 0.5f + getRight() * mSize.y * 0.5f + getUp() * mSize.z * 0.5f ,
		center + getForward() * mSize.x * 0.5f + getRight() * mSize.y * 0.5f - getUp() * mSize.z * 0.5f ,
		center + getForward() * mSize.x * 0.5f - getRight() * mSize.y * 0.5f + getUp() * mSize.z * 0.5f ,
		center + getForward() * mSize.x * 0.5f - getRight() * mSize.y * 0.5f - getUp() * mSize.z * 0.5f ,
		center - getForward() * mSize.x * 0.5f + getRight() * mSize.y * 0.5f + getUp() * mSize.z * 0.5f ,
		center - getForward() * mSize.x * 0.5f + getRight() * mSize.y * 0.5f - getUp() * mSize.z * 0.5f ,
		center - getForward() * mSize.x * 0.5f - getRight() * mSize.y * 0.5f + getUp() * mSize.z * 0.5f ,
		center - getForward() * mSize.x * 0.5f - getRight() * mSize.y * 0.5f - getUp() * mSize.z * 0.5f ,
	};
}

void BoxCollider::DrawDebug()
{
	//Draw Box
	Matrix4Row wt;
	wt =  Mat4RowCreateScale(mSize * 0.5f);
	wt *= Mat4RowCreateFromQuaternion(mpParentTransform->getQRotation());
	wt *= Mat4RowCreateTranslation(getCenter());
	
	Assets::GetShader("Simple")->SetMatrix4Row("uWorldTransform", wt);
	Assets::GetShader("Simple")->SetVector4f("uColor", Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	
	mDebugMesh->getVertexArray()->SetActive();
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glDrawArrays(GL_TRIANGLES, 0, mDebugMesh->getVertexArray()->GetVerticesCount());

	//Draw Nearest Sphere
	wt =  Mat4RowCreateScale(mSize * 0.5f);
	wt *= Mat4RowCreateFromQuaternion(mpParentTransform->getQRotation());
	wt *= Mat4RowCreateTranslation(getCenter());
	
	Assets::GetShader("Simple")->SetMatrix4Row("uWorldTransform", wt);
	Assets::GetShader("Simple")->SetVector4f("uColor", Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	
	mDebugMesh->getVertexArray()->SetActive();
	
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glDrawArrays(GL_TRIANGLES, 0, mDebugMesh->getVertexArray()->GetVerticesCount());
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}
void BoxCollider::OnEnd()
{
	Collider3D::OnEnd();
	mDebugMesh = nullptr;
	mpParentTransform = nullptr;
}