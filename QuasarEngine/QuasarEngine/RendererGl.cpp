#include "RendererGl.h"
#include "Window.h"
#include "glew.h"
#include "Log.h"
#include "cModel.h"
#include "Assets.h"
#include <SDL_image.h>

RendererGl::RendererGl():
	pWindow(nullptr), 
	pSpriteVao(nullptr), 
	mContext(nullptr), 
	pSpriteShaderProgram(nullptr),
	mSpriteViewProj(Mat4RowCreateSimpleViewProj(Window::GetSize().x, Window::GetSize().y)),
	continue here
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
	pSpriteVao = new VertexArray(vertices, 4, indices, 6);
	mView = Mat4RowCreateSimpleViewProj(800, 800);
	return true;
}

void RendererGl::BeginDraw()
{
	glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	pSpriteVao->SetActive();
}

void RendererGl::Draw()
{
	DrawModels();
}

void RendererGl::DrawModels()
{
	if (mModelList.empty()) return;
	for (Model* model : mModelList)
	{
		model->Draw(mView);
	}
}

void RendererGl::EndDraw()
{
	SDL_GL_SwapWindow(pWindow->GetSdlWindow());
}

void RendererGl::Close()
{
	SDL_GL_DeleteContext(mContext);
	delete pSpriteVao;
	pSpriteVao = nullptr;
}

void RendererGl::AddModel(Model* _pModel)
{
	mModelList.push_back(_pModel);
}

void RendererGl::RemoveModel(Model* _pModel)
{
	std::vector<Model*>::iterator it;
	it = std::find(mModelList.begin(), mModelList.end(), _pModel);
	mModelList.erase(it);
}