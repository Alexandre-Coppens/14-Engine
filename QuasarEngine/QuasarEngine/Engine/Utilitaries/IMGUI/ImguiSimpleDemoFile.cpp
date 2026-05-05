// dear imgui - simplified demo (SDL2 + OpenGL3 backend)

#include "Engine/Utilitaries/Managers/ImguiManager.h"

#include "Engine/.ImGuiFiles/imgui.h"
#include <SDL.h>
#include <SDL_opengl.h>

static bool  show_demo    = false;
static bool  show_another = false;
static float f            = 0.0f;
static int   counter      = 0;
static char  buf[128]     = "hello";
static float col[3]       = {0.4f, 0.7f, 0.2f};

void ShowMyWindow()
{
    ImGui::Begin("My First Tool");

    ImGui::Text("A simple window with common widgets.");
    ImGui::Separator();

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::ColorEdit3("color", col);
    ImGui::InputText("input", buf, IM_ARRAYSIZE(buf));

    if (ImGui::Button("Click me"))
        counter++;
    ImGui::SameLine();
    ImGui::Text("count = %d", counter);

    ImGui::Separator();

    if (ImGui::CollapsingHeader("More stuff"))
    {
        ImGui::Indent();
        ImGui::BulletText("Bullet A");
        ImGui::BulletText("Bullet B");
        static int item = 0;
        const char* items[] = { "Apple", "Banana", "Cherry" };
        ImGui::Combo("combo", &item, items, IM_ARRAYSIZE(items));
        ImGui::Unindent();
    }

    ImGui::Separator();
    ImGui::Checkbox("Show demo window",    &show_demo);
    ImGui::Checkbox("Show another window", &show_another);

    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
    ImGui::End();
}

void ShowAnotherWindow()
{
    ImGui::Begin("Another Window", &show_another);
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close")) show_another = false;
    ImGui::End();
}