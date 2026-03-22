#include "cBoxCollider.h"

#include <glew.h>

#include "Camera.h"
#include "cModel.h"
#include "Engine/Scene.h"
#include "Engine/3D/Mesh.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Utilitaries/Assets.h"

BoxCollider::BoxCollider(Actor* _pOwner):
	Collider3D(_pOwner)
{
	mColliderType = BOX;
	mTransform = new Transform3D(pOwner, LOCAL);
	mDebugModel = new Model(pOwner, mTransform, "Wireframe");
	mDebugModel->setMesh(Assets::GetMesh("Cube"));
	setDebugColor(Vector4(1.0f, 1.0f, 0.0f, 1.0f));
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

void BoxCollider::Destroy()
{
	Collider3D::Destroy();
	delete mTransform;
	mTransform = nullptr;
}