#include "Assets.h"
#include <sstream>

#include "Log.h"

std::map<std::string, Texture> Assets::mTextureList = {};

Texture Assets::LoadTextureFromFile(Renderer& _pRenderer, const std::string& _pFileName)
{
	Texture texture;
	texture.Load(_pRenderer, _pFileName);
	return texture;
}

Texture Assets::LoadTexture(Renderer& _pRenderer, const std::string& _pFileName, const std::string& _pName)
{
	mTextureList[_pName] = LoadTextureFromFile(_pRenderer, _pFileName);
	return mTextureList[_pName];
}

Texture& Assets::GetTexture(const std::string& _pName)
{
	if (mTextureList.find(_pName) == mTextureList.end())
	{
		std::ostringstream loadError;
		loadError << "Texture " << _pName << " does not exist in assets manager\n";
		Log::Error(LogType::Application, loadError.str());
	}
	return mTextureList[_pName];
}

void Assets::Clear()
{
	for (auto iter : mTextureList)
	{
		iter.second.Unload();
	}
	mTextureList.clear();
}
