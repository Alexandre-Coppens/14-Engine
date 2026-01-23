#ifndef BOX_H
#define BOX_H

#include "Actor.h"
#include "CommonLib.h"

class Box : public Actor
{
private:
public:

private:
public:
	Box(Scene* _pScene);
	~Box();

	void Start()					override;
	void Update(float deltaTime)	override;
	void Destroy()					override;
};

#endif