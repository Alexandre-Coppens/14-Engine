#pragma once
#include "Engine/Scene.h"

class Scene_Bowling : public Scene
{
private:

protected:

public:
	Scene_Bowling(std::string _name);
	~Scene_Bowling() override;

	void Start()					override;
	void Update(float _deltaTime)	override;
	void Close()					override;
};