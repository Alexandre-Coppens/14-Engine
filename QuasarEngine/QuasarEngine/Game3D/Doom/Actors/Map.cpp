#include "Map.h"

#include <fstream>
#include <iostream>

#include "Engine/Utilitaries/Assets.h"
#include "Engine/Scene.h"
#include "Engine/.Prefabs/Object.h"
#include "Engine/3D/cBoxCollider.h"
#include "Engine/Utilitaries/Log.h"
#include "Game3D/Doom/Actors/Door.h"

using std::ifstream;

//Thanks Joa!
Map::Map(const std::string& pPath)
{
    mapActor = new Actor(true);
    
    std::string line;
    ifstream myFile;
    
    myFile.open(pPath);

    //Check for errors
    if (myFile.fail()) {
        Log::Info("Failed to open map : " + pPath, LogLevel::Error);
    }

    while (std::getline(myFile, line)) {
        switch (line[0])
        {
        case '$':
            Log::Info("Reading map with version : " + BreakString(line, ' ')[1], LogLevel::Normal);
            break;
            
        case 'D' :
            ResolveDict(line);
            break;

        case 'F' :
            ResolveFloor(line);
            break;

        case 'V':
            ResolveVertex(line);
            break;

        case 'W':
            ResolveWall(line);
            break;
            
        case 'A':
            ResolveActor(line);
            
        default:
            break;
        }
        
    }

    myFile.close();
}

