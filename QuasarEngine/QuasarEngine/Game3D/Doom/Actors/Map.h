#pragma once
#include <map>
#include <string>

#include "Engine/.EngineGenerated/Generated.h"
#include "Engine/Utilitaries/CommonLib.h"
#include "Engine/Utilitaries/MathLib.h"
#include "Engine/3D/cTransform3D.h"
#include "Engine/Render/VertexArray.h"
#include "Engine/Render/Shaders/ShaderProgram.h"

class Texture;

constexpr float MAP_SCALE = 0.03f;
constexpr float FLOOR_TILESIZE = 5.0f;

struct MapWall
{
    GENERATED_TEXTURE texture;
    VertexArray* Vertices;
    MapWall(): texture(), Vertices(nullptr) {};
};

struct MapFloor
{
    GENERATED_TEXTURE texture;
    VertexArray* VerticesFloor;
    VertexArray* VerticesCeiling;
    MapFloor(): texture(), VerticesFloor(nullptr), VerticesCeiling(nullptr) {};
};

//Thanks Joa!
class Map
{

private:
    std::map<int, std::string> mTextureMap;
    std::vector<MapWall> mWallList;
    std::vector<MapFloor> mFloorList;
    std::map<int, Vector3> mVertices;
    
    Actor* mapActor;

    void ResolveDict(const std::string& pLine);
    void ResolveWall(const std::string& pLine);
    void ResolveVertex(const std::string& pLine);
    void ResolveFloor(const std::string& pLine);
    void ResolveActor(const std::string& pLine);
    
public:
    Map() = delete;
    explicit Map(const std::string& pPath);
    
    void Draw(ShaderProgram* _shader);
};
