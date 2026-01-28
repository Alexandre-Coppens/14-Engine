#include "Scene_Pong.h"
#include "Log.h"
#include "Assets.h"

#include "Paddle.h"
#include "Box.h"

Scene_Pong::Scene_Pong(std::string _name):
	Scene(_name)
{
}

void Scene_Pong::Start()
{
	Scene::Start();
	Log::Info("GAME: Loading Scene: '" + mName + "'.");

	Assets::LoadTexture(*pRenderer, "Ressources/pokeball.png", "ball");
	Assets::LoadTexture(*pRenderer, "Ressources/MegaAnim/00_megaman.png", "00_megaman");
	Assets::LoadTexture(*pRenderer, "Ressources/MegaAnim/01_megaman.png", "01_megaman");
	Assets::LoadTexture(*pRenderer, "Ressources/MegaAnim/02_megaman.png", "02_megaman");
	Assets::LoadTexture(*pRenderer, "Ressources/MegaAnim/03_megaman.png", "03_megaman");
	Assets::LoadTexture(*pRenderer, "Ressources/MegaAnim/04_megaman.png", "04_megaman");
	Assets::LoadTexture(*pRenderer, "Ressources/MegaAnim/05_megaman.png", "05_megaman");
	Assets::LoadTexture(*pRenderer, "Ressources/MegaAnim/06_megaman.png", "06_megaman");
	Assets::LoadTexture(*pRenderer, "Ressources/MegaAnim/07_megaman.png", "07_megaman");

	AddActor(new Paddle());
	AddActor(new Box());
}

void Scene_Pong::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Scene_Pong::Close()
{
}