void Map::Draw(ShaderProgram* _shader)
{
    for (MapWall wall : mWallList)
    {
        Assets::GetTexture(wall.texture)->SetActive();
        _shader->SetMatrix4Row("uWorldTransform", Matrix4Row::Mat4RowIdentity());
        wall.Vertices->SetActive();

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    for (MapFloor floor : mFloorList)
    {
        Assets::GetTexture(floor.texture)->SetActive();
        _shader->SetMatrix4Row("uWorldTransform", Matrix4Row::Mat4RowIdentity());
        
        floor.VerticesFloor->SetActive();
        glDrawArrays(GL_TRIANGLE_FAN, 0, floor.VerticesFloor->GetVerticesCount());

        if (floor.VerticesCeiling != nullptr)
        {
            floor.VerticesCeiling->SetActive();
            glDrawArrays(GL_TRIANGLE_FAN, 0, floor.VerticesCeiling->GetVerticesCount());
        }
    }
}

void Map::ResolveDict(const std::string& pLine)
{
    auto dict = BreakString(BreakString(pLine, ' ')[1], ':');
    mTextureMap[std::stoi(dict[0])] = dict[1];
}

void Map::ResolveWall(const std::string& pLine)
{
    // W int(start) int(end) int(dictionaryPointer) vec3(location) vec3(rotation) vec3(size)
    const auto brokeLine = BreakString(pLine, ' ');

    const auto brokePos = BreakString(brokeLine[4], ':');
    const auto brokeRot = BreakString(brokeLine[5], ':');
    const auto brokeScale = BreakString(brokeLine[6], ':');

    Vector3 pos = Vector3(stof(brokePos[0]), std::stof(brokePos[1]), 0.0f) * MAP_SCALE;
    Vector3 scale = Vector3(stof(brokeScale[0]), std::stof(brokeScale[1]), 0.0f) * 0.5f * MAP_SCALE;
    pos.z = std::stof(brokePos[2]);
    scale.z = std::stof(brokeScale[2]) * 0.5f;
    const float rotation = stof(brokeRot[2]) + 90.0f;

    Vector3 left = mVertices[std::stoi(brokeLine[1])];
    Vector3 right = mVertices[std::stoi(brokeLine[2])];
    float distance = Distance(left, right);

    std::vector<float> spriteVertices = {
        //POSITION                      NORMALS                TEXCOORDS
        left.x, left.y,   pos.z + scale.z,    0.0f, 0.0f, 0.0f,      0.0f,     0.0f,            //top left
        left.x, left.y,   pos.z - scale.z,    0.0f, 0.0f, 0.0f,      0.0f,     scale.z * 2,     //bottom left
        right.x, right.y, pos.z + scale.z,    0.0f, 0.0f, 0.0f,      distance, 0.0f,            //top right
        right.x, right.y, pos.z - scale.z,    0.0f, 0.0f, 0.0f,      distance, scale.z * 2,     //bottom right
    };
    
    MapWall wall;
    wall.texture = getTextureEnum(mTextureMap[std::stoi(brokeLine[3])]);
    wall.Vertices = new VertexArray(spriteVertices.data(), spriteVertices.size());
    mWallList.push_back(wall);

    BoxCollider* collider = dynamic_cast<BoxCollider*>(mapActor->AddComponent(new BoxCollider(mapActor)));
    collider->getTransform()->setLocation(pos);
    collider->getTransform()->addRotationZ(rotation);
    collider->getTransform()->setScale(scale * 2.0f);

    wall.Vertices = nullptr;
}

void Map::ResolveVertex(const std::string& pLine)
{
    // V int(iterator) vec2(location)
    const auto brokeLine = BreakString(pLine, ' ');
    const int indice = std::stoi(brokeLine[1]);

    const auto brokePos = BreakString(brokeLine[2], ':');
    const Vector3 pos = Vector3(stof(brokePos[0]), std::stof(brokePos[1]), 0.0f) * MAP_SCALE;

    mVertices[indice] = pos;
}

void Map::ResolveFloor(const std::string& pLine)
{
    // F int(nbr vertices) Vector2(center) vec<int>(vertices) int(dictionaryPointer) float(floor) float(ceiling)
    const auto brokeLine = BreakString(pLine, ' ');

    if (std::stoi(brokeLine[1]) == 0) return;
    
    const auto brokeindices = BreakString(brokeLine[3], ':');
    const auto brokeCenter = BreakString(brokeLine[2], ':');
    const float floorHeight = std::stof(brokeLine[5]);
    const float ceilingHeight = std::stof(brokeLine[6]);

    std::vector<int> indices;
    for (std::string strIndex : brokeindices)
    {
        indices.push_back(stoi(strIndex));
    }
    indices.push_back(indices[0]);

    float maxX = INFINITY_NEG;
    float minX = INFINITY_POS;
    float maxY = INFINITY_NEG;
    float minY = INFINITY_POS;

    std::vector<float> floorVertices((std::stoi(brokeLine[1]) + 2) * 8, 0.0f);
    std::vector<float> ceilingVertices((std::stoi(brokeLine[1]) + 2) * 8, 0.0f);

    Vector2 center = Vector2(std::stof(brokeCenter[0]), std::stof(brokeCenter[1])) * MAP_SCALE;
    
    floorVertices[0] = center.x;
    floorVertices[1] = center.y;
    floorVertices[2] = floorHeight;
    floorVertices[3] = 0.0f;
    floorVertices[4] = 1.0f;
    floorVertices[5] = 0.0f;
    floorVertices[6] = center.x;
    floorVertices[7] = center.y;

    ceilingVertices[0] = center.x;
    ceilingVertices[1] = center.y;
    ceilingVertices[2] = ceilingHeight;
    ceilingVertices[3] = 0.0f;
    ceilingVertices[4] = -1.0f;
    ceilingVertices[5] = 0.0f;
    ceilingVertices[6] = center.x;
    ceilingVertices[7] = center.y;

    for (int i = 1; i <= static_cast<int>(indices.size()); i++)
    {
        Vector3 vertex = mVertices[indices[i - 1]];
        floorVertices[i * 8] = vertex.x;
        floorVertices[(i * 8) + 1] = vertex.y;
        floorVertices[(i * 8) + 2] = floorHeight;
        floorVertices[(i * 8) + 3] = 0.0f;
        floorVertices[(i * 8) + 4] = 1.0f;
        floorVertices[(i * 8) + 5] = 0.0f;
        floorVertices[(i * 8) + 6] = vertex.x;
        floorVertices[(i * 8) + 7] = vertex.y;

        ceilingVertices[i * 8] = vertex.x;
        ceilingVertices[(i * 8) + 1] = vertex.y;
        ceilingVertices[(i * 8) + 2] = ceilingHeight;
        ceilingVertices[(i * 8) + 3] = 0.0f;
        ceilingVertices[(i * 8) + 4] = -1.0f;
        ceilingVertices[(i * 8) + 5] = 0.0f;
        ceilingVertices[(i * 8) + 6] = vertex.x;
        ceilingVertices[(i * 8) + 7] = vertex.y;
        
        maxX = Max(maxX, vertex.x);
        minX = Min(minX, vertex.x);
        maxY = Max(maxY, vertex.y);
        minY = Min(minY, vertex.y);
    }
        
    MapFloor floor;
    floor.texture = getTextureEnum(mTextureMap[std::stoi(brokeLine[4])]);
    floor.VerticesFloor = new VertexArray(floorVertices.data(), floorVertices.size() / 8);
    if (floorHeight < ceilingHeight) floor.VerticesCeiling = new VertexArray(ceilingVertices.data(), ceilingVertices.size() / 8);
    else floor.VerticesCeiling = nullptr;
    
    mFloorList.push_back(floor);

    BoxCollider* collider = dynamic_cast<BoxCollider*>(mapActor->AddComponent(new BoxCollider(mapActor)));
    collider->getTransform()->setLocation(Vector3(maxX - ((Abs(maxX) + Abs(minX)) * 0.5f), maxY - ((Abs(maxY) + Abs(minY)) * 0.5f), floorVertices[2]));
    collider->getTransform()->setScale(Vector3(Abs(maxX) + Abs(minX), Abs(maxY) + Abs(minY), 0.001f));

    if (floorHeight < ceilingHeight)
    {
        collider = dynamic_cast<BoxCollider*>(mapActor->AddComponent(new BoxCollider(mapActor)));
        collider->getTransform()->setLocation(Vector3(maxX - ((Abs(maxX) + Abs(minX)) * 0.5f), maxY - ((Abs(maxY) + Abs(minY)) * 0.5f), ceilingVertices[2]));
        collider->getTransform()->setScale(Vector3(Abs(maxX) + Abs(minX), Abs(maxY) + Abs(minY), 0.001f));
    }
    
    floor.VerticesFloor = nullptr;
    floor.VerticesCeiling = nullptr;
    collider = nullptr;
}

void Map::ResolveActor(const std::string& pLine)
{
    // A string(name) Vector2(location) float(rotation) float(height) string(bonus)
    const auto brokeLine = BreakString(pLine, ' ');
    
    if (brokeLine[1] == "Door")
    {
        const auto brokePos = BreakString(brokeLine[2], ':');
        const Vector3 pos = Vector3(stof(brokePos[0])* MAP_SCALE, std::stof(brokePos[1])* MAP_SCALE, std::stof(brokeLine[4])) ;

        Actor* door = Scene::ActiveScene->AddActor(new Door());
        
        door->getTransform3D()->setLocation(pos);
        const float rotation = std::stof(brokeLine[2]) + 90.0f;
        door->getTransform3D()->addRotationZ(rotation);
    }
}
