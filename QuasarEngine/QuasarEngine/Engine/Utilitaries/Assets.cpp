#include "Assets.h"
#include <sstream>
#include <iostream>
#include <filesystem>

#include "MathLib.h"
#include "Engine/Render/RendererGl.h"

#include "Engine/Render/Shader.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Utilitaries/Log.h"
#include "Engine/3D/Mesh.h"
#include "Engine/Render/VertexArray.h"
#include "Engine/Utilitaries/tiny_obj_loader.h"

std::string Assets::engineFile   = "Engine/.EngineAssets";
std::string Assets::resourceFile = "Resources";
std::string Assets::outputPath   = "Engine/.EngineGenerated";

std::vector<std::string> Assets::mSupportedShaderTypes = {".vert", ".frag", ".tesc", ".tese", ".geom"};
std::map<std::string, std::string> Assets::mGeneratedTextures = {};
std::map<std::string, std::string> Assets::mGeneratedMeshes	  = {};
std::map<std::string, std::string> Assets::mGeneratedShader   = {};

std::map<GENERATED_TEXTURE,	Texture*>	Assets::mLoadedTextures = {};
std::map<GENERATED_MESHES,	Mesh*>		Assets::mLoadedMeshes	= {};
std::map<GENERATED_SHADERS,	Shader*>	Assets::mLoadedShaders	= {};

std::map<std::string, int> Assets::mTextureListUses = {};
std::map<std::string, ShaderProgram*> Assets::mShaderProgramList = {};
std::map<ShaderProgram*, std::vector<Model*>> Assets::mDrawOrder = {};

IRenderer* Assets::mRenderer;



static std::string toUpper(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
				   [](unsigned char c) { return std::toupper(c); });
	return s;
}

// -=-=-=-=- FILE GENERATION -=-=-=-=-

//Parse through the Engine Assets and Resources
void Assets::ScanFiles()
{
	const std::filesystem::path engineFilePath{ engineFile };
	const std::filesystem::path resourceFilePath{ resourceFile };
	std::vector<std::filesystem::path> assetsPaths {resourceFilePath, engineFilePath};

	for (const auto& path : assetsPaths)
	{
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			Log::Info("PATH::" + entry.path().string());

			const auto filenameStr = entry.path().filename().string();

			if (entry.is_directory()) {
				std::cout << "dir:  " << filenameStr << '\n';
				Assets::RecursiveScan(path.string() + "/" + filenameStr);
			}
		}
	}

	//Check in Generated.h if it needs to be Updated;
	int oldTextureNbr { 0 };
	int oldModelsNbr  { 0 };
	int oldShadersNbr { 0 };
	int currentLine = 1;
	std::string line;
	std::ifstream loadFile(outputPath + "/" + "Generated.h");

	if (loadFile.is_open())
	{
		while (getline(loadFile, line) ){
			if (currentLine == 4) oldTextureNbr = stoi(BreakString(line, ' ')[4]);
			if (currentLine == 5) oldModelsNbr = stoi(BreakString(line, ' ')[4]);
			if (currentLine == 6) oldShadersNbr = stoi(BreakString(line, ' ')[4]);
			currentLine++;
		}
		loadFile.close();
	}
	if (oldTextureNbr == mGeneratedTextures.size() && oldModelsNbr == mGeneratedMeshes.size() && oldShadersNbr == mGeneratedShader.size())
	{
		Log::Info("Asset Generation: No new Asset Detected.");
		return;
	}
	
	WriteAssetsOnFile(outputPath);
}

//Recursive scan until it find a file
void Assets::RecursiveScan(std::string _path)
{
	const std::filesystem::path resourcePath{ _path };

	for (const auto& entry : std::filesystem::directory_iterator(resourcePath)) {
		const auto filenameStr = entry.path().filename().string();
		
		if (entry.is_directory()) {
			Log::Info("PATH::" + entry.path().string());
			Assets::RecursiveScan(_path + "/" + filenameStr);
			continue;
		}
		
		Log::Info("FILE::" + filenameStr);
		const auto fileStemStr = entry.path().stem().string();
		const auto fileExtensionStr = entry.path().extension().string();

		std::cout << "      -file: " << filenameStr << '\n';
		if (fileExtensionStr == ".png") {
			mGeneratedTextures[_path + "/" + filenameStr] = toUpper(fileExtensionStr.substr(1)) + "_" + CleanFileName(fileStemStr);
		}
		else if (fileExtensionStr == ".obj") {
			mGeneratedMeshes[_path + "/" + filenameStr] = toUpper(fileExtensionStr.substr(1)) + "_" + CleanFileName(fileStemStr);
		}
		else if (find(mSupportedShaderTypes.begin(), mSupportedShaderTypes.end(), fileExtensionStr) != mSupportedShaderTypes.end()) {
			mGeneratedShader[_path + "/" + filenameStr] = toUpper(fileExtensionStr.substr(1)) + "_" + CleanFileName(fileStemStr);
		}
		else {
			Log::Info("Assets::Generation - " + fileExtensionStr + " not supported.");
		}
	}
}

