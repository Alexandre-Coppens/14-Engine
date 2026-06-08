#pragma once
#include "ShaderProgram.h"

struct Uniform;

class Material
{
private:
    ShaderProgram* mShaderProgram;

    std::vector<Uniform*> mUniforms;
    std::vector<TextureBinding> mTextures;
    DrawOption mDrawOption;

public:
    ShaderProgram* getShaderProgram() const { return mShaderProgram; }
    std::vector<Uniform*> getUniforms() { return mUniforms; }
    std::vector<TextureBinding>* getTextures() { return &mTextures; }
    DrawOption getDrawOption() { return mDrawOption; }

    void setDrawOption(DrawOption _option) { mDrawOption = _option; }
    
private:
    
public:
    Material(ShaderProgram* _shaderProgram, DrawOption _drawOption);
    ~Material();

    void Unload();
    void Bind();
    
    Uniform* GetUniform(const std::string _name);

    void SetFloat		(const std::string _name, GLfloat _f);
    void SetInteger		(const std::string _name, GLint	_i);
    void SetVector2f	(const std::string _name, GLfloat _x, GLfloat _y);
    void SetVector2f	(const std::string _name, const Vector2&);
    void SetVector3f	(const std::string _name, GLfloat _x, GLfloat _y, GLfloat _z);
    void SetVector3f	(const std::string _name, const Vector3&);
    void SetVector4f	(const std::string _name, GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _w);
    void SetVector4f	(const std::string _name, const Vector4&);
    void SetMatrix4		(const std::string _name, const Matrix4& _matrix);
    void SetMatrix4Row	(const std::string _name, const Matrix4Row& _matrix);
    void SetTexture		(std::string _name, Texture* _texture);
};
