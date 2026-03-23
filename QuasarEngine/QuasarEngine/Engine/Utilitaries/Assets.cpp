#include "Assets.h"
#include <sstream>
#include <iostream>
#include <filesystem>

#include "Engine/Render/RendererGl.h"

#include "Engine/Render/Shader.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Utilitaries/Log.h"
#include "Engine/3D/Mesh.h"
#include "Engine/Render/VertexArray.h"
#include "Engine/Utilitaries/tiny_obj_loader.h"

std::map<std::string, Texture*> Assets::mTextureList = {};
std::map<std::string, int> Assets::mTextureListUses = {};

std::map<std::string, Shader*> Assets::mShaderList = {};
std::map<std::string, ShaderProgram*> Assets::mShaderProgramList = {};

std::map<std::string, Mesh*> Assets::mMeshList = {};

std::map<ShaderProgram*, std::vector<Model*>> Assets::mDrawOrder = {};

std::vector<std::string> Assets::mSupportedShaderTypes = {".vert", ".frag", ".tesc", ".tese"};
std::map<std::string, std::string> Assets::mGeneratedTextures = {};
std::map<std::string, std::string> Assets::mGeneratedMeshes = {};
std::map<std::string, std::string> Assets::mGeneratedShader = {};

static std::string toUpper(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(),
				   [](unsigned char c) { return std::toupper(c); });
	return s;
}

void Assets::ScanFiles()
{
	std::string engineFile = "Engine/.EngineAssets";
	std::string resourceFile = "Resources";
	std::string outputPath = "Engine/.EngineGenerated";
    
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
	WriteAssetsOnFile(outputPath);
}

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
			mGeneratedTextures[_path + "/" + filenameStr] = toUpper(fileExtensionStr.substr(1)) + "_" + Clean(fileStemStr);
		}
		else if (fileExtensionStr == ".obj") {
			mGeneratedMeshes[_path + "/" + filenameStr] = toUpper(fileExtensionStr.substr(1)) + "_" + Clean(fileStemStr);
		}
		else if (find(mSupportedShaderTypes.begin(), mSupportedShaderTypes.end(), fileExtensionStr) != mSupportedShaderTypes.end()) {
			mGeneratedShader[_path + "/" + filenameStr] = toUpper(fileExtensionStr.substr(1)) + "_" + Clean(fileStemStr);
		}
		else {
			Log::Info("Assets::Generation - " + fileExtensionStr + " not supported.");
		}
	}
}

std::string Assets::Clean(std::string _fileName)
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
	file << "enum GENERATED_MODELS\n";
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
		file << "    " + it->second +",\n";
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
	file << "static std::string getTexturePath(GENERATED_MODELS _model)\n";
	file << "{\n";
	file << "   switch (_model)\n";
	file << "	{\n";
	for (auto it = mGeneratedMeshes.begin(); it != mGeneratedMeshes.end(); it++)
	{
		file << "   case " + it->second +":  return" + '"'  + it->first + '"'  + ";\n";
	}
	file << "	}\n";
	file << "};\n";
	
	file << "\n";
	file << "static std::string getTexturePath(GENERATED_SHADERS _shader)\n";
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

Texture* Assets::LoadTexture(IRenderer& _pRenderer, const std::string& _pFileName, const std::string& _pName)
{
	Texture* temp = LoadTextureFromFile(_pRenderer, _pFileName);
	if(temp == nullptr) return mTextureList["NULLTEXTURE"];
	mTextureList[_pName] = temp;
	return mTextureList.at(_pName);
}

Texture* Assets::LoadTextureFromFile(IRenderer& _pRenderer, const std::string& _pFileName)
{
	Texture* texture = new Texture();
	if (!texture->Load(_pRenderer, _pFileName)) return nullptr;
	return texture;
}

Texture* Assets::GetTexture(const std::string& _pName)
{
	if (mTextureList.find(_pName) == mTextureList.end())
	{
		std::ostringstream loadError;
		loadError << "Texture " << _pName << " does not exist in assets manager\n";
		Log::Error(LogType::Application, loadError.str());
		return mTextureList["NULLTEXTURE"];
	}
	return mTextureList[_pName];
}

//CAREFUL: This Function uses a find to EVERY textures so be precise in the name!
std::vector<Texture*> Assets::GetTextures(const std::string& _pName)
{
	std::vector<Texture*> tList;

	for (auto t = mTextureList.begin(); t != mTextureList.end(); t++)
	{
		if (t->first.find(_pName) != std::string::npos)
			tList.push_back(t->second);
	}

	return tList;
}

