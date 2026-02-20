#ifndef BOX_H
#define BOX_H

#include "Actor.h"

class Box : public Actor
{
private:
public:

private:
public:
	Box();
	~Box();

	void Start()					override;
	void Update(float _deltaTime)	override;
	void Destroy()					override;
};

#endif