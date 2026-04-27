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
	
	SDL_Surface* converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
	SDL_FreeSurface(surface);
	
	//HACK: Rotating the texture 90d cw to fit with blender export
	SDL_Surface* rotated = SDL_CreateRGBSurfaceWithFormat(0, converted->h, converted->w, converted->format->BitsPerPixel, converted->format->format);

	int bpp = converted->format->BytesPerPixel;

	for (int y = 0; y < converted->h; y++)
	{
		for (int x = 0; x < converted->w; x++)
		{
			memcpy(
				(char*)rotated->pixels + x * rotated->pitch + (converted->h - 1 - y) * bpp,
				(char*)converted->pixels + y * converted->pitch + x * bpp,
				bpp
			);
		}
	}
	
	SDL_FreeSurface(converted);
	
	if (_renderer.getType() == RendererType::SDL)
		return LoadSdl(dynamic_cast<RendererSdl*>(&_renderer), _filePath, rotated);
	return LoadGl(dynamic_cast<RendererGl*>(&_renderer), _filePath, rotated);
}

bool Texture::LoadGl(RendererGl* _renderer, const std::string& _filename, SDL_Surface* _pSurface)
{
	bool hasAlpha = SDL_ISPIXELFORMAT_ALPHA(_pSurface->format->format);
	int format = hasAlpha ? GL_RGBA : GL_RGB;
	
	SDL_PixelFormatEnum targetFormat = hasAlpha ? SDL_PIXELFORMAT_RGBA32 : SDL_PIXELFORMAT_RGB24;
	SDL_Surface* glSurface = SDL_ConvertSurfaceFormat(_pSurface, targetFormat, 0);
	
	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	
	glPixelStorei(GL_UNPACK_ROW_LENGTH, glSurface->pitch / glSurface->format->BytesPerPixel);
	Log::Info("Pitch: " + std::to_string(glSurface->pitch) + " expected: " + std::to_string(glSurface->w * glSurface->format->BytesPerPixel), LogLevel::Normal);
	
	glTexImage2D(GL_TEXTURE_2D, 0, format, glSurface->w,  glSurface->h, 0, format, GL_UNSIGNED_BYTE, glSurface->pixels);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	
	glGenerateMipmap(GL_TEXTURE_2D);
	SDL_FreeSurface(_pSurface);
	SDL_FreeSurface(glSurface);
	Log::Info("Loaded GL texture : " + mFileName, LogLevel::Normal);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return true;
}

void Texture::SetActive() const {
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
	Log::Info("Loaded Texture: " + mFileName, LogLevel::Normal);
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
