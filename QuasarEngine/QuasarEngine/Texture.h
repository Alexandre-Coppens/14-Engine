#pragma once
#include <string>
#include <SDL_image.h>
#include "CommonLib.h"

class IRenderer;
class RendererSdl;
class RendererGl;
class Texture
{
private:
	std::string mFileName;
	SDL_Texture* pSdlTexture;
	uint16_t mWidth, mHeight;
	unsigned int mTextureID ;

public:
	Vector2 GetSize()			 const	{ return Vector2{ (float)mWidth, (float)mHeight }; }
	uint16_t GetWidth()			 const	{ return mWidth; }
	uint16_t GetHeight()		 const	{ return mHeight; }
	SDL_Texture* GetSdlTexture() const	{ return pSdlTexture; }

private:
public:
	Texture();
	~Texture();

	bool Load(IRenderer& _renderer, const std::string& _filename);
	bool LoadSdl(RendererSdl* _renderer, const std::string& _filename, SDL_Surface* _pSurface);
	bool LoadGl(RendererGl* _renderer, const std::string& _filename, SDL_Surface* _pSurface);
	void SetActive() const;
	void Unload();
	void UpdateInfo(uint16_t& _pWidthOut, uint16_t& _pHeightOut);
};