#pragma once
#include <glew.h>
#include <string>
#include <map>

#include "Engine/Utilitaries/CommonLib.h"
#include "Engine/Utilitaries/Log.h"
#include "Engine/Utilitaries/MathLib.h"

enum class UniformType
{
	UFloat,
	UInt,
	UVector2,
	UVector3,
	UVector4,
	UMatrix,
	UMatrixRow,
};

static inline std::map<std::string, UniformType> stringToUniformType{
	{"UFloat",		UniformType::UFloat},
	{"UInt",		UniformType::UInt},
	{"UVector2",	UniformType::UVector2},
	{"UVector3",	UniformType::UVector3},
	{"UVector4",    UniformType::UVector4},
	{"UMatrix",     UniformType::UMatrix},
	{"UMatrixRow",  UniformType::UMatrixRow},
};

struct Uniform
{
	std::string uName;
	Uniform(std::string _name): uName {_name} {}
	virtual ~Uniform() = default;
	virtual void SetUniform(const unsigned int _id) {Log::Info("Invalid Uniform Type!", LogLevel::Error);}
};

struct Uniform1f : public Uniform
{
	float uFloat;
	Uniform1f(std::string _name, float _float): Uniform(_name), uFloat {_float} {}
	~Uniform1f() override = default;
	void SetUniform(const unsigned int _id) override {glUniform1f(glGetUniformLocation(_id, uName.c_str()), uFloat);}
};

struct Uniform1i : public Uniform
{
	int uInt;
	Uniform1i(std::string _name, int _int): Uniform(_name), uInt {_int} {}
	~Uniform1i() override = default;
	void SetUniform(const unsigned int _id) override {glUniform1i(glGetUniformLocation(_id, uName.c_str()), uInt);}
};

struct Uniform2f : public Uniform
{
	Vector2 uVector2;
	Uniform2f(std::string _name, float _floatX, float _floatY): Uniform(_name), uVector2 {_floatX, _floatY} {}
	Uniform2f(std::string _name, Vector2 _vector2): Uniform(_name), uVector2 {_vector2} {}
	~Uniform2f() override = default;
	void SetUniform(const unsigned int _id) override {glUniform2f(glGetUniformLocation(_id, uName.c_str()), uVector2.x, uVector2.y);}
};

struct Uniform3f : public Uniform
{
	Vector3 uVector3;
	Uniform3f(std::string _name, float _floatX, float _floatY, float _floatZ): Uniform(_name), uVector3 {_floatX, _floatY, _floatZ} {}
	Uniform3f(std::string _name, Vector3 _vector3): Uniform(_name), uVector3 {_vector3} {}
	~Uniform3f() override = default;
	void SetUniform(const unsigned int _id) override {glUniform3f(glGetUniformLocation(_id, uName.c_str()), uVector3.x, uVector3.y, uVector3.z);}
};

struct Uniform4f : public Uniform
{
	Vector4 uVector4;
	Uniform4f(std::string _name, float _floatX, float _floatY, float _floatZ, float _floatW): Uniform(_name), uVector4 {_floatX, _floatY, _floatZ, _floatW} {}
	Uniform4f(std::string _name, Vector4 _vector4): Uniform(_name), uVector4 {_vector4} {}
	~Uniform4f() override = default;
	void SetUniform(const unsigned int _id) override {glUniform4f(glGetUniformLocation(_id, uName.c_str()), uVector4.x, uVector4.y, uVector4.z, uVector4.w);}
};

struct UniformMatrix4 : public Uniform
{
	Matrix4 uMatrix;
	UniformMatrix4(std::string _name, Matrix4 _matrix4): Uniform(_name), uMatrix {_matrix4} {}
	~UniformMatrix4() override = default;
	void SetUniform(const unsigned int _id) override {glUniform4fv(glGetUniformLocation(_id, uName.c_str()), GL_TRUE, GetAsFloatPtr(uMatrix));}
};

struct UniformMatrix4Row : public Uniform
{
	Matrix4Row uMatrixRow;
	UniformMatrix4Row(std::string _name, Matrix4Row _matrix4Row): Uniform(_name), uMatrixRow {_matrix4Row} {}
	~UniformMatrix4Row() override = default;
	void SetUniform(const unsigned int _id) override {glUniform4fv(glGetUniformLocation(_id, uName.c_str()), GL_TRUE, GetAsFloatPtr(uMatrixRow));}
};