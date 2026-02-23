#ifndef MATERIAL_H
#define MATERIAL_H

#include "Component.h"
#include "CommonLib.h"

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
	
	virtual void SetMesh(Mesh* _pMesh) { mMesh = _pMesh; }
	void setTextureIndex(const size_t _pTextureIndex) { mTextureIndex = _pTextureIndex; }

private:
public:
	Model(Actor* _pOwner, const std::string _shader);
	~Model() override;

	void Update(float _deltaTime) override {}
	virtual void Draw();

	void SetShader(const std::string _shader);
};

#endif // !1