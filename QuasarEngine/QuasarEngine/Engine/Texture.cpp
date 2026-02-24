#include "Texture.h"
#include "glew.h"

#include "Engine/Utilitaries/Log.h"

#include "Engine/Render/IRenderer.h"
#include "Engine/Render/RendererSdl.h"
#include "Engine/Render/RendererGl.h"

#include "Scene.h"

Texture::Texture()
{
}

Texture::~Texture()
{
	Unload();
}

bool Texture::Load(IRenderer& _renderer, const std::string& _filename)
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

	if (_renderer.getType() == RendererType::SDL)
		return LoadSdl(dynamic_cast<RendererSdl*>(&_renderer), _filename, surface);
	return LoadGl(dynamic_cast<RendererGl*>(&_renderer), _filename, surface);
}

bool Texture::LoadGl(RendererGl* _renderer, const std::string& _filename, SDL_Surface* _pSurface)
{
	int format = 0;
	SDL_Surface* glSurface = SDL_ConvertSurfaceFormat(_pSurface, SDL_PIXELFORMAT_RGBA32, 0);

	if (glSurface->format->format == SDL_PIXELFORMAT_RGB24) // REMOVE OR FIND A WAY TO SEPARETE ALPHA OR NOT
	{
		format = GL_RGB;
	}
	else if (glSurface->format->format == SDL_PIXELFORMAT_RGBA32)
	{
		format = GL_RGBA;
	}

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, glSurface->pixels);
	SDL_FreeSurface(_pSurface);
	SDL_FreeSurface(glSurface);
	Log::Info("Loaded GL texture : " + mFileName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void Texture::SetActive() const
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}

bool Texture::LoadSdl(RendererSdl* _renderer, const std::string& _filename, SDL_Surface* _pSurface)
{
	//Create Texture from surface
	pSdlTexture = SDL_CreateTextureFromSurface(_renderer->getSdlRenderer(), _pSurface);
	SDL_FreeSurface(_pSurface);
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
	else glDeleteTextures(1, &mTextureID);
}

void Texture::UpdateInfo(uint16_t& _pWidthOut, uint16_t& _pHeightOut)
{
	_pWidthOut	= mWidth;
	_pHeightOut = mHeight;
}
