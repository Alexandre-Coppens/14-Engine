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
	Paddle();
	~Paddle();

	void Start()					override;
	void Update(float _deltaTime)	override;
	void Destroy()					override;
};

#endif