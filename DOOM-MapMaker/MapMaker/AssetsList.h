#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"

using std::string;
using std::vector;
using std::map;

class AssetList {
private:
    static Texture2D textureTemp;

public:
    static Music music;
    static map<string, Sound> soundList;
    static map<string, Font> textFont;
    static map<string, Texture2D> SpriteList;
    static AssetList* instance;

private:
    AssetList();
    ~AssetList();
    
    static void LoadFontFolder(string path);
    static void LoadSoundFolder(string path);
    static void LoadTextureFolder(string path);

    static void LoadTexture2D(string name, string link);

public:
    static void LoadRessources();
    static string GetNameAtPosition(int position);
    static AssetList* GetInstance();
};