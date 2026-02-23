#pragma once
#include <glew.h>

#include "Shader.h"
#include <vector>

#include "CommonLib.h"
#include "MathLib.h"

enum DrawOption
{
	NULL_SHADER = 1,
	TEXTURE = 2,
	COLOR = 4,
	DEBUG = 8
};

class ShaderProgram
{
private:
	unsigned int mID;
	int mDrawOptions; //Bitmask of DrawOption

public:
	unsigned int getID() const { return mID; }
	unsigned int getDrawOptions() const { return mDrawOptions; }

public:
	ShaderProgram();
	ShaderProgram(int _options);
	~ShaderProgram() = default;
	void Unload();
	void Compose(std::vector<Shader*> shaders);

	void Use();
	void SetFloat		(const GLchar* _name, GLfloat _f);
	void SetInteger		(const GLchar* _name, GLint	_i);
	void SetVector2f	(const GLchar* _name, GLfloat _x, GLfloat _y);
	void SetVector2f	(const GLchar* _name, const Vector2&);
	void SetVector3f	(const GLchar* _name, GLfloat _x, GLfloat _y, GLfloat _z);
	void SetVector3f	(const GLchar* _name, const Vector3&);
	void SetVector4f	(const GLchar* _name, GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _w);
	void SetVector4f	(const GLchar* _name, const Vector4&);
	void SetMatrix4		(const GLchar* _name, const Matrix4& matrix);
	void SetMatrix4Row	(const GLchar* _name, const Matrix4Row& matrix);
};