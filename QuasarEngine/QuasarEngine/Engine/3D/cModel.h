#ifndef MATERIAL_H
#define MATERIAL_H

#include "Engine/Component.h"
#include "Engine/Render/ShaderProgram.h"

class Texture;
class ShaderProgram;
class Mesh;
class Model : public Component
{
protected:
	Mesh* mMesh;
	Transform3D* mParent;
	size_t mTextureIndex;
	std::vector<Texture*> pTextures;
	std::string mShader;

	Vector4 mColor {1.0f, 1.0f, 1.0f, 1.0f};
	bool mVisible  { true };

public:
	Mesh* getMesh() const { return mMesh; }
	Vector4 getColor() const { return mColor; }
	std::string getShaderName() const { return mShader; }
	bool getVisible() const { return mVisible; }
	Texture* getTexture(const uint16_t _i)  const { return pTextures[_i]; }
	
	virtual void setMesh(Mesh* _pMesh) { mMesh = _pMesh; }
	virtual void setColor(Vector4 _color) { mColor = _color; }
	void setTextureIndex(const size_t _pTextureIndex) { mTextureIndex = _pTextureIndex; }
	void setVisible(const bool _newVisibility) { mVisible = _newVisibility; }
	void setTexture(Texture* _t) {pTextures[0] = _t;}

private:
public:
	Model(Actor* _pOwner, std::string _shader);
	Model(Actor* _pOwner, Transform3D* _parent, const std::string _shader);
	~Model() override;

	void OnStart() override;
	void Update(float _deltaTime) override {}
	virtual void Draw(DrawOption _option);
	void Destroy() override;

	void SetShader(const std::string _shader);
	void AddTexture(Texture* _t) { pTextures.push_back(_t); }

};

#endif // !1