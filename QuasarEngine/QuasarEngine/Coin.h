#ifndef COIN_H
#define COIN_H

#include "Actor.h"
#include "CommonLib.h"

class Coin : public Actor
{
private:
public:

private:
public:
	Coin();
	~Coin();

	void Start()					override;
	void Update(float deltaTime)	override;
	void Destroy()					override;
};

#endif