#pragma once
#include "Engine/Actor.h"
#include "Engine/3D/cModel.h"

class Collider3D;
class Cube : public Actor
{
private:
	std::string mModelName;
	std::string mTextureName;
	std::string mShaderName;
    
	Model* mModel            {nullptr};
	//Collider3D* mCollider    {nullptr};
	float mTime {0};

public:
	Model* getModel() const {return mModel;}

private:
public:
	Cube(std::string _name, std::string _model = "Cube", std::string _texture = "", std::string _shader = "");
	~Cube() override;

	void Start()					override;
	void Update(float _deltaTime)	override;
	void Destroy()					override;
};
