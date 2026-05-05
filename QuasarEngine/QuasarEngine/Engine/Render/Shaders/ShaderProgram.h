#pragma once
#include <glew.h>

#include "Engine/Utilitaries/CommonLib.h"

#include "Engine/Render/Shaders/Shader.h"
#include <vector>

#include "Engine/Texture.h"
#include "Engine/Render/Shaders/Uniform.h"

struct Uniform;

enum class DrawOption
{
	NONE,
	COLOR,
	NULL_SHADER,
	TEXTURE,
	WIREFRAME,
	TESSELATION,
	GEOMETRY,
	INSTANCED,
	DEBUG
};

struct TextureBinding
{
	std::string name;
	Texture* texture = nullptr;
};

class ShaderProgram
{
private:
	unsigned int mID;
	std::vector<Uniform*> uniforms;
	std::vector<TextureBinding> textures;

public:
	unsigned int getID() const { return mID; }
	std::vector<Uniform*> getUniforms() { return uniforms; }
	std::vector<TextureBinding> getTextures() { return textures; }

	void setUniformList(const std::vector<Uniform*> _uniforms) {uniforms = _uniforms; }
	void setTextures(const std::vector<std::string> _texturesNames){
		for (TextureBinding bind : textures) bind.texture = nullptr;
		textures.clear();
		for (int i = 0; i < static_cast<int>(_texturesNames.size()); i++){
			textures.push_back(TextureBinding{_texturesNames[i].c_str(), nullptr});
		}
	}
	
public:
	ShaderProgram();
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