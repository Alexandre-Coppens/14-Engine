#ifndef SCENE_PONG_H
#define SCENE_PONG_H

#include "Engine/Scene.h"

class Scene_Pong : public Scene
{
private:
public:
	
private:
public:
	Scene_Pong(std::string _name);
	~Scene_Pong() override;

	void Start()					override;
	void Update(float _deltaTime)	override;
	void Close()					override;
};

#endif