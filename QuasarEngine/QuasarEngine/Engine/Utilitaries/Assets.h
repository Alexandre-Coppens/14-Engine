#pragma once
#include <map>
#include <string>
#include <vector>
#define TINYOBJLOADER_IMPLEMENTATION

#include "Engine/Texture.h"
#include "Engine/Render/Shaders/ShaderProgram.h"

#include "Engine/.EngineGenerated/Generated.h"
#include "Engine/Render/Shaders/Uniform.h"

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
	static std::map<std::string, std::string> mGeneratedShaderPrograms;

	//Loaded Asset List
	static std::map<GENERATED_TEXTURE,	Texture*>				mLoadedTextures;
	static std::map<GENERATED_MESHES,	Mesh*>					mLoadedMeshes;
	static std::map<GENERATED_SHADERS,	Shader*>				mLoadedShaders;
	static std::map<GENERATED_SHADER_PROGRAMS, ShaderProgram*>	mShaderProgramList;

	//Used Assets
	static std::map<std::string, int> mTextureListUses;
	static std::map<ShaderProgram*, std::vector<Model*>> mDrawOrder;
	
public:
	static void setRenderer(IRenderer* _renderer) {mRenderer = _renderer;}

private:
	Assets() = default;
	static Texture* LoadTextureFromFile(const std::string& _pFileName);
	static ShaderProgram* LoadShaderProgramFromFile(const std::string& _filePath, GENERATED_SHADER_PROGRAMS _name);
	static void ComposeShader(ShaderProgram* shaderProgram, std::vector<GENERATED_SHADERS> _shaders);
	static Mesh* LoadMeshFromFile(const std::string& _filePath);

public:
	static void ScanFiles();
	static void RecursiveScan(std::string _path);
	static std::string CleanFileName(std::string);
	static void WriteAssetsOnFile(std::string _filePath);
	
	static Texture* GetTexture(const GENERATED_TEXTURE& _texture);
	static std::vector<Texture*> GetTextures(const std::vector<GENERATED_TEXTURE>& _searchList);
	static ShaderProgram* GetShaderProgram(GENERATED_SHADER_PROGRAMS _shaderName);
	static Mesh* GetMesh(GENERATED_MESHES _mesh);

	static Texture* LoadTexture(const std::string& _filePath);
	static ShaderProgram* LoadShader(GENERATED_SHADER_PROGRAMS _name, std::vector<GENERATED_SHADERS> _shaders, std::vector<Uniform> _uniforms, std::string
	                                 _texture[]);

	static void Clear();
};