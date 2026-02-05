#include "Scene_Pong.h"
#include "Log.h"
#include "Assets.h"

#include "Paddle.h"
#include "Box.h"
#include "Floor.h"
#include "RendererSdl.h"

Scene_Pong::Scene_Pong(std::string _name):
	Scene(_name)
{
}

void Scene_Pong::Start()
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
	Actor* box5 = AddActor(new Box());

	player->getTransform()->setLocation(Vector2{ 200, 500 });

	box1->getTransform()->setLocation(Vector2{350, 750});
	box1->getTransform()->setSize(Vector2{700, 100});

	box2->getTransform()->setLocation(Vector2{ 150, 550 });
	box2->getTransform()->setSize(Vector2{ 25, 25 });

	box3->getTransform()->setLocation(Vector2{ 400, 550 });
	box3->getTransform()->setSize(Vector2{ 125, 25 });

	box4->getTransform()->setLocation(Vector2{ 400, 350 });
	box4->getTransform()->setSize(Vector2{ 25, 25 });

	box5->getTransform()->setLocation(Vector2{ 650, 675 });
	box5->getTransform()->setSize(Vector2{ 50, 50 });
}

void Scene_Pong::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void Scene_Pong::Close()
{
}
