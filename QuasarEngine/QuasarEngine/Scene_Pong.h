#ifndef SCENE_PONG_H
#define SCENE_PONG_H

#include "Scene.h"

class Scene_Pong : public Scene
{
private:
public:
	
private:
public:
	Scene_Pong(std::string _name);
	~Scene_Pong();

	void Start()					override;
	void Update(float _deltaTime)	override;
	void Close()					override;
};

#endif