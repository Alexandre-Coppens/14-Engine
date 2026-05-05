#pragma once
#include "Engine/Scene.h"

class Scene_Cube : public Scene
{
private:

protected:

public:
	Scene_Cube(std::string _name);
	~Scene_Cube() override;

	void Start()					override;
	void Update(float _deltaTime)	override;
	void Close()					override;
};