#pragma once
#include <string>
#include <SDL_image.h>
#include "CommonLib.h"

class RendererSdl;
class Texture
{
private:
	std::string mFileName;
	SDL_Texture* pSdlTexture;
	uint16_t mWidth;
	uint16_t mHeight;

public:
	Vector2 GetSize()		const	{ return Vector2{ (float)mWidth, (float)mHeight }; }
	uint16_t GetWidth()		const	{ return mWidth; }
	uint16_t GetHeight()	const	{ return mHeight; }
	SDL_Texture* GetSdlTexture()	const	{ return pSdlTexture; }

private:
public:
	Texture();
	~Texture();

	bool Load(RendererSdl& _renderer, const std::string& _filename);
	void Unload();
	void UpdateInfo(uint16_t& _pWidthOut, uint16_t& _pHeightOut);
};