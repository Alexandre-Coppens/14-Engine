#include "Texture.h"
#include "glew.h"

#include "Engine/Utilitaries/Log.h"
#include "Engine/Utilitaries/DebugMemoryLeakCatcher.h"

#include "Engine/Render/IRenderer.h"
#include "Engine/Render/RendererSdl.h"
#include "Engine/Render/RendererGl.h"

Texture::Texture()
{
	DEBUGAddClass("Texture");
}

Texture::~Texture() = default;

bool Texture::Load(IRenderer& _renderer, const std::string& _filePath)
{
	mFileName = _filePath;
	SDL_Surface* surface = IMG_Load(mFileName.c_str());
	if (!surface)
	{
		Log::Error(LogType::Application, "Failed to load texture file :" + mFileName);
		return false;
	}
	mWidth  = static_cast<Uint16>(surface->w);
	mHeight = static_cast<Uint16>(surface->h);
	
	SDL_Surface* flipped = SDL_CreateRGBSurface(0, surface->h, surface->w, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);
	
	for (int y = 1; y < surface->h; y++)
	{
		for (int x = 1; x < surface->w; x++) {
			memcpy(
				(char*)flipped->pixels + (flipped->pitch * x) + (flipped->pitch - (y + 1) * flipped->format->BytesPerPixel),
				(char*)surface->pixels + (y * flipped->pitch) + (x * flipped->format->BytesPerPixel),
				flipped->format->BytesPerPixel
			);
		}
	}
	
	SDL_FreeSurface(surface);
	
	if (_renderer.getType() == RendererType::SDL)
		return LoadSdl(dynamic_cast<RendererSdl*>(&_renderer), _filePath, flipped);
	return LoadGl(dynamic_cast<RendererGl*>(&_renderer), _filePath, flipped);
}

bool Texture::LoadGl(RendererGl* _renderer, const std::string& _filename, SDL_Surface* _pSurface)
{
	int format = 0;
	SDL_Surface* glSurface = SDL_ConvertSurfaceFormat(_pSurface, SDL_PIXELFORMAT_RGBA32, 0);

	if (glSurface->format->format == SDL_PIXELFORMAT_RGB24) // REMOVE OR FIND A WAY TO SEPARATE ALPHA OR NOT
	{
		format = GL_RGB;
	}
	else if (glSurface->format->format == SDL_PIXELFORMAT_RGBA32)
	{
		format = GL_RGBA;
	}

	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, glSurface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	SDL_FreeSurface(_pSurface);
	SDL_FreeSurface(glSurface);
	Log::Info("Loaded GL texture : " + mFileName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	return true;
}

void Texture::SetActive() const
{
	glBindTexture(GL_TEXTURE_2D, mTextureId);
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
	else glDeleteTextures(1, &mTextureId);
	DEBUGRemoveClass("Texture");
}

void Texture::UpdateInfo(float& _pWidthOut, float& _pHeightOut)
{
	_pWidthOut	= mWidth;
	_pHeightOut = mHeight;
}
