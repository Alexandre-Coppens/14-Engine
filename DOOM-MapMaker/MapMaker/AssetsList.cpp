#include <iostream>
#include <filesystem>
#include "AssetsList.h"

Texture2D AssetList::textureTemp;
Music AssetList::music;
AssetList* AssetList::instance = nullptr;
map<string, Font> AssetList::textFont;
map<string, Texture2D> AssetList:: SpriteList;
map<string, Sound> AssetList:: soundList;

AssetList::AssetList() {
    if (SpriteList.size() > 0) return;
    LoadRessources();
}

AssetList::~AssetList(){
}

void AssetList::LoadRessources(){
    string path = "resources";
    const std::filesystem::path resourcePath{ path };

    for (const auto& entry : std::filesystem::directory_iterator(resourcePath)) {

        const auto filenameStr = entry.path().filename().string();

        if (entry.is_directory()) {
            std::cout << "dir:  " << filenameStr << '\n';
            if (filenameStr == "fonts") LoadFontFolder(path + "/" + filenameStr);
            if (filenameStr == "sprites") LoadTextureFolder(path + "/" + filenameStr);
        }
        else if (entry.is_regular_file()) {
            std::cout << "file: " << filenameStr << '\n';
        }
    }
}

void AssetList::LoadFontFolder(string path) {
    const std::filesystem::path resourcePath{ path };

    for (const auto& entry : std::filesystem::directory_iterator(resourcePath)) {
        if (!entry.is_regular_file()) {
            std::cout << "??    " << entry.path().filename().string() << '\n';
            continue;
        }

        const auto filenameStr = entry.path().filename().string();
        const auto fileStemStr = entry.path().stem().string();
        const auto fileExtensionStr = entry.path().extension().string();

        std::cout << "      -file: " << filenameStr << '\n';
        if (fileExtensionStr == ".png") {
            AssetList::textFont[fileStemStr] = LoadFont((path + "/" + filenameStr).c_str());
        }
        else {
            std::cout << "ResourceLoader: File skipped, other files than png are not supported.          " << '\n';
        }
    }
}

void AssetList::LoadTextureFolder(string path) {
    const std::filesystem::path resourcePath{ path };

    for (const auto& entry : std::filesystem::directory_iterator(resourcePath)) {
        if (!entry.is_regular_file()) {
            std::cout << "??    " << entry.path().filename().string() << '\n';
            continue;
        }

        const auto filenameStr = entry.path().filename().string();
        const auto fileStemStr = entry.path().stem().string();
        const auto fileExtensionStr = entry.path().extension().string();

        std::cout << "      -file: " << filenameStr << '\n';
        if (fileExtensionStr == ".png") {
            LoadTexture2D(fileStemStr, path + "/" + filenameStr);
        }
        else {
            std::cout << "ResourceLoader: File skipped, other files than png are not supported.          " << '\n';
        }
    }
}

string AssetList::GetNameAtPosition(int position) {
    int i = 0;
    for (auto s : SpriteList) {
        if (i == position) return s.first;
        i++;
    }
    return "Unknown";
}

void AssetList::LoadTexture2D(string name, string link) {
    Image temp = LoadImage(link.c_str());
    textureTemp = LoadTextureFromImage(temp);
    SpriteList[name] = textureTemp;
    UnloadImage(temp);
}

AssetList* AssetList::GetInstance() {
    if (instance == nullptr) {
        instance = new AssetList();
    }
    return instance;
}