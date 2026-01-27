#pragma once
#include <string>
#include <SDL_image.h>
#include "CommonLib.h"

class Renderer;
class Texture
{
private:
	std::string sFileName;
	SDL_Texture* pSdlTexture;
	uint16_t u16Width;
	uint16_t u16Height;

public:
	Vector2 GetSize()		const	{ return Vector2{ (float)u16Width, (float)u16Height }; }
	uint16_t GetWidth()		const	{ return u16Width; }
	uint16_t GetHeight()	const	{ return u16Height; }
	SDL_Texture* GetSdlTexture()	const	{ return pSdlTexture; }

private:
public:
	Texture();
	~Texture();

	bool Load(Renderer& _renderer, const std::string& _filename);
	void Unload();
	void UpdateInfo(uint16_t& _pWidthOut, uint16_t& _pHeightOut);
};