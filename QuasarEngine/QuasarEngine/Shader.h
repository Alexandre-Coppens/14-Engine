#pragma once
#include <string>
#include <fstream>

enum ShaderType
{
	VERTEX,
	FRAGMENT
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

	void Load(std::string _fileName, ShaderType _shaderType);
};