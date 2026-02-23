#ifndef BOXGL_H
#define BOXGL_H

#include "Actor.h"
#include "cModel.h"
#include "CommonLib.h"

class BoxGl : public Actor
{
private:
	Model* mModel;
	
public:
	Model* getModel() const {return mModel;}

private:
public:
	BoxGl();
	~BoxGl();

	void Start()					override;
	void Update(float _deltaTime)	override;
	void Destroy()					override;
};

#endif