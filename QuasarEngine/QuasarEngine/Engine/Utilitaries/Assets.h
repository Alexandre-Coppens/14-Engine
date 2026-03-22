#pragma once
#include <map>
#include <string>
#include <vector>
#define TINYOBJLOADER_IMPLEMENTATION

#include "Engine/Texture.h"
#include "Engine/Render/ShaderProgram.h"

class Mesh;
class Model;
class Shader;
class ShaderProgram;
class IRenderer;
class Assets
{
private:
	static std::map<std::string, Texture*> mTextureList;
	static std::map<std::string, int> mTextureListUses;
	static std::map<std::string, Shader*> mShaderList;
	static std::map<std::string, ShaderProgram*> mShaderProgramList;
	static std::map<std::string, Mesh*> mMeshList;
	static std::map<ShaderProgram*, std::vector<Model*>> mDrawOrder;

public:

private:
	Assets() = default;
	static Texture* LoadTextureFromFile(IRenderer& _pRenderer, const std::string& _pFileName);
	static Mesh* LoadMeshFromFile(const std::string& _pFileName);

public:
	static Texture* LoadTexture(IRenderer& _pRenderer, const std::string& _pFileName, const std::string& _pName);
	static Texture* GetTexture(const std::string& _pName);
	static std::vector<Texture*> GetTextures(const std::string& _pName);

	static ShaderProgram* LoadShader(RendererGl* pRendererGl, std::string _vertexFile, std::string _fragmentFile, std::string _name, DrawOption _option);
	static ShaderProgram* LoadShader(RendererGl* pRendererGl, std::string _vertexFile, std::string _tesselationControlFile, std::string _tesselationEvaluationFile, std::string _fragmentFile, std::string _name, DrawOption _option);
	static ShaderProgram* GetShader(const std::string _name);
	
	static Mesh* LoadMesh(std::string _fileName, std::string _name);
	static Mesh* GetMesh(const std::string _name);
	
	static void Clear();
};