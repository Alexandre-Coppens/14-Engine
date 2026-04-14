#pragma once
#include <string>
#include <SDL_image.h>
#include "Engine/Utilitaries/CommonLib.h"

class IRenderer;
class RendererSdl;
class RendererGl;
class Texture
{
private:
	std::string mFileName;
	SDL_Texture* pSdlTexture  {nullptr};
	Uint16   mWidth           {0},
			 mHeight		  {0};
	unsigned int mTextureId   {0};

public:
	Vector2 GetSize()			 const	{ return Vector2{ static_cast<float>(mWidth), static_cast<float>(mHeight) }; }
	uint16_t GetWidth()			 const	{ return mWidth; }
	uint16_t GetHeight()		 const	{ return mHeight; }
	SDL_Texture* GetSdlTexture() const	{ return pSdlTexture; }

private:
public:
	Texture();
	~Texture();

	bool Load(IRenderer& _renderer, const std::string& _filePath);
	bool LoadSdl(RendererSdl* _renderer, const std::string& _filename, SDL_Surface* _pSurface);
	bool LoadGl(RendererGl* _renderer, const std::string& _filename, SDL_Surface* _pSurface);
	void SetActive() const;
	void Unload();
	void UpdateInfo(float& _pWidthOut, float& _pHeightOut);
};