#pragma once
#include <SDL_stdinc.h>

#include "Shader.h"
#include "ShaderProgram.h"

struct Vertex; 
class VertexArray;
class ShaderProgram;
class Texture;
class Mesh
{
private:
	VertexArray* pVao;
	std::vector<Vertex> mVertices;
	std::vector<Texture*> pTextures;

public:
	VertexArray* getVertexArray()	  const { return pVao; }
	Texture* getTexture(const uint16_t _i)  const { return pTextures[_i]; }

private:
public:
	Mesh();
	Mesh(std::vector<Vertex> _pVertices);
	~Mesh();

	void AddTexture(Texture* _t) { pTextures.push_back(_t); }
	void Unload();
	
	float* ToVerticeArray();
	
};