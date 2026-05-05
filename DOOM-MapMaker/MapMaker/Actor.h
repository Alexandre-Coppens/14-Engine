#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "raymath.h"
#include "AssetsList.h"

using std::string;
using std::vector;
using std::map;

class Actor {
private:
protected:
    static map<string, Actor*> ActorList;
    static vector<vector<Actor*>> ActorsByLayer;
    Rectangle rect;
public:
    bool enabled        { true };
    bool needToDestroy  { false };
    
    bool hovered    { false };
    bool clicked    { false };

    string name         { "" };
    
    Vector2 anchor      { 0.0f, 0.0f };
    Vector2 position    { 0,0 };
    Vector2 size        { 0,0 };
    
    short layer         { 0 };
    Texture2D* sprite   { nullptr };
    Color color         { WHITE };

private:
protected:
    void CreateRect();

public:
    Actor(bool _enabled, string _name, Vector2 _anchor, Vector2 _pos, Vector2 _size, Texture2D* _sprite, short _layer);
    virtual ~Actor();
    
    virtual void Update() = 0;
    virtual void Draw(Vector2 _scroll) = 0;
    void Destroy(); 
    
    bool IsCursorInBounds();
    virtual void Clicked() = 0;
    
    static Actor* GetActorWithName(string _name);
    static vector<Actor*> GetAllActors();
    static vector<vector<Actor*>>* GetAllActorsLayered();
    
    static void DestroyActorList();
};