std::string Assets::CleanFileName(std::string _fileName)
{
	std::string result;
	std::vector<char> charList {'.','-',' '};
	for (char& c : _fileName)
	{
		if (std::find(charList.begin(), charList.end(), c) != charList.end()) 
			result += '_';
		else result += c;
	}
	return result;
}

void Assets::WriteAssetsOnFile(std::string _filePath)
{ 
	std::ofstream file;
	file.open( _filePath + "/" + "Generated.h");
	file << "#pragma once \n";
	file << "//Do not write anything in it. Auto-Generated in Assets.cpp.\n";
	file << "\n";
	file << "static int texturesCount = " + std::to_string(mGeneratedTextures.size()) + " ;\n";
	file << "static int meshesCount = " + std::to_string(mGeneratedMeshes.size()) + " ;\n";
	file << "static int shadersCount = " + std::to_string(mGeneratedShader.size()) + " ;\n";
	
	//Create ENUM Part
	file << "\n";
	file << "enum GENERATED_TEXTURE\n";
	file << "{\n";
	for (auto it = mGeneratedTextures.begin(); it != mGeneratedTextures.end(); it++)
	{
		file << "    " + it->second +",\n";
	}
	file << "};\n";
	
	file << "\n";
	file << "enum GENERATED_MESHES\n";
	file << "{\n";
	for (auto it = mGeneratedMeshes.begin(); it != mGeneratedMeshes.end(); it++)
	{
		file << "    " + it->second +",\n";
	}
	file << "};\n";
	
	file << "\n";
	file << "enum GENERATED_SHADERS\n";
	file << "{\n";
	for (auto it = mGeneratedShader.begin(); it != mGeneratedShader.end(); it++)
	{
		file << "    " + it->second + ",\n";
	}
	file << "};\n";
	
	//Create TRANSLATION Part
	file << "\n";
	file << "static std::string getTexturePath(GENERATED_TEXTURE _texture)\n";
	file << "{\n";
	file << "   switch (_texture)\n";
	file << "	{\n";
	for (auto it = mGeneratedTextures.begin(); it != mGeneratedTextures.end(); it++)
	{
		file << "   case " + it->second +":  return" + '"' + it->first + '"' + ";\n";
	}
	file << "	}\n";
	file << "};\n";
	
	file << "\n";
	file << "static std::string getMeshPath(GENERATED_MESHES _mesh)\n";
	file << "{\n";
	file << "   switch (_mesh)\n";
	file << "	{\n";
	for (auto it = mGeneratedMeshes.begin(); it != mGeneratedMeshes.end(); it++)
	{
		file << "   case " + it->second +":  return" + '"'  + it->first + '"'  + ";\n";
	}
	file << "	}\n";
	file << "};\n";
	
	file << "\n";
	file << "static std::string getShaderPath(GENERATED_SHADERS _shader)\n";
	file << "{\n";
	file << "   switch (_shader)\n";
	file << "	{\n";
	for (auto it = mGeneratedShader.begin(); it != mGeneratedShader.end(); it++)
	{
		file << "   case " + it->second +":  return" + '"'  + it->first + '"'  + ";\n";
	}
	file << "	}\n";
	file << "};\n";
	
	file.close();
}

// -=-=-=-=- GET ASSETS -=-=-=-=-

//Returns the pointer of the asked for Texture
Texture* Assets::GetTexture(const GENERATED_TEXTURE& _texture)
{
	if (mLoadedTextures.count(_texture) == 0)
	{
		mLoadedTextures[_texture] = LoadTexture(getTexturePath(_texture));
	}
	return mLoadedTextures[_texture];
}

//Returns a list of Textures
std::vector<Texture*> Assets::GetTextures(const std::vector<GENERATED_TEXTURE>& _searchList)
{
	std::vector<Texture*> tList;

	for (auto t = _searchList.begin(); t != _searchList.end(); t++)
	{
		if (mLoadedTextures.count(*t) == 0)
		{
			mLoadedTextures[*t] = LoadTexture(getTexturePath(*t));
		}
		tList.push_back(mLoadedTextures[*t]);
	}

	return tList;
}

ShaderProgram* Assets::GetShaderProgram(const std::string _shaderName)
{
	if (mShaderProgramList.count(_shaderName) == 0)
	{
		return mShaderProgramList["NULL_SHADER"];
	}
	return mShaderProgramList[(_shaderName)];
}

Mesh* Assets::GetMesh(const GENERATED_MESHES _mesh)
{
	if (mLoadedMeshes.count(_mesh) == 0)
	{
		mLoadedMeshes[_mesh] = LoadMeshFromFile(getMeshPath(_mesh));
	}
	return mLoadedMeshes[_mesh];
}

