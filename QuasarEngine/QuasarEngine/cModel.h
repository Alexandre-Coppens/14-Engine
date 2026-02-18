#ifndef MATERIAL_H
#define MATERIAL_H

#include "Component.h"
#include "CommonLib.h"
#include "Texture.h"
#include "RendererGl.h"

class Mesh;
class Model : public Component
{
protected:
	Mesh* mMesh;
	size_t mTextureIndex;

public:
	virtual void SetMesh(Mesh* _pMesh) { mMesh = _pMesh; }
	void setTextureIndex(size_t _pTextureIndex) { mTextureIndex = _pTextureIndex; }

private:
public:
	Model(Actor* _pOwner);
	virtual ~Model();

	virtual void Draw(Matrix4Row _viewProj);
};

#endif // !1