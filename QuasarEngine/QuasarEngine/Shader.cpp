#include "Shader.h"
#include "Log.h"
#include <glew.h>

const std::string Shader::SHADER_PATH = "Ressources/Shaders/";

Shader::Shader():
	mID(0), mCode(""), mType(VERTEX)
{
}

Shader::Shader(int _ID, std::string _file, ShaderType _shaderType):
	mID(_ID), mCode(_file), mType(_shaderType)
{
}

Shader::~Shader()
{
}

void Shader::Load(std::string _fileName, ShaderType _shaderType)
{
	mType = _shaderType;
	std::ifstream myFile;
	myFile.open(SHADER_PATH + _fileName);
	if (myFile.fail())
	{
		Log::Error(LogType::Video, "Error - failed to open " + _fileName);
	}

	std::string fileText = "";
	std::string line = "";
	while (getline(myFile, line))
	{
		fileText += line + '\n';
	}

	myFile.close();
	mCode = fileText;

	switch (mType)
	{
	case VERTEX:
		mID = glCreateShader(GL_VERTEX_SHADER);
		break;

	case FRAGMENT:
		mID = glCreateShader(GL_FRAGMENT_SHADER);
		break;

	default:
		Log::Error(LogType::Render, "this shader type has not yet been implemented.");
		mID = glCreateShader(GL_VERTEX_SHADER);
		break;
	}

	const char* source = mCode.c_str();
	glShaderSource(mID, 1, &source, NULL);
	glCompileShader(mID);
}
