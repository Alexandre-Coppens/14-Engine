#pragma once

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include <string>
#include <vector>
#include "AssetsList.h"

using std::string;
using std::vector;

class Engine {
private:
	AssetList* assets{};
	Vector2 scroll{};
	Vector2 scrollSpeed{ 150, 150};
	
	int startVertex;
	int endVertex;

private:
    void CheckIfOutOfBound();

public:
	Engine();
	void Start();
	void Update();
	void Draw();
};
