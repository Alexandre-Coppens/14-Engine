#pragma once
#include <map>
#include <string>
#include <vector>
#define TINYOBJLOADER_IMPLEMENTATION

#include "Engine/Texture.h"
#include "Engine/Render/ShaderProgram.h"

#include "Engine/.EngineGenerated/Generated.h"

class Mesh;
class Model;
class Shader;
class ShaderProgram;
class IRenderer;
class Assets
{
private:
	static IRenderer* mRenderer;
	
	//FilePaths
	static std::string engineFile;
	static std::string resourceFile;
	static std::string outputPath;
	
	static std::vector<std::string> mSupportedShaderTypes;
	//Used for Generated.h content | 1 = Path, 2 = FileName
	static std::map<std::string, std::string> mGeneratedTextures;
	static std::map<std::string, std::string> mGeneratedMeshes;
	static std::map<std::string, std::string> mGeneratedShader;

	//Loaded Asset List
	static std::map<GENERATED_TEXTURE,	Texture*>	mLoadedTextures;
	static std::map<GENERATED_MESHES,	Mesh*>		mLoadedMeshes;
	static std::map<GENERATED_SHADERS,	Shader*>	mLoadedShaders;

	//Used Assets
	static std::map<std::string, int> mTextureListUses;
	static std::map<std::string, ShaderProgram*> mShaderProgramList;
	static std::map<ShaderProgram*, std::vector<Model*>> mDrawOrder;
	
public:
	static void setRenderer(IRenderer* _renderer) {mRenderer = _renderer;}

private:
	Assets() = default;
	static Texture* LoadTextureFromFile(const std::string& _pFileName);
	static Mesh* LoadMeshFromFile(const std::string& _filePath);

public:
	static void ScanFiles();
	static void RecursiveScan(std::string _path);
	static std::string CleanFileName(std::string);
	static void WriteAssetsOnFile(std::string _filePath);
	
	static Texture* GetTexture(const GENERATED_TEXTURE& _texture);
	static std::vector<Texture*> GetTextures(const std::vector<GENERATED_TEXTURE>& _searchList);
	static ShaderProgram* GetShaderProgram(const std::string _name);
	static Mesh* GetMesh(GENERATED_MESHES _mesh);

	static Texture* LoadTexture(const std::string& _filePath);
	static ShaderProgram* LoadShader(GENERATED_SHADERS _vertexFile, GENERATED_SHADERS _fragmentFile, const std::string& _name, DrawOption
	                                 _option);
	static ShaderProgram* LoadShader(GENERATED_SHADERS _vertexFile, GENERATED_SHADERS _tesselationControlFile, GENERATED_SHADERS
	                                 _tesselationEvaluationFile, GENERATED_SHADERS _fragmentFile, const std::string& _name, DrawOption _option);
	
	static void Clear();
};