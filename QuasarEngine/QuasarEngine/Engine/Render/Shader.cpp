#include "Shader.h"
#include "Engine/Utilitaries/Log.h"
#include <glew.h>
#include <vector>

#include "Engine/Utilitaries/DebugMemoryLeakCatcher.h"

const std::string Shader::SHADER_PATH = "Resources/Shaders/";

Shader::Shader():
	mID(0), mCode(""), mType(ShaderType::VERTEX)
{
	DEBUGAddClass("Shader");
}

Shader::Shader(int _ID, std::string _file, ShaderType _shaderType):
	mID(_ID), mCode(_file), mType(_shaderType)
{
	DEBUGAddClass("Shader");
	Load(_file, _shaderType);
}

Shader::~Shader()
{
	DEBUGRemoveClass("Shader");
}

void Shader::Load(std::string _filePath, ShaderType _shaderType)
{
	mType = _shaderType;
	std::ifstream myFile;
	myFile.open(_filePath);
	if (myFile.fail())
	{
		Log::Error(LogType::Video, "Error - failed to open " + _filePath);
	}

	std::string fileText = "";
	std::string line = "";
	while (getline(myFile, line))
	{
		if (line.empty()) continue;
		fileText += line + '\n';
	}

	myFile.close();
	mCode = fileText;

	if(mCode == "") Log::Error(LogType::Video, "Error - " + _filePath + " has not been read or is empty!");


	switch (mType)
	{
	case ShaderType::VERTEX:
		mID = glCreateShader(GL_VERTEX_SHADER);
		break;

	case ShaderType::TESSELLATION_CONTROL:
		mID = glCreateShader(GL_TESS_CONTROL_SHADER);
		break;

	case ShaderType::TESSELLATION_EVAL:
		mID = glCreateShader(GL_TESS_EVALUATION_SHADER);
		break;

	case ShaderType::GEOMETRY:
		mID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
		
	case ShaderType::FRAGMENT:
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
	
	if (ValidateCompilation(mID))
	{
		Log::Info("Shader - " + _filePath  + " successfully loaded with ID: " + std::to_string(mID) );
	}
}

bool Shader::ValidateCompilation(int _ID)
{
	//Check if there was compile error
	int success;
	glGetShaderiv(_ID, GL_COMPILE_STATUS, &success);

	bool compileError = (success == GL_FALSE ? true : false);

	//Print compile error info
	if (compileError)
	{
		GLint infoLength;
		glGetShaderiv(_ID, GL_INFO_LOG_LENGTH, &infoLength);

		GLchar* info = new GLchar[infoLength + 1];
		glGetShaderInfoLog(_ID, infoLength, NULL, info);

		Log::Error(LogType::Render, std::string("SHADER COMPILE ERROR: ") + info);

		delete[] info; // Don't forget to free memory!
	}

	//Return true if no compile error and false otherwise
	return !compileError;
}