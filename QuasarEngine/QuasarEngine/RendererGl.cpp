#include "RendererGl.h"

#include <SDL_image.h>
#include "Window.h"
#include "glew.h"
#include "Log.h"
#include "Assets.h"
#include "CameraManager.h"

#include "VertexArray.h"
#include "ShaderProgram.h"

#include "cModel.h"
#include "cSprite2D.h"

RendererGl::RendererGl():
	pWindow(nullptr), 
	pSpriteVao(nullptr), 
	mContext(nullptr), 
	pSpriteShaderProgram(nullptr),
	mSpriteViewProj(Mat4RowCreateSimpleViewProj(Window::GetSize().x, Window::GetSize().y)),
	mView(Mat4RowCreateLookAt(Vector3(0, 0, 5), Vector3UnitX(), Vector3UnitZ())),
	mProj(Mat4RowCreatePerspectiveFOV(70.0f, Window::GetSize().x, Window::GetSize().y, 0.01f, 10000.0f))
{
}

RendererGl::~RendererGl() = default;

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
	
	pSpriteVao = new VertexArray(spriteVertices, 4);

	//Load the NULL Shader
	Assets::LoadShader(this, "NULL.vert", "NULL.frag", "NULL", DrawOption::NULL_SHADER);
	Assets::LoadTexture(*dynamic_cast<IRenderer*>(this), "Resources/NullShader.png", "NULLSHADER");
	Assets::LoadTexture(*dynamic_cast<IRenderer*>(this), "Resources/NullTexture.png", "NULLTEXTURE");
	
	return true;
}

void RendererGl::BeginDraw()
{
	CameraManager::UpdateCurrentCamera();
	glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererGl::Draw()
{
	DrawModels();
	DrawSprites();
}

//Draws all the Models via the ShaderLists
void RendererGl::DrawModels() const
{
	if (mModelDrawOrder.empty()) return;

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	
	for (auto& shader : mModelDrawOrder)
	{
		DrawOption argument = (shader.first == Assets::GetShader("NULL") ? DrawOption::NULL_SHADER : DrawOption::TEXTURE);
		glBindTexture(GL_TEXTURE_2D, 0);
		shader.first->Use();
		shader.first->SetMatrix4Row("uViewProj", mView * mProj);
		for (Model* model : shader.second)
		{
			model->Draw(shader.first->getDrawOptions() | DrawOption::DEBUG);
		}
	}
}

void RendererGl::DrawSprites()
{
	if (mSpriteList.empty()) return;

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (pSpriteShaderProgram != nullptr) pSpriteShaderProgram->Use();
	pSpriteShaderProgram->SetMatrix4Row("uViewProj", mSpriteViewProj);
	pSpriteVao->SetActive();

	for (Sprite2D* sprite : mSpriteList)
	{
		//sprite->Draw(*this, DebugMode::DRAW_COLLISIONS);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		//TODO: Add a plane object to create ui sprites
	}
}

void RendererGl::AddSprite(Sprite2D* _pSprite)
{
}

void RendererGl::RemoveSprite(Sprite2D* _pSprite)
{
}

void RendererGl::EndDraw()
{
	SDL_GL_SwapWindow(pWindow->GetSdlWindow()); //TODO Fix this breakpoint error
}

void RendererGl::Close()
{
	SDL_GL_DeleteContext(mContext);
	delete pSpriteVao;
	pSpriteVao = nullptr;
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
	mModelDrawOrder[_pShaderProgram];
}

void RendererGl::RemoveShaderProgram(ShaderProgram* _pShaderProgram)
{
	//TODO: Create a default shaderProgram for all the models without shaders
}
