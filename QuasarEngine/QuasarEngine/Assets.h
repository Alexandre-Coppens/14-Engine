#pragma once
#include <map>
#include <string>
#include <vector>
#include "Texture.h"

class Assets
{
private:
	static std::map<std::string, Texture> mTextureList;

public:

private:
	Assets() = default;
	static Texture LoadTextureFromFile(RendererSdl& _pRenderer, const std::string& _pFileName);

public:
	static Texture LoadTexture(RendererSdl& _pRenderer, const std::string& _pFileName, const std::string& _pName);
	static Texture& GetTexture(const std::string& _pName);
	static std::vector<Texture*> GetTextures(const std::string& _pName);
	static void Clear();
};