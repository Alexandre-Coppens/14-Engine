#pragma once
#include <map>
#include <string>
#include "Texture.h"

class Assets
{
private:
	static std::map<std::string, Texture> mTextureList;

public:
	Texture* GetTexture(std::string _sTextureName){
		if (mTextureList.find(_sTextureName) != mTextureList.end()) return &mTextureList[_sTextureName];
		return nullptr;
	}

private:
	Assets() = default;
	static Texture LoadTextureFromFile(Renderer& _pRenderer, const std::string& _pFileName);

public:
	static Texture LoadTexture(Renderer& _pRenderer, const std::string& _pFileName, const std::string& _pName);
	static Texture& GetTexture(const std::string& _pName);
	static void Clear();
};