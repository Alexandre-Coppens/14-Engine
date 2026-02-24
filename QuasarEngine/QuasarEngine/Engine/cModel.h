#ifndef MATERIAL_H
#define MATERIAL_H

#include "Component.h"
#include "Engine/Utilitaries/CommonLib.h"

class ShaderProgram;
class Mesh;
class Model : public Component
{
protected:
	Mesh* mMesh;
	size_t mTextureIndex;
	std::string mShader;

public:
	Mesh* getMesh() const { return mMesh; }
	std::string getShaderName() const { return mShader; }
	
	virtual void setMesh(Mesh* _pMesh) { mMesh = _pMesh; }
	void setTextureIndex(const size_t _pTextureIndex) { mTextureIndex = _pTextureIndex; }

private:
public:
	Model(Actor* _pOwner, const std::string _shader);
	~Model() override;

	void Update(float _deltaTime) override {}
	virtual void Draw(int _option);

	void SetShader(const std::string _shader);
};

#endif // !1