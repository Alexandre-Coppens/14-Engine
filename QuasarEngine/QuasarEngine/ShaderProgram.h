#pragma once
#include <glew.h>

#include "Shader.h"
#include <vector>

#include "CommonLib.h"
#include "MathLib.h"

class ShaderProgram
{
private:
	unsigned int mID;

public:
	unsigned int getID() const { return mID; }

public:
	ShaderProgram();
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