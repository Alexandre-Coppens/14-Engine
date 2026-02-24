#ifndef SCENE_TEST_H
#define SCENE_TEST_H

#include "Engine/Scene.h"

class Scene_Test : public Scene
{
private:

protected:

public:
	Scene_Test(std::string _name);
	~Scene_Test();

	void Start()					override;
	void Update(float _deltaTime)	override;
	void Close()					override;
};

#endif