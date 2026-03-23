#include <iostream>
#include <fstream>

#include "Terrain.h"

using std::ofstream;
using std::ifstream;
using std::getline;
using std::to_string;
using std::cout;

map<int, string> Terrain::dictionary;
vector<Terrain::Wall> Terrain::wallList;
map<int, Vector2> Terrain::wallVertices;

int Terrain::verticesCount { 0 };
Vector2 Terrain::position{ 0,0 };
short Terrain::maxLayer{ 5 };

//
float Terrain::gridMeterInPixels;
int Terrain::gridSubdivision;
float Terrain::wallDrawSize;

//
Gizmo Terrain::nearGizmo {Vertex};
int Terrain::nearIndice{-1};

//void Terrain::SaveMap(string filename);
//void Terrain::LoadMap(string filename);

Terrain::Terrain() {
}

Terrain::~Terrain(){
}

void Terrain::Update()
{
}

int Terrain::AddNewVertex(Vector2 pos) {
	verticesCount++;
	wallVertices[verticesCount] = pos;
	return verticesCount;
}

void Terrain::AddNewWall(Wall wall)
{
	wallList.push_back(wall);
}

void Terrain::AddToDictionary(int index, string name) {
	if (AssetList::SpriteList.find(name) == AssetList::SpriteList.end()) {
		dictionary[index] = "Unknown";
	}
	else {
		dictionary[index] = name;
	}
}

int Terrain::CheckInDictionary(string name) {
	for (auto d : dictionary) {
		if (name == d.second) {
			return d.first;
		}
	}
	int newInt = (int)dictionary.size();
	dictionary[newInt] = name;
	return newInt;
}

void Terrain::ComputeWall(Wall* wall)
{
	wall->rotation = Vector2LineAngle(Terrain::wallVertices[wall->start], Terrain::wallVertices[wall->end]) * RAD2DEG;
	wall->computed = true;
}

void Terrain::ISCursorOnSomething(Vector2 position)
{
	for (auto v : wallVertices)
	{
		if (Vector2Distance(position, v.second) <= 5)
		{
			nearGizmo = Vertex;
			nearIndice = v.first;
			return;
		}
	}
	for (int i = 0; i < wallList.size(); i++)
	{
		Wall wall = wallList[i];
		if (CheckCollisionPointLine(position, wallVertices[wall.start], wallVertices[wall.end], ceil(wallDrawSize)))
		{
			nearGizmo = Edge;
			nearIndice = i;
			return;
		}
	}
	nearIndice = -1;
}

void Terrain::SaveMap(string fileName){
	bool checkIfSure = true;
	while (checkIfSure) {
		BeginDrawing();
		DrawText("Do you want to SAVE ?.", 150, 300, 20, RED);
		DrawText("Enter. Yes   -   Del. No", 150, 330, 20, RED);
		EndDrawing();
		if (IsKeyPressed(KEY_ENTER)) checkIfSure = false;
		else if (IsKeyPressed(KEY_BACKSPACE)) return;
	}

	ofstream saveFile;
	saveFile.open(fileName + ".txt");
	if (saveFile.is_open()) {
		for (auto d : dictionary) {
			saveFile << "D " + to_string(d.first) + ":" + d.second + "\n";
		}
		for (auto vertice : wallVertices) {
			saveFile << "V " + to_string(vertice.first)  + " " +
					to_string(vertice.second.x) + ":" + to_string(vertice.second.y) + "\n";
		}
		for (auto wall : wallList) {
			saveFile << "W " + 
					to_string(wall.start)  + " " +
					to_string(wall.end)  + " " +
					to_string(wall.dictionaryTexture)  + "\n";
		}
		saveFile.close();
	}
	else {
		cout << "Could not load " + fileName + ".txt ." + "\n";
	}
}

void Terrain::LoadMap(string fileName){
	bool checkIfSure = true;
	while (checkIfSure) {
		BeginDrawing();
		DrawText("Do you want to LOAD ?.", 150, 300, 20, RED);
		DrawText("Enter. Yes   -   Del. No", 150, 330, 20, RED);
		EndDrawing();
		if (IsKeyPressed(KEY_ENTER)) checkIfSure = false;
		else if (IsKeyPressed(KEY_BACKSPACE)) return;
	}

	dictionary.clear();
	wallVertices.clear();
	wallList.clear();

	string line;
	ifstream loadFile(fileName + ".txt");

	if (loadFile.is_open()) {
		while (getline(loadFile, line) ){
			if (line[0] == 'D') {	// D int(iterator) string(textureName)
				vector<string> dict = BreakString(line, ' ');
				dict = BreakString(dict[1], ':');
				AddToDictionary(stoi(dict[0]), dict[1]);
			}
			if (line[0] == 'V') {	// V int(iterator) vec2(location)
				vector<string> vertex = BreakString(line, ' ');
				vector<string> locString = BreakString(vertex[2], ':');
				Vector2 posV  { stof(locString[0]), stof(locString[1]) };
				wallVertices[stoi(vertex[1])] = posV;
			}
			if (line[0] == 'W') {	// W int(start) int(end) int(dictionaryPointer)
				vector<string> wallString = BreakString(line, ' ');
				Wall wall;
				wall.start = stoi(wallString[1]);
				wall.end = stoi(wallString[2]);
				wall.dictionaryTexture = stoi(wallString[3]);
				wallList.push_back(wall);
			}
		}
		loadFile.close();
	}
	else {
		cout << "Could not load " + fileName + ".txt ." + "\n";
	}
}

vector<string> Terrain::BreakString(string str, char breacker) {
	vector<string> r;
	string word;
	for(int i = 0; i < str.size(); i++)
	{
		if (str[i] == breacker) {
			r.push_back(word);
			word.clear();
		}
		else{
			word += str[i];
		}
	}
	r.push_back(word);
	return r;
}