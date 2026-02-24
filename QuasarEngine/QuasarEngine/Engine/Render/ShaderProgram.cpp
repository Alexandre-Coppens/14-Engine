#include "ShaderProgram.h"

#include "Engine/Utilitaries/MathLib.h"

ShaderProgram::ShaderProgram()
{
	mID = 0;
	mDrawOptions = 0;
}

ShaderProgram::ShaderProgram(int _options)
{
	mID = 0;
	mDrawOptions = _options;
}

void ShaderProgram::Unload() 
{
	glDeleteProgram(mID);
}

void ShaderProgram::Compose(std::vector<Shader*> _shaders)
{
	mID = glCreateProgram();
	for (int i = 0; i < _shaders.size(); i++)
	{
		glAttachShader(mID, _shaders[i]->getID());
	}
	glLinkProgram(mID);
	Use();
}

void ShaderProgram::Use()
{
	glUseProgram(mID); 
}

void ShaderProgram::SetFloat(const GLchar* name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(mID, name), value);
}
void ShaderProgram::SetInteger(const GLchar* name, GLint value)
{
	glUniform1i(glGetUniformLocation(mID, name), value);
}
void ShaderProgram::SetVector2f(const GLchar* name, GLfloat x, GLfloat y)
{
	glUniform2f(glGetUniformLocation(mID, name), x, y);
}
void ShaderProgram::SetVector2f(const GLchar* name, const Vector2& value)
{
	glUniform2f(glGetUniformLocation(mID, name), value.x, value.y);
}
void ShaderProgram::SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(glGetUniformLocation(mID, name), x, y, z);
}
void ShaderProgram::SetVector3f(const GLchar* name, const Vector3& value)
{
	glUniform3f(glGetUniformLocation(mID, name), value.x, value.y, value.z);
}
void ShaderProgram::SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(glGetUniformLocation(mID, name), x, y, z, w);
}
void ShaderProgram::SetVector4f(const GLchar* name, const Vector4& value)
{
	glUniform4f(glGetUniformLocation(mID, name), value.x, value.y, value.z, value.w);
}
void ShaderProgram::SetMatrix4(const GLchar* name, const Matrix4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(mID, name), 1, GL_TRUE, GetAsFloatPtr(matrix));
}
void ShaderProgram::SetMatrix4Row(const GLchar* name, const Matrix4Row& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(mID, name), 1, GL_TRUE, GetAsFloatPtr(matrix));
}