// -=-=-=-=- LOAD ASSETS -=-=-=-=-

Texture* Assets::LoadTexture(const std::string& _filePath)
{
	Texture* temp = LoadTextureFromFile(_filePath);
	if(temp == nullptr) return mLoadedTextures[PNG_NullTexture];
	return temp;
}

Texture* Assets::LoadTextureFromFile(const std::string& _pFileName)
{
	Texture* texture = new Texture();
	if (!texture->Load(*mRenderer, _pFileName)){
		delete texture;
		return nullptr;
	}
	return texture;
}

//TODO: Add the shaderPrograms to the Generated File

ShaderProgram* Assets::LoadShader(const std::vector<GENERATED_SHADERS> _shaders, const std::string _name, DrawOption _option)
{
	ShaderProgram* shaderProgram = new ShaderProgram(_option);
	std::vector<Shader*> mShaderList {};
	Shader* tempShader;

	for (GENERATED_SHADERS shader : _shaders)
	{
		tempShader = new Shader();
		ShaderType type;
		std::string extension = getShaderPath(shader).substr(getShaderPath(shader).length() - 5, getShaderPath(shader).length() - 1);
		if (extension == ".vert") type = ShaderType::VERTEX;
		else if (extension == ".frag") type = ShaderType::FRAGMENT;
		else if (extension == ".geom") type = ShaderType::GEOMETRY;
		else if (extension == ".tesc") type = ShaderType::TESSELLATION_CONTROL;
		else if (extension == ".tese") type = ShaderType::TESSELLATION_EVAL;
		else type = ShaderType::NONE;
		tempShader->Load(getShaderPath(shader), type);
		mLoadedShaders[shader] = tempShader;
		mShaderList.push_back(tempShader);
		tempShader = nullptr;
	}
	
	shaderProgram->Compose(mShaderList);
	mShaderProgramList[_name] = shaderProgram;
	dynamic_cast<RendererGl*>(mRenderer)->AddShaderProgram(mShaderProgramList[_name]);
	Log::Info("ShaderProgram - " + _name + " successfully composed.");
	shaderProgram = nullptr;
	
	return mShaderProgramList[_name];
}

Mesh* Assets::LoadMeshFromFile(const std::string& _filePath)
{
	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warning, errors;
	bool success = LoadObj(&attributes, &shapes, &materials, &warning, &errors, _filePath.c_str());
	if (!success)
	{
		Log::Error(LogType::Application, "Error::Mesh::" + _filePath + " does not exist or is not .obj.");
		return new Mesh();
	}
	else
	{
		Log::Info("Mesh::" + _filePath + " successfully loaded.");
	}
	std::vector<Vertex> vertices;
	for (int i = 0; i < static_cast<int>(shapes.size()); i++)
	{
		tinyobj::shape_t& shape = shapes[i];
		tinyobj::mesh_t &mesh = shape.mesh;
		for (auto [vertex_index, normal_index, texcoord_index] : mesh.indices)
		{
			Vector3 position = Vector3{
				attributes.vertices[vertex_index * 3],
				attributes.vertices[vertex_index * 3 + 2],
				attributes.vertices[vertex_index * 3 + 1]
			};
			Vector3 normal = Vector3{
				attributes.normals[normal_index * 3],
				attributes.normals[normal_index * 3 + 1],
				attributes.normals[normal_index * 3 + 2]
			};
			Vector2 texCoord = {
				attributes.texcoords[texcoord_index * 2],
				attributes.texcoords[texcoord_index * 2 + 1]
			};
			Vertex vertex = Vertex{position, normal, texCoord};
			vertices.push_back(vertex);
		}
	}
	return new Mesh(vertices);
}

//-=-=-=-=- CLEAR ASSETS -=-=-=-=-

void Assets::Clear()
{
	if (!mLoadedTextures.empty())
	{
		for (auto& iter : mLoadedTextures)
		{
			iter.second->Unload();
			delete iter.second;
			iter.second = nullptr;
		}
		mLoadedTextures.clear();
	}

	if (!mLoadedShaders.empty())
	{
		for (auto& iter : mLoadedShaders)
		{
			delete iter.second;
			iter.second = nullptr;
		}
		mLoadedShaders.clear();
	}
	
	if (!mShaderProgramList.empty())
	{
		for (auto& iter : mShaderProgramList)
		{
			if (iter.second == nullptr) continue;
			iter.second->Unload();
			delete iter.second;
			iter.second = nullptr;
		}
		mShaderProgramList.clear();
	}
	
	if (!mLoadedMeshes.empty())
	{
		for (auto& iter : mLoadedMeshes)
		{
			iter.second->Unload();
			delete iter.second;
			iter.second = nullptr;
		}
		mLoadedMeshes.clear();
	}
	mRenderer = nullptr;
}