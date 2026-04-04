#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "Actor.h"

using std::string;
using std::vector;
using std::map;

class UI_TilesMenu : public Actor {
private:
    bool open{ false };
    Rectangle rectangle{};
    float scroll = 0;
    string currentTextureName {};

public:
    UI_TilesMenu();
    ~UI_TilesMenu();

    void Draw(Vector2 Scroll);
    void Update();
    void Clicked();

    void OpenTilesTab();
    bool GetOpen() { return open; }
    string GetTexture() {return currentTextureName;}
    void SetTexture(string textureName) {currentTextureName = textureName;}
};