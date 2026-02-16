#ifndef SCENE_PONG_H
#define SCENE_PONG_H

#include "Scene.h"
#include "CommonLib.h"

class Scene_Pong : public Scene
{
private:
protected:

public:
	Scene_Pong(std::string _name);
	void Start()					override;
	void Update(float _deltaTime)	override;
	void Close()					override;
};

#endif