ShaderProgram* Assets::LoadShader(RendererGl* pRendererGl, const std::string _vertexFile, const std::string _fragmentFile,const std::string _name, DrawOption _option)
{
	ShaderProgram* shader = new ShaderProgram(_option);
	Shader* mTempVertex = nullptr;
	Shader* mTempFragment = nullptr;

	if (mShaderList.find(_vertexFile) != mShaderList.end()) mTempVertex = mShaderList[_vertexFile];
	else
	{
		mTempVertex = new Shader();
		mTempVertex->Load(_vertexFile, ShaderType::VERTEX);
		mShaderList[_vertexFile] = std::move(mTempVertex);
	}

	if (mShaderList.find(_fragmentFile) != mShaderList.end()) mTempFragment = mShaderList[_fragmentFile];
	else
	{
		mTempFragment = new Shader();
		mTempFragment->Load(_fragmentFile, ShaderType::FRAGMENT);
		mShaderList[_fragmentFile] = std::move(mTempFragment);
	}
	
	shader->Compose(std::vector<Shader*>{mShaderList[_vertexFile], mShaderList[_fragmentFile]});
	mShaderProgramList[_name] = shader;
	pRendererGl->AddShaderProgram(mShaderProgramList[_name]);
	Log::Info("ShaderProgram - " + _name + " successfully composed.");
	
	return mShaderProgramList[_name];
}

ShaderProgram* Assets::LoadShader(RendererGl* pRendererGl, const std::string _vertexFile, const std::string _tesselationControlFile, const std::string _tesselationEvaluationFile, const std::string _fragmentFile,const std::string _name, DrawOption _option)
{
	ShaderProgram* shader = new ShaderProgram(_option);
	Shader* mTempVertex = nullptr;
	Shader* mTempTessControl = nullptr;
	Shader* mTempTessEval = nullptr;
	Shader* mTempFragment = nullptr;

	if (mShaderList.find(_vertexFile) != mShaderList.end()) mTempVertex = mShaderList[_vertexFile];
	else
	{
		mTempVertex = new Shader();
		mTempVertex->Load(_vertexFile, ShaderType::VERTEX);
		mShaderList[_vertexFile] = std::move(mTempVertex);
	}

	if (mShaderList.find(_tesselationControlFile) != mShaderList.end()) mTempTessControl = mShaderList[_tesselationControlFile];
	else
	{
		mTempTessControl = new Shader();
		mTempTessControl->Load(_tesselationControlFile, ShaderType::TESSELLATION_CONTROL);
		mShaderList[_tesselationControlFile] = std::move(mTempTessControl);
	}

	if (mShaderList.find(_tesselationEvaluationFile) != mShaderList.end()) mTempTessEval = mShaderList[_tesselationEvaluationFile];
	else
	{
		mTempTessEval = new Shader();
		mTempTessEval->Load(_tesselationEvaluationFile, ShaderType::TESSELLATION_EVAL);
		mShaderList[_tesselationEvaluationFile] = std::move(mTempTessEval);
	}

	if (mShaderList.find(_fragmentFile) != mShaderList.end()) mTempFragment = mShaderList[_fragmentFile];
	else
	{
		mTempFragment = new Shader();
		mTempFragment->Load(_fragmentFile, ShaderType::FRAGMENT);
		mShaderList[_fragmentFile] = std::move(mTempFragment);
	}
	
	shader->Compose(std::vector<Shader*>{mShaderList[_vertexFile], mShaderList[_tesselationControlFile], mShaderList[_tesselationEvaluationFile], mShaderList[_fragmentFile]});
	mShaderProgramList[_name] = shader;
	pRendererGl->AddShaderProgram(mShaderProgramList[_name]);
	Log::Info("ShaderProgram - " + _name + " successfully composed.");
	
	return mShaderProgramList[_name];
}

ShaderProgram* Assets::GetShader(const std::string _name)
{
	if (mShaderProgramList.find(_name) != mShaderProgramList.end()) return mShaderProgramList[_name];
	return mShaderProgramList["NULL"];
}

Mesh* Assets::LoadMesh(const std::string _fileName, std::string _name)
{
	mMeshList[_name] = LoadMeshFromFile(_fileName);
	return mMeshList[_name];
}

Mesh* Assets::LoadMeshFromFile(const std::string& _pFileName)
{
	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warning, errors;
	bool success = LoadObj(&attributes, &shapes, &materials, &warning, &errors, _pFileName.c_str());
	if (!success)
	{
		Log::Error(LogType::Application, "Error::Mesh::" + _pFileName + " does not exist or is not .obj.");
		return new Mesh();
	}
	else
	{
		Log::Info("Mesh::" + _pFileName + " successfully loaded.");
	}
	std::vector<Vertex> vertices;
	for (int i = 0; i < shapes.size(); i++)
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
				-attributes.texcoords[texcoord_index * 2 + 1]
			};
			Vertex vertex = Vertex{position, normal, texCoord};
			vertices.push_back(vertex);
		}
	}
	return new Mesh(vertices);
}

Mesh* Assets::GetMesh(const GENERATED_MODELS _models)
{
	return mMeshList[]; FINISH THE TRANSLATION ENUM -> MESH
}

void Assets::Clear()
{
	if (!mTextureList.empty())
	{
		for (const auto& iter : mTextureList)
		{
			iter.second->Unload();
		}
		mTextureList.clear();
	}

	if (!mShaderList.empty())
	{
		for (const auto& iter : mShaderList)
		{
			delete(iter.second);
		}
		mShaderList.clear();
	}
	
	if (!mShaderProgramList.empty())
	{
		for (const auto& iter : mShaderProgramList)
		{
			iter.second->Unload();
		}
		mShaderProgramList.clear();
	}
	
	if (!mMeshList.empty())
	{
		for (const auto& iter : mMeshList)
		{
			iter.second->Unload();
		}
		mMeshList.clear();
	}
}
