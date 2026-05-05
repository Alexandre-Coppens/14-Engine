#ifndef MATERIAL_H
#define MATERIAL_H

#include "Engine/Component.h"
#include "Engine/.EngineGenerated/Generated.h"
#include "Engine/Render/Shaders/Material.h"
#include "Engine/Render/Shaders/ShaderProgram.h"

class Texture;
class ShaderProgram;
class Mesh;
class Material;
class Model : public Component
{
protected:
	Mesh* mMesh;
	Transform3D* mParent;
	Material mMaterial;

	Vector4 mColor {1.0f, 1.0f, 1.0f, 1.0f};
	bool mVisible  { true };
	DrawOption option;

public:
	Mesh* getMesh() const { return mMesh; }
	Material* getMaterial() { return &mMaterial; }
	Vector4 getColor() const { return mColor; }
	bool getVisible() const { return mVisible; }
	
	virtual void setMesh(Mesh* _pMesh) { mMesh = _pMesh; }
	virtual void setColor(Vector4 _color) { mColor = _color; }
	void setVisible(const bool _newVisibility) { mVisible = _newVisibility; }

private:
public:
	Model(Actor* _pOwner, GENERATED_SHADER_PROGRAMS _shader, DrawOption _option = DrawOption::NONE);
	Model(Actor* _pOwner, Transform3D* _parent, GENERATED_SHADER_PROGRAMS _shader, DrawOption _option = DrawOption::NONE);
	~Model() override;

	void OnStart() override;
	void Update(float _deltaTime) override {}
	virtual void Draw();
	void Destroy() override;

	void SetShader(GENERATED_SHADER_PROGRAMS _shader, DrawOption _option);
};

#endif // !1