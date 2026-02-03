#ifndef FLOOR_H
#define FLOOR_H

#include "Actor.h"
#include "CommonLib.h"

class Floor : public Actor
{
private:
public:

private:
public:
	Floor();
	~Floor();

	void Start()					override;
	void Update(float deltaTime)	override;
	void Destroy()					override;
};

#endif