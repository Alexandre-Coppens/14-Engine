#include "cBoxCollider.h"

#include <glew.h>

#include "Engine/3D/Mesh.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/VertexArray.h"
#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Log.h"

BoxCollider::BoxCollider(Actor* _pOwner):
	Collider3D(_pOwner)
{
	mColliderType = BOX;
	mDebugMesh = Assets::GetMesh("Cube");
	mTransform = new Transform3D(pOwner, LOCAL);
}

BoxCollider::~BoxCollider()
{
	Collider3D::~Collider3D();
}

Vector3 BoxCollider::getCenter()
{
	return mTransform->getWorldLocation();
}

Vector3 BoxCollider::getScale()
{
	return mTransform->getWorldScale();
}

std::vector<Vector3> BoxCollider::getWorldVertices()
{
	std::string name = pOwner->getName();
	Vector3 center = getCenter();
	Vector3 scale = getScale();
	Log::Info(pOwner->getName() + " : " + ToString(center));
	return std::vector<Vector3>
	{
		center + (getForward() * scale.x + getRight() * scale.y + getUp() * scale.z) * 1,
		center + (getForward() * scale.x + getRight() * scale.y - getUp() * scale.z) * 1,
		center + (getForward() * scale.x - getRight() * scale.y + getUp() * scale.z) * 1,
		center + (getForward() * scale.x - getRight() * scale.y - getUp() * scale.z) * 1,
		center + (getForward() * scale.x * -1 + getRight() * scale.y + getUp() * scale.z) * 1 ,
		center + (getForward() * scale.x * -1 + getRight() * scale.y - getUp() * scale.z) * 1 ,
		center + (getForward() * scale.x * -1 - getRight() * scale.y + getUp() * scale.z) * 1 ,
		center + (getForward() * scale.x * -1 - getRight() * scale.y - getUp() * scale.z) * 1 ,
	};
}

void BoxCollider::DrawDebug()
{
	//Draw Box
	Matrix4Row wt = mTransform->getWorldTransform();
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
	delete mTransform;
	mTransform = nullptr;
	mDebugMesh = nullptr;
}