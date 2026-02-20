#include "Scene_Pong.h"
#include "CommonLib.h"
#include "Assets.h"

#include "Paddle.h"
#include "Box.h"
#include "Coin.h"
#include "RendererSdl.h"

Scene_Pong::Scene_Pong(std::string _name):
	Scene(std::move(_name))
{
}

Scene_Pong::~Scene_Pong()
{
	Scene::~Scene();
}


void Scene_Pong::Start()
{
	Scene::Start();

	RendererSdl* sdl = dynamic_cast<RendererSdl*>(pRenderer);
	Assets::LoadTexture(*sdl, "Resources/pokeball.png", "ball");
	Assets::LoadTexture(*sdl, "Resources/Block.png", "Block");
	Assets::LoadTexture(*sdl, "Resources/MegaAnim/00_megaman.png", "00_megaman");
	Assets::LoadTexture(*sdl, "Resources/MegaAnim/01_megaman.png", "01_megaman");
	Assets::LoadTexture(*sdl, "Resources/MegaAnim/02_megaman.png", "02_megaman");
	Assets::LoadTexture(*sdl, "Resources/MegaAnim/03_megaman.png", "03_megaman");
	Assets::LoadTexture(*sdl, "Resources/MegaAnim/04_megaman.png", "04_megaman");
	Assets::LoadTexture(*sdl, "Resources/MegaAnim/05_megaman.png", "05_megaman");
	Assets::LoadTexture(*sdl, "Resources/MegaAnim/06_megaman.png", "06_megaman");
	Assets::LoadTexture(*sdl, "Resources/MegaAnim/07_megaman.png", "07_megaman");

	Assets::LoadTexture(*sdl, "Resources/CoinAnim/Coin-01.png", "00_coin");
	Assets::LoadTexture(*sdl, "Resources/CoinAnim/Coin-02.png", "01_coin");
	Assets::LoadTexture(*sdl, "Resources/CoinAnim/Coin-03.png", "02_coin");
	Assets::LoadTexture(*sdl, "Resources/CoinAnim/Coin-04.png", "03_coin");
	Assets::LoadTexture(*sdl, "Resources/CoinAnim/Coin-05.png", "04_coin");
	Assets::LoadTexture(*sdl, "Resources/CoinAnim/Coin-06.png", "05_coin");


	Actor* player = AddActor(new Paddle());

	Actor* box1 = AddActor(new Box());
	Actor* box2 = AddActor(new Box());
	Actor* box3 = AddActor(new Box());
	Actor* box4 = AddActor(new Box());
	Actor* box5 = AddActor(new Box());

	Actor* coin1 = AddActor(new Coin());
	Actor* coin2 = AddActor(new Coin());
	Actor* coin3 = AddActor(new Coin());

	player->getTransform2D()->setLocation(Vector2{ 200, 500 });

	box1->getTransform2D()->setLocation(Vector2{350, 750});
	box1->getTransform2D()->setSize(Vector2{700, 100});

	box2->getTransform2D()->setLocation(Vector2{ 150, 550 });
	box2->getTransform2D()->setSize(Vector2{ 25, 25 });

	box3->getTransform2D()->setLocation(Vector2{ 400, 550 });
	box3->getTransform2D()->setSize(Vector2{ 125, 25 });

	box4->getTransform2D()->setLocation(Vector2{ 400, 350 });
	box4->getTransform2D()->setSize(Vector2{ 25, 25 });

	box5->getTransform2D()->setLocation(Vector2{ 650, 675 });
	box5->getTransform2D()->setSize(Vector2{ 50, 50 });

	coin1->getTransform2D()->setLocation(Vector2{ 500, 475 });
	coin1->getTransform2D()->setSize(Vector2{ 50, 50 });

	coin2->getTransform2D()->setLocation(Vector2{ 400, 475 });
	coin2->getTransform2D()->setSize(Vector2{ 50, 50 });

	coin3->getTransform2D()->setLocation(Vector2{ 300, 475 });
	coin3->getTransform2D()->setSize(Vector2{ 50, 50 });

}

void Scene_Pong::Update(const float _deltaTime)
{
	Scene::Update(_deltaTime);
}

void Scene_Pong::Close()
{
}
