#ifndef SCENE_GAMEOVER_H
#define SCENE_GAMEOVER_H

#include "Scene.h"

#include "CommonLib.h"

class Scene_GameOver : public Scene
{
private:
protected:

public:
	Scene_GameOver(std::string _name);
	void Start()					override;
	void Update(float _deltaTime)	override;
	void Close()					override;
};

#endif