#include "RendererGl.h"
#include "glew.h"
#include "Log.h"
#include "cSprite2D.h"
#include <SDL_image.h>

RendererGl::RendererGl():
	pWindow(nullptr), pVao(nullptr), mContext(nullptr)
{
}

RendererGl::~RendererGl()
{
	delete pVao;
}

bool RendererGl::Initialize(Window& _rWindow)
{
	pWindow = &_rWindow;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mContext = SDL_GL_CreateContext(pWindow->GetSdlWindow());
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		Log::Error(LogType::Video, "Failed to Initialize GLEW");
		return false;
	}
	glGetError();

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		Log::Error(LogType::Video, "Failed to initialize SDL_Image");
	}
	pVao = new VertexArray(vertices, 4, indices, 6);
	return true;
}

void RendererGl::BeginDraw()
{
	glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (pShaderProgram != nullptr) pShaderProgram->Use();
	pVao->SetActive();
}

void RendererGl::Draw()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void RendererGl::DrawSprites()
{
}

void RendererGl::EndDraw()
{
	SDL_GL_SwapWindow(pWindow->GetSdlWindow());
}

void RendererGl::DrawSprite(Actor& pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin,Flip pFlip) const
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}


void RendererGl::Close()
{
	SDL_GL_DeleteContext(mContext);
	delete pVao;
}

void RendererGl::AddSprite(Sprite2D* _pSprite)
{
	int spriteDrawOrder = _pSprite->getDrawOrder();
	std::vector<Sprite2D*>::iterator it;
	for (it = mSprites.begin(); it != mSprites.end(); it++)
	{
		if (spriteDrawOrder < (*it)->getDrawOrder()) break;
	}
	mSprites.insert(it, _pSprite);
}

void RendererGl::RemoveSprite(Sprite2D* _pSprite)
{
	std::vector<Sprite2D*>::iterator it;
	it = std::find(mSprites.begin(), mSprites.end(), _pSprite);
	mSprites.erase(it);
}