#pragma once
#include <string>
#include "CommonLib.h"

class VertexArray;
class ShaderProgram;
class Shader;
class Texture;
class Mesh
{
private:
	VertexArray* pVao;
	Shader mVertexShader;
	Shader mFragmentShader;
	ShaderProgram mShaderProgram;
	std::vector<Texture*> pTextures;

	uint16_t mVerticeCount;
	uint16_t mIndicesCount;
	
	float mVertices[28*5] {
   -0.5, -0.5, -0.5, 0, 0 ,
   0.5, -0.5, -0.5, 1, 0 ,
   -0.5, 0.5, -0.5,0, -1 ,
   0.5, 0.5, -0.5, 1, -1 ,
   -0.5, 0.5, 0.5, 0, -1 ,
   0.5, 0.5, 0.5, 1, -1 ,
   -0.5, -0.5, 0.5, 0, 0 ,
   0.5, -0.5, 0.5, 1, 0 ,
   -0.5, 0.5, -0.5, 0, -1 ,
   0.5, -0.5, -0.5, 1, 0 ,
   -0.5, 0.5, -0.5, 0, -1 ,
   0.5, 0.5, -0.5, 1, -1 ,
   -0.5, 0.5, 0.5, 0, -1 ,
   -0.5, 0.5, 0.5, 0, -1 ,
   0.5, 0.5, 0.5, 1, -1 ,
   -0.5, -0.5, 0.5, 0, 0 ,
   -0.5, -0.5, 0.5, 0, 0 ,
   0.5, -0.5, 0.5, 1, 0 ,
   -0.5, -0.5, -0.5, 0, 0 ,
   0.5, -0.5, -0.5, 1, 0 ,
   0.5, -0.5, -0.5, 1, 0 ,
   0.5, -0.5, 0.5, 1, 0 ,
   0.5, 0.5, -0.5, 1, -1 ,
   0.5, 0.5, 0.5, 1, -1 ,
   -0.5, -0.5, 0.5, 0, 0 ,
   -0.5, -0.5, -0.5, 0, 0 ,
   -0.5, 0.5, 0.5, 0, -1 ,
   -0.5, 0.5, -0.5, 0, -1
	};

	unsigned int mIndices[36] {
   2, 1, 0 ,
	3, 9, 8 ,
	4, 11, 10 ,
	5, 11, 12 ,
	6, 14, 13 ,
	7, 14, 15 ,
	18, 17, 16 ,
	19, 17, 18 ,
	22, 21, 20 ,
	23, 21, 22 ,
	26, 25, 24 ,
	27, 25, 26
	};


public:
	VertexArray* getVertexArray() { return pVao; }
	ShaderProgram* getShaderProgram() { return &mShaderProgram; }
	Texture* getTexture(uint16_t _i) { return pTextures[_i]; }

	void setShader(Shader _vert, Shader _frag) { mVertexShader = _vert; mFragmentShader = _frag; }

private:
public:
	Mesh();
	~Mesh();

	void AddTexture(Texture* _t) { pTextures.push_back(_t); }
	void Unload();
};