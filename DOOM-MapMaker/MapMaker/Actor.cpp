#include "Actor.h"

map<string, Actor*> Actor::ActorList;
vector<vector<Actor*>> Actor::ActorsByLayer;

Actor::Actor(){
	CreateRect();
}

Actor::Actor(bool _enabled, string _name, Vector2 _pos, Vector2 _size, Texture2D* _sprite, ActorType _type) {
	enabled = _enabled;
	name = _name;
	position = _pos;
	size = _size;
	sprite = _sprite;
	type = _type;

	CreateRect();
}

Actor::~Actor(){
	ActorList.erase(name);
}

void Actor::Update() {
}

void Actor::Draw(Vector2 scroll) {
	DrawTextureRec(*sprite, rect, Vector2Add(position, scroll), WHITE);
}

bool Actor::IsCursorInBounds(){
	if (!enabled)return false;
	return GetMouseX() >= position.x && GetMouseX() <= position.x + size.x && GetMouseY() >= position.y && GetMouseY() <= position.y + size.y;
}

void Actor::CreateRect(){
	rect.x = 0;
	rect.y = 0;
	rect.width = size.x;
	rect.height = size.y;
}

void Actor::Collided(){
}

void Actor::CreateActor(const string id, Actor* gO){
	gO->name = id;
	ActorList[id] = gO;
}

Actor* Actor::GetActorWithName(string _name) {
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

vector<Actor*> Actor::GetAllActorsWith(ActorType type){
	vector<Actor*> ret;
	for(auto const& i : ActorList){
		if (i.second->type == type) {
			ret.push_back(const_cast<Actor*>(i.second));
		}
	}
    return ret;
}

void Actor::DestroyActorList(){
	ActorList.clear();
}

int Actor::Clicked() {
	return 0;
}

void Actor::Destroy() {
	needToDestroy = true;
}