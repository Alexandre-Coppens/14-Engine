#include "Material.h"

#include <functional>

#include "Uniform.h"
#include "Engine/Utilitaries/Assets.h"
#include "Engine/Utilitaries/Log.h"

Material::Material(ShaderProgram* _shaderProgram, DrawOption _drawOption = DrawOption::NONE):
    mShaderProgram(_shaderProgram),
    mTextures(mShaderProgram->getTextures()),
    mDrawOption(_drawOption)
{
    std::vector<Uniform*> shaderUniforms = mShaderProgram->getUniforms();
    for (Uniform* uniform : shaderUniforms)
    {
        switch(uniform->uType) {
        case UniformType::UFloat:
            mUniforms.push_back(new Uniform1f(uniform->uName, static_cast<Uniform1f*>(uniform)->uFloat));
            break;
        case UniformType::UInt:
            mUniforms.push_back(new Uniform1i(uniform->uName, static_cast<Uniform1i*>(uniform)->uInt));
            break;
        case UniformType::UVector2:
            mUniforms.push_back(new Uniform2f(uniform->uName, static_cast<Uniform2f*>(uniform)->uVector2));
            break;
        case UniformType::UVector3:
            mUniforms.push_back(new Uniform3f(uniform->uName, static_cast<Uniform3f*>(uniform)->uVector3));
            break;
        case UniformType::UVector4:
            mUniforms.push_back(new Uniform4f(uniform->uName, static_cast<Uniform4f*>(uniform)->uVector4));
            break;
        case UniformType::UMatrix:
            mUniforms.push_back(new UniformMatrix4(uniform->uName, static_cast<UniformMatrix4*>(uniform)->uMatrix));
            break;
        case UniformType::UMatrixRow:
            mUniforms.push_back(new UniformMatrix4Row(uniform->uName, static_cast<UniformMatrix4Row*>(uniform)->uMatrixRow));
            break;
        }
    }
}

Material::~Material() = default;

void Material::Unload()
{
    mShaderProgram = nullptr;
    for (Uniform* uniform : mUniforms)
    {
        delete uniform;
        uniform = nullptr;
    }
    mUniforms.clear();
    for (TextureBinding texture : mTextures)
    {
        texture.texture = Assets::GetTexture(PNG_NullTexture);
    }
}

//Automatically bind Uniforms and Textures
void Material::Bind()
{
    for (int i = 0; i < static_cast<int>(getUniforms().size()); i++)
    {
        getUniforms()[i]->SetUniform(getShaderProgram()->getID()); 
    }
		
    for (int i = 0; i < Min(static_cast<int>(getTextures()->size()), 32); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        if (getTextures()->at(i).texture == nullptr) continue;
        getTextures()->at(i).texture->SetActive();
    }
}

Uniform* Material::GetUniform(const std::string* _name)
{
    for (int i = 0; i < static_cast<int>(mUniforms.size()); ++i)
    {
        if (mUniforms[i]->uName == *_name) return mUniforms[i];
    }
    Log::Info("Uniform " + *_name + " not found", LogLevel::Warning);
    return nullptr;
}


void Material::SetFloat(const std::string* _name, GLfloat value)
{
    Uniform* parent = GetUniform(_name);
    Uniform1f* uniform = dynamic_cast<Uniform1f*>(parent);
    parent = nullptr;
    if (uniform != nullptr)
        uniform->uFloat = value;
    uniform = nullptr;
}
void Material::SetInteger(const std::string* _name, GLint value)
{
    Uniform* parent = GetUniform(_name);
    Uniform1i* uniform = dynamic_cast<Uniform1i*>(parent);
    parent = nullptr;
    if (uniform != nullptr)
        uniform->uInt = value;
    uniform = nullptr;
}
void Material::SetVector2f(const std::string* _name, GLfloat x, GLfloat y)
{
    Uniform* parent = GetUniform(_name);
    Uniform2f* uniform = dynamic_cast<Uniform2f*>(parent);
    parent = nullptr;
    if (uniform != nullptr)
        uniform->uVector2 = Vector2{x, y};
    uniform = nullptr;
}
void Material::SetVector2f(const std::string* _name, const Vector2& value)
{
    Uniform* parent = GetUniform(_name);
    Uniform2f* uniform = dynamic_cast<Uniform2f*>(parent);
    parent = nullptr;
    if (uniform != nullptr)
        uniform->uVector2 = value;
    uniform = nullptr;
}
void Material::SetVector3f(const std::string* _name, GLfloat x, GLfloat y, GLfloat z)
{
    Uniform* parent = GetUniform(_name);
    Uniform3f* uniform = dynamic_cast<Uniform3f*>(parent);
    parent = nullptr;
    if (uniform != nullptr)
        uniform->uVector3 = Vector3{x, y, z};
    uniform = nullptr;
}
void Material::SetVector3f(const std::string* _name, const Vector3& value)
{
    Uniform* parent = GetUniform(_name);
    Uniform3f* uniform = dynamic_cast<Uniform3f*>(parent);
    parent = nullptr;
    if (uniform != nullptr)
        uniform->uVector3 = value;
    uniform = nullptr;
}
void Material::SetVector4f(const std::string* _name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    Uniform* parent = GetUniform(_name);
    Uniform4f* uniform = dynamic_cast<Uniform4f*>(parent);
    parent = nullptr;
    if (uniform != nullptr)
        uniform->uVector4 = Vector4{x, y, z, w};
    uniform = nullptr;
}
void Material::SetVector4f(const std::string* _name, const Vector4& value)
{
    Uniform* parent = GetUniform(_name);
    Uniform4f* uniform = dynamic_cast<Uniform4f*>(parent);
    parent = nullptr;
    if (uniform != nullptr)
        uniform->uVector4 = value;
    uniform = nullptr;
}
void Material::SetMatrix4(const std::string* _name, const Matrix4& _matrix)
{
    Uniform* parent = GetUniform(_name);
    UniformMatrix4* uniform = dynamic_cast<UniformMatrix4*>(parent);
    parent = nullptr;
    if (uniform != nullptr)
        uniform->uMatrix = _matrix;
    uniform = nullptr;
}
void Material::SetMatrix4Row(const std::string* _name, const Matrix4Row& _matrix)
{
    Uniform* parent = GetUniform(_name);
    UniformMatrix4Row* uniform = dynamic_cast<UniformMatrix4Row*>(parent);
    parent = nullptr;
    if (uniform != nullptr)
        uniform->uMatrixRow = _matrix;
    uniform = nullptr;
}

void Material::SetTexture(std::string _name, Texture* _texture)
{
    for (int i = 0; i < static_cast<int>(mTextures.size()); i++)
    {
        if (_name == mTextures[i].name)
        {
            mTextures[i].texture = _texture;
            return;
        }
    }
    Log::Info(" Shader:: No Texture named: " + _name + " found.", LogLevel::Warning);
}
