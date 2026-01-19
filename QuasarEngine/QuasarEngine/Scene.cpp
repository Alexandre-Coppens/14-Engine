#include "Scene.h"

#include "Renderer.h"
#include "Actor.h"

Scene::Scene(std::string _sName):
	sName(_sName)
{
}

void Scene::Start()
{
}

//Update Before Inputs
void Scene::EarlyUpdate()
{
}

void Scene::Update(float deltaTime)
{
	for (Actor* actor : vActorList)
	{
		actor->Update(deltaTime);
	}
}

//Update After Rendering
void Scene::LateUpdate()
{
}

void Scene::Render()
{
	Rectangle rect;
	for (Actor* actor : vActorList)
	{
		rect = Rectangle{ actor->GetTransform()->GetLocation(), Vector2 {50, 50} };
		pRenderer->DrawRect(rect);
	}
}

void Scene::Close()
{
}