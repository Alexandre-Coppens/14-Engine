#ifndef PADDLE_H
#define PADDLE_H

#include "Actor.h"
#include "CommonLib.h"

class Paddle : public Actor
{
private:
public:

private:
public:
	Paddle(Scene* _pScene);
	~Paddle();

	void Start()					override;
	void Update(float deltaTime)	override;
	void Destroy()					override;
};

#endif