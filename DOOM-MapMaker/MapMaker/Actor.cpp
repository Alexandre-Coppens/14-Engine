#include "Actor.h"
#include "raymath.h"

map<string, Actor*> Actor::ActorList;
vector<vector<Actor*>> Actor::ActorsByLayer;

Actor::Actor(bool _enabled, string _name, Vector2 _anchor, Vector2 _pos, Vector2 _size, Texture2D* _sprite, short _layer):
	enabled(_enabled),
	name(_name),
	position(_pos),
	size(_size),
	sprite(_sprite),
	layer(_layer),
	anchor(_anchor)
{
	ActorList[name] = this;
	while (ActorsByLayer.size() <= layer)
	{
		ActorsByLayer.push_back({});
	}
	ActorsByLayer[layer].push_back(this);
	CreateRect();
}

Actor::~Actor()
{
	ActorList.erase(name);
}

// void Actor::Draw(Vector2 _scroll) {
// 	DrawTextureRec(*sprite, rect, Vector2Add(position, _scroll), WHITE);
// }

bool Actor::IsCursorInBounds()
{
	if (!enabled)return false;
	return CheckCollisionPointRec(GetMousePosition(), rect);
}

void Actor::CreateRect()
{
	float width = GetScreenWidth();
	rect.x = position.x + (anchor.x * GetScreenWidth())  - size.x * 0.5;
	rect.y = position.y + (anchor.y * GetScreenHeight()) - size.y * 0.5;
	rect.width = size.x;
	rect.height = size.y;
}

Actor* Actor::GetActorWithName(string _name)
{
	for (auto const& i : ActorList) {
		if (i.first == _name) {
			return const_cast<Actor*>(i.second);
		}
	}
	return nullptr;
}

vector<Actor*> Actor::GetAllActors()
{
	vector<Actor*> ret;
	for (auto const& i : ActorList) {
		ret.push_back(const_cast<Actor*>(i.second));
	}
	return ret;
}

vector<vector<Actor*>>* Actor::GetAllActorsLayered()
{
	return &ActorsByLayer;
}

void Actor::DestroyActorList()
{
	ActorList.clear();
	for (auto& i : ActorList)
	{
		delete i.second;
		i.second = nullptr;
	}
}

void Actor::Destroy()
{
	needToDestroy = true;
}