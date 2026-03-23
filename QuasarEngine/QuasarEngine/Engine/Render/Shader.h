#pragma once
#include <string>
#include <fstream>

enum ShaderType
{
	VERTEX,
	FRAGMENT,
	TESSELLATION_CONTROL,
	TESSELLATION_EVAL,
	GEOMETRY,
};

class Shader
{
protected:
	std::string mCode;
	unsigned int mID;
	ShaderType mType;

public:
	static const std::string SHADER_PATH;
	int getID() const { return mID; }
	std::string& getCode() { return mCode; }

public:
	Shader();
	Shader(int _ID, std::string _file, ShaderType _shaderType);
	~Shader();

	void Load();
	void Load(std::string _filePath, ShaderType _shaderType);
	bool ValidateCompilation(int _ID);
};