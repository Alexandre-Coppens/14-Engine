#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "Actor.h"

using std::string;
using std::vector;
using std::map;

enum Gizmo
{
    Vertex,
    Edge,
};

class Terrain {
private:
public:
    struct Wall{
        int start;
        int end;
        float floor   { 0 };
        float ceiling { 3 };
        int dictionaryTexture{ 0 };
        
        bool computed{ false };
        Vector3 location {Vector3Zero()};
        Vector3 rotation {Vector3Zero()};
        Vector3 size     {Vector3Zero()};
    };
    
    static int verticesCount;
    static map<int, Vector2> wallVertices;
    static vector<Wall> wallList;

    static map<int, string> dictionary;
    
    static float gridMeterInPixels;
    static int   gridSubdivision;
    static float wallDrawSize;
    
    static Vector2 position;
    static short maxLayer;
    
    static Gizmo nearGizmo;
    static int nearIndice;

private:
public:
    Terrain();
    ~Terrain();

    void Update();

    static int AddNewVertex(Vector2 pos);
    static void AddNewWall(Wall wall);
    static void AddToDictionary(int index, string name);
    static int CheckInDictionary(string n);

    static void ComputeWall(Wall& wall);
    
    static void ISCursorOnSomething(Vector2 position);
    
    static void SaveMap(string fileName);
    static void LoadMap(string fileName);
    static vector<string> BreakString(string str, char breacker);
};