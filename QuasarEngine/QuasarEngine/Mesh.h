#pragma once
#include <SDL_stdinc.h>

#include "Shader.h"
#include "ShaderProgram.h"

class VertexArray;
class ShaderProgram;
class Texture;
class Mesh
{
private:
	VertexArray* pVao;
	
	std::vector<Texture*> pTextures;

	uint16_t mVerticesCount;
	uint16_t mIndicesCount;

	float mVertices[14*5] = {
		-0.5,-0.5,-0.5, 0, 0,
		 0.5,-0.5,-0.5, 1, 0,
		 0.5, 0.5,-0.5, 2, 0,
		-0.5, 0.5,-0.5, 3, 0,
		-0.5,-0.5,-0.5, 4, 0,
    
		-0.5,-0.5, 0.5, 0, 1,
		 0.5,-0.5, 0.5, 1, 1,
		 0.5, 0.5, 0.5, 2, 1,
		-0.5, 0.5, 0.5, 3, 1,
		-0.5,-0.5, 0.5, 4, 1,
    
		-0.5, 0.5,-0.5, 0,-1,
		 0.5, 0.5,-0.5, 1,-1,
    
		-0.5, 0.5, 0.5, 0, 2,
		 0.5, 0.5, 0.5, 1, 2
	};

	const unsigned int mIndices[6*2*3] = {
		0, 1, 5,
		5, 1, 6,
		1, 2, 6,
		6, 2, 7,
		2, 3, 7,
		7, 3, 8,
		3, 4, 8,
		8, 4, 9,
		10,11, 0,
		0,11, 1,
		5, 6,12,
		12, 6,13
   };

public:
	VertexArray* getVertexArray()	  const { return pVao; }
	Texture* getTexture(const uint16_t _i)  const { return pTextures[_i]; }

private:
public:
	Mesh();
	~Mesh();

	void AddTexture(Texture* _t) { pTextures.push_back(_t); }
	void Unload();
};