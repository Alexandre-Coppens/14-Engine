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
    Rectangle interactibleBar{};

public:

private:
public:
    UI_TilesMenu();
    ~UI_TilesMenu();

    void Draw();
    void Update();
    int Clicked();

    void OpenTilesTab();
};