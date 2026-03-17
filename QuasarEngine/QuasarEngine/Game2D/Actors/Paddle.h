#ifndef PADDLE_H
#define PADDLE_H

#include "Engine/Actor.h"
#include "Engine/Utilitaries/CommonLib.h"

class Paddle : public Actor
{
private:
	int life{ 3 };

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