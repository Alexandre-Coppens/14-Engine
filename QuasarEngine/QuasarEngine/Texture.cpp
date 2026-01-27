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
	sFileName = _filename;
	SDL_Surface* surface = IMG_Load(sFileName.c_str());
	if (!surface)
	{
		Log::Error(LogType::Application, "Failed to load texture file :" + sFileName);
		return false;
	}
	u16Width = surface->w;
	u16Height = surface->h;

	//Create Texture from surface
	pSdlTexture = SDL_CreateTextureFromSurface(_renderer.GetSdlRenderer(), surface);
	SDL_FreeSurface(surface);
	if (!pSdlTexture)
	{
		Log::Error(LogType::Render, "Failed to convert surface to texture: " + sFileName);
		return false;
	}
	Log::Info("Loaded Texture: " + sFileName);
	return true;
}

void Texture::Unload()
{
	if (pSdlTexture) SDL_DestroyTexture(pSdlTexture);
}

void Texture::UpdateInfo(uint16_t& _pWidthOut, uint16_t& _pHeightOut)
{
	_pWidthOut	= u16Width;
	_pHeightOut = u16Height;
}
