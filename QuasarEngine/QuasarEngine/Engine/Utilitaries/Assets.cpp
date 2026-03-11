#include "Assets.h"
#include <sstream>

#include "Engine/Render/RendererGl.h"

#include "Engine/Render/Shader.h"
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Utilitaries/Log.h"
#include "Engine/3D/Mesh.h"
#include "Engine/Utilitaries/tiny_obj_loader.h"

std::map<std::string, Texture*> Assets::mTextureList = {};
std::map<std::string, Shader*> Assets::mShaderList = {};
std::map<std::string, ShaderProgram*> Assets::mShaderProgramList = {};
std::map<std::string, Mesh*> Assets::mMeshList = {};
std::map<ShaderProgram*, std::vector<Model*>> Assets::mDrawOrder = {};

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

ShaderProgram* Assets::LoadShader(RendererGl* pRendererGl, const std::string _vertexFile, const std::string _fragmentFile,const std::string _name, int _options)
{
	ShaderProgram* shader = new ShaderProgram(_options);
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
	Mesh mesh;
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

Mesh* Assets::GetMesh(const std::string _name)
{
	if (mMeshList.find(_name) != mMeshList.end()) return mMeshList[_name];
	return nullptr;
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
		mShaderProgramList.clear();
	}
	
	if (!mShaderProgramList.empty())
	{
		for (const auto& iter : mShaderProgramList)
		{
			iter.second->Unload();
		}
		mShaderProgramList.clear();
	}
	
}
