#include "Texture.h"
#include "Renderer.h"
#include "Log.h"
#include "Scene.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

bool Texture::Load(Renderer& _renderer, const std::string& _filename)
{
	mFileName = _filename;
	SDL_Surface* surface = IMG_Load(mFileName.c_str());
	if (!surface)
	{
		Log::Error(LogType::Application, "Failed to load texture file :" + mFileName);
		return false;
	}
	mWidth = surface->w;
	mHeight = surface->h;

	//Create Texture from surface
	pSdlTexture = SDL_CreateTextureFromSurface(_renderer.getSdlRenderer(), surface);
	SDL_FreeSurface(surface);
	if (!pSdlTexture)
	{
		Log::Error(LogType::Render, "Failed to convert surface to texture: " + mFileName);
		return false;
	}
	Log::Info("Loaded Texture: " + mFileName);
	return true;
}

void Texture::Unload()
{
	if (pSdlTexture) SDL_DestroyTexture(pSdlTexture);
}

void Texture::UpdateInfo(uint16_t& _pWidthOut, uint16_t& _pHeightOut)
{
	_pWidthOut	= mWidth;
	_pHeightOut = mHeight;
}
