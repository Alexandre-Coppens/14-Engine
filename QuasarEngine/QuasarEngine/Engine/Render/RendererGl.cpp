#include "RendererGl.h"

#include <SDL_image.h>
#include "glew.h"
#include "Engine/Scene.h"

#include "Engine/Render/Window.h"
#include "Engine/Render/VertexArray.h"
#include "Engine/Utilitaries/MathLib.h"
#include "Engine/Render/Shaders/ShaderProgram.h"

#include "Engine/Utilitaries/Log.h"
#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Managers/CameraManager.h"

#include "Engine/3D/cModel.h"
#include "Engine/2D/Sprite2D.h"
#include "Engine/3D/Mesh.h"
#include "Engine/Utilitaries/DebugMemoryLeakCatcher.h"
#include "Engine/Utilitaries/Time.h"

RendererGl::RendererGl():
	pWindow(nullptr), 
	pSpriteVao(nullptr), 
	mContext(nullptr), 
	pSpriteShaderProgram(nullptr),
	mModelDrawOrder(std::map<ShaderProgram*, std::vector<Model*>>()),
	mSpriteViewProj(Mat4RowCreateSimpleViewProj(-Window::GetSize().x, Window::GetSize().y)),
	mView(Mat4RowCreateLookAt(Vector3(0, 0, 5), Vector3UnitX(), Vector3UnitZ())),
	mProj(Mat4RowCreatePerspectiveFOV(70.0f, Window::GetSize().x, Window::GetSize().y, 0.01f, 10000.0f))
{
	DEBUGAddClass("RendererGL");
}

RendererGl::~RendererGl() = default;

bool RendererGl::Initialize(Window& _rWindow)
{
	pWindow = &_rWindow;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	SDL_GL_SetSwapInterval(0);
	
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
	
	pSpriteVao = new VertexArray(spriteVertices, 4);

	glPatchParameteri(GL_PATCH_VERTICES, 3);
	
	return true;
}

void RendererGl::BeginDraw()
{
	CameraManager::UpdateCurrentCamera();
	glClearColor(0.016f, 0.0f, 0.051f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererGl::Draw()
{
	Scene::ActiveScene->Draw();
	DrawModels();
	DrawSprites();
}

//Draws all the Models via the ShaderLists
void RendererGl::DrawModels() const
{
	if (mModelDrawOrder.empty()) return;

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	
	float time = Time::currentFrameTime;
	
	for (auto& [shader, modelList] : mModelDrawOrder)
	{
		if (!shader || modelList.empty()) continue;
		shader->Use();
		
		shader->SetFloat("uTime", time);
		shader->SetMatrix4Row("uViewProj", mView * mProj);
		
		for (Model* model : modelList)
		{
			model->Draw();
		}
	}
}

void RendererGl::DrawSprites() {
	if (mSpriteList.empty()) return;

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	
	auto* shader = Assets::GetShaderProgram(PROG_Sprite);
	shader->Use();
	shader->SetInteger("uTexture", 0);
	shader->SetFloat("uTime", Time::currentFrameTime);
	shader->SetMatrix4Row("uViewProj", mSpriteViewProj);
	
	for (int i = 0; i < static_cast<int>(mSpriteList.size()); i++) {
		for (Sprite2D* sprite : mSpriteList[i]) {
			sprite->DrawGL(shader);
		}
	}
}

void RendererGl::AddSprite(Sprite2D* _pSprite, int _drawOrder)
{
	while (static_cast<int>(mSpriteList.size()) <= _drawOrder)
	{
		mSpriteList.push_back(std::vector<Sprite2D*>());
	}
	mSpriteList[_drawOrder].push_back(_pSprite);
}

void RendererGl::RemoveSprite(Sprite2D* _pSprite, int _drawOrder)
{
	mSpriteList[_drawOrder].erase(std::find(mSpriteList[_drawOrder].begin(), mSpriteList[_drawOrder].end(), _pSprite));
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
	
	pWindow = nullptr;
	pSpriteShaderProgram = nullptr;
	mModelDrawOrder.clear();
	mSpriteList.clear();
	
	DEBUGRemoveClass("RendererGL");
}

void RendererGl::AddModel(Model* _pModel, ShaderProgram* _pShaderProgram)
{
	mModelDrawOrder[_pShaderProgram].push_back(_pModel);
}

void RendererGl::RemoveModel(Model* _pModel, ShaderProgram* _pShaderProgram )
{
	std::vector<Model*>::iterator it;
	it = std::find(mModelDrawOrder[_pShaderProgram].begin(), mModelDrawOrder[_pShaderProgram].end(), _pModel);
	mModelDrawOrder[_pShaderProgram].erase(it);
}

void RendererGl::AddShaderProgram(ShaderProgram* _pShaderProgram)
{
	mModelDrawOrder[_pShaderProgram] = std::vector<Model*>();
}

void RendererGl::RemoveShaderProgram(ShaderProgram* _pShaderProgram)
{
	//TODO: Create a default shaderProgram for all the models without shaders
}
