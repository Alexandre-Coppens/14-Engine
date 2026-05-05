#include "ImguiManager.h"

#include "Engine/.ImGuiFiles/imgui.h"
#include "Engine/.ImGuiFiles/imgui_impl_opengl3.h"
#include "Engine/.ImGuiFiles/imgui_impl_sdl2.h"

#include "Engine/Render/IRenderer.h"
#include "Engine/Render/RendererGl.h"
#include "Engine/Utilitaries/Assets.h"

void ImguiManager::Initialize(IRenderer* _renderer, Window* _window)
{
	if (_renderer->getType() == RendererType::OPENGL)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	
		ImGui_ImplSDL2_InitForOpenGL(_window->GetSdlWindow(), dynamic_cast<RendererGl*>(_renderer)->getContext());
		ImGui_ImplOpenGL3_Init();
	}
}

void ImguiManager::PullEvents(SDL_Event* _events)
{
	ImGui_ImplSDL2_ProcessEvent(_events);
}

void ImguiManager::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();
}

void ImguiManager::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiManager::Close()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}