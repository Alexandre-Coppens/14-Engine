#include "Scene_GameOver.h"
#include "Assets.h"

#include "Paddle.h"
#include "Box.h"
#include "RendererSdl.h"

Scene_GameOver::Scene_GameOver(std::string _name) :
	Scene(_name)
{
}

void Scene_GameOver::Start()
{
	Scene::Start();
	
	RendererSdl* sdl = dynamic_cast<RendererSdl*>(pRenderer);
	Assets::LoadTexture(*sdl, "Ressources/pokeball.png", "ball");
	Assets::LoadTexture(*sdl, "Ressources/Block.png", "Block");
	Assets::LoadTexture(*sdl, "Ressources/MegaAnim/00_megaman.png", "00_megaman");
	Assets::LoadTexture(*sdl, "Ressources/MegaAnim/01_megaman.png", "01_megaman");
	Assets::LoadTexture(*sdl, "Ressources/MegaAnim/02_megaman.png", "02_megaman");
	Assets::LoadTexture(*sdl, "Ressources/MegaAnim/03_megaman.png", "03_megaman");
	Assets::LoadTexture(*sdl, "Ressources/MegaAnim/04_megaman.png", "04_megaman");
	Assets::LoadTexture(*sdl, "Ressources/MegaAnim/05_megaman.png", "05_megaman");
	Assets::LoadTexture(*sdl, "Ressources/MegaAnim/06_megaman.png", "06_megaman");
	Assets::LoadTexture(*sdl, "Ressources/MegaAnim/07_megaman.png", "07_megaman");

	Actor* player = AddActor(new Paddle());
	Actor* box1 = AddActor(new Box());
	Actor* box2 = AddActor(new Box());
	Actor* box3 = AddActor(new Box());
	Actor* box4 = AddActor(new Box());

	player->getTransform()->setLocation(Vector2{ 150, 400 });

	box1->getTransform()->setLocation(Vector2{ 400, 150 });
	box1->getTransform()->setSize(Vector2{ 800, 300 });

	box2->getTransform()->setLocation(Vector2{ 300, 650 });
	box2->getTransform()->setSize(Vector2{ 600, 300 });

	box3->getTransform()->setLocation(Vector2{ 50, 400 });
	box3->getTransform()->setSize(Vector2{ 100, 800 });

	box4->getTransform()->setLocation(Vector2{ 750, 400 });
	box4->getTransform()->setSize(Vector2{ 100, 800 });
}

void Scene_GameOver::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Scene_GameOver::Close()
{
}
