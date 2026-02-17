#include "RendererGl.h"
#include "glew.h"
#include "Log.h"
#include "Material.h"
#include "Assets.h"
#include <SDL_image.h>

RendererGl::RendererGl():
	pWindow(nullptr), pVao(nullptr), mContext(nullptr)
{
}

RendererGl::~RendererGl()
{
	//Close();
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
	mViewProj = Mat4RowCreateSimpleViewProj(800, 800);
	return true;
}

void RendererGl::BeginDraw()
{
	glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (pShaderProgram != nullptr) pShaderProgram->Use();
	pShaderProgram->SetMatrix4Row("uViewProj", mViewProj);

	pVao->SetActive();
}

void RendererGl::Draw()
{
	DrawSprites();
}

void RendererGl::DrawSprites()
{
	if (mSpriteList.empty()) return;
	for (Material* sprite : mSpriteList)
	{
		sprite->Draw(*this, DebugMode::DRAWCOLLISIONS);
	}
}

void RendererGl::EndDraw()
{
	SDL_GL_SwapWindow(pWindow->GetSdlWindow());
}

void RendererGl::DrawSprite(Actor& pActor, Texture* pTex, Rectangle pSourceRect, Vector2 pOrigin,Flip pFlip) const
{
	pShaderProgram->Use();
	pActor.getTransform3D()->ComputeWorldTransform();
	Matrix4Row scaleMat = Mat4RowCreateScale(
		pTex->GetWidth(),
		pTex->GetHeight(),
		0.0f);
	Matrix4Row world = scaleMat * pActor.getTransform3D()->getWorldTransform();
	pShaderProgram->SetMatrix4Row("uWorldTransform", world);
	uniforms doesn't seems to work'
	pTex->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void RendererGl::Close()
{
	SDL_GL_DeleteContext(mContext);
	delete pVao;
	pVao = nullptr;
}

void RendererGl::AddSprite(Material* _pSprite)
{
	int spriteDrawOrder = _pSprite->getDrawOrder();
	std::vector<Material*>::iterator it;
	for (it = mSpriteList.begin(); it != mSpriteList.end(); it++)
	{
		if (spriteDrawOrder < (*it)->getDrawOrder()) break;
	}
	mSpriteList.insert(it, _pSprite);
}

void RendererGl::RemoveSprite(Material* _pSprite)
{
	std::vector<Material*>::iterator it;
	it = std::find(mSpriteList.begin(), mSpriteList.end(), _pSprite);
	mSpriteList.erase(it);
}