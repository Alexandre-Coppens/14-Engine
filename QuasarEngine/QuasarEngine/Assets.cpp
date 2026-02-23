#include "Assets.h"
#include <sstream>

#include "IRenderer.h"
#include "RendererGl.h"

#include "Log.h"
#include "Shader.h"
#include "ShaderProgram.h"

std::map<std::string, Texture*> Assets::mTextureList = {};
std::map<std::string, Shader*> Assets::mShaderList = {};
std::map<std::string, ShaderProgram*> Assets::mShaderProgramList = {};
std::map<ShaderProgram*, std::vector<Model*>> Assets::mDrawOrder = {};

Texture* Assets::LoadTexture(IRenderer& _pRenderer, const std::string& _pFileName, const std::string& _pName)
{
	mTextureList[_pName] = LoadTextureFromFile(_pRenderer, _pFileName);
	return mTextureList.at(_pName);
}

Texture* Assets::LoadTextureFromFile(IRenderer& _pRenderer, const std::string& _pFileName)
{
	Texture* texture = new Texture();
	texture->Load(_pRenderer, _pFileName);
	return texture;
}

Texture* Assets::GetTexture(const std::string& _pName)
{
	if (mTextureList.find(_pName) == mTextureList.end())
	{
		std::ostringstream loadError;
		loadError << "Texture " << _pName << " does not exist in assets manager\n";
		Log::Error(LogType::Application, loadError.str());
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

ShaderProgram* Assets::LoadShader(RendererGl* pRendererGl, const std::string _vertexFile, const std::string _fragmentFile,const std::string _name)
{
	ShaderProgram* shader = new ShaderProgram();
	Shader* mTempVertex = nullptr;
	Shader* mTempFragment = nullptr;

	if (mShaderList.find(_vertexFile) != mShaderList.end()) mTempVertex = mShaderList[_vertexFile];
	else
	{
		mTempVertex = new Shader();
		mTempVertex->Load("BasicModel.vert", ShaderType::VERTEX);
		mShaderList[_vertexFile] = std::move(mTempVertex);
	}

	if (mShaderList.find(_fragmentFile) != mShaderList.end()) mTempFragment = mShaderList[_fragmentFile];
	else
	{
		mTempFragment = new Shader();
		mTempFragment->Load("BasicModel.frag", ShaderType::FRAGMENT);
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

void Assets::Clear()
{
	for (const auto& iter : mTextureList)
	{
		iter.second->Unload();
	}
	mTextureList.clear();

	for (const auto& iter : mShaderList)
	{
		delete(iter.second);
	}
	mShaderProgramList.clear();
	
	for (const auto& iter : mShaderProgramList)
	{
		iter.second->Unload();
	}
	mShaderProgramList.clear();
}
