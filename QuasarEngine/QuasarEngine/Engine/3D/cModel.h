#ifndef MATERIAL_H
#define MATERIAL_H

#include "Engine/Component.h"
#include "Engine/Render/ShaderProgram.h"

class ShaderProgram;
class Mesh;
class Model : public Component
{
protected:
	Mesh* mMesh;
	size_t mTextureIndex;
	std::string mShader;

	Vector4 mColor {1.0f, 1.0f, 1.0f, 1.0f};

public:
	Mesh* getMesh() const { return mMesh; }
	Vector4 getColor() const { return mColor; }
	std::string getShaderName() const { return mShader; }
	
	virtual void setMesh(Mesh* _pMesh) { mMesh = _pMesh; }
	virtual void setColor(Vector4 _color) { mColor = _color; }
	void setTextureIndex(const size_t _pTextureIndex) { mTextureIndex = _pTextureIndex; }

private:
public:
	Model(Actor* _pOwner, const std::string _shader);
	~Model() override;

	void Update(float _deltaTime) override {}
	virtual void Draw(DrawOption _option);

	void SetShader(const std::string _shader);
};

#endif // !1