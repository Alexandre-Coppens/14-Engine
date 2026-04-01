#pragma once
#include <glew.h>

#include "Engine/Utilitaries/CommonLib.h"

#include "Engine/Render/Shader.h"
#include <vector>

enum class DrawOption
{
	COLOR,
	NULL_SHADER,
	TEXTURE,
	WIREFRAME,
	TESSELATION,
	GEOMETRY,
	DEBUG
};

class ShaderProgram
{
private:
	unsigned int mID;
	DrawOption mDrawOptions;

public:
	unsigned int getID() const { return mID; }
	DrawOption getDrawOptions() const { return mDrawOptions; }

public:
	ShaderProgram(DrawOption _option);
	~ShaderProgram() = default;
	void Unload();
	void Compose(std::vector<Shader*> _shaders);

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