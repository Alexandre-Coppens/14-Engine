#include "Assets.h"
#include <sstream>

#include "IRenderer.h"

#include "Log.h"

std::map<std::string, Texture> Assets::mTextureList = {};

Texture Assets::LoadTextureFromFile(IRenderer& _pRenderer, const std::string& _pFileName)
{
	Texture texture;
	texture.Load(_pRenderer, _pFileName);
	return texture;
}

Texture Assets::LoadTexture(IRenderer& _pRenderer, const std::string& _pFileName, const std::string& _pName)
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

//CAREFULL: This Function uses a find to EVERY textures so be precise in the name!
std::vector<Texture*> Assets::GetTextures(const std::string& _pName)
{
	std::vector<Texture*> tList;

	for (auto t = mTextureList.begin(); t != mTextureList.end(); t++)
	{
		if (t->first.find(_pName) != std::string::npos)
			tList.push_back(&t->second);
	}

	return tList;
}

void Assets::Clear()
{
	for (auto iter : mTextureList)
	{
		iter.second.Unload();
	}
	mTextureList.clear();
}
