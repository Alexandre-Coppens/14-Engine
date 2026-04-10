#pragma once
#include <SDL_stdinc.h>

#include "Engine/Render/ShaderProgram.h"

struct Vertex; 
class VertexArray;
class ShaderProgram;
class Mesh
{
private:
	VertexArray* pVao;
	std::vector<Vertex> mVertices;

public:
	VertexArray* getVertexArray()	  const { return pVao; }
	
private:
public:
	Mesh();
	Mesh(std::vector<Vertex> _pVertices);
	~Mesh();

	void Unload();
	
	float* ToVerticeArray();
};