#pragma once

#include <Windows.h>
#include <string>

class Vector2;
class Vector3;
class Vector4;
class Color;
class Matrix;

class BinaryWriter
{
public:
	BinaryWriter();
	~BinaryWriter();

	void Open(std::wstring filePath, UINT openOption = CREATE_ALWAYS);
	void Close();

	void Bool(bool data);
	void Word(WORD data);
	void Int(int data);
	void UInt(UINT data);
	void Float(float data);
	void Double(double data);

	void Vector2f(const Vector2& data);
	void Vector3f(const Vector3& data);
	void Vector4f(const Vector4& data);
	void Color3f(const Color& data);
	void Color4f(const Color& data);
	void Matrixf(const Matrix& data);

	void String(const std::string& data);
	void Byte(void* data, UINT dataSize);

protected:
	HANDLE fileHandle;
	DWORD size;
};

//////////////////////////////////////////////////////////////////////////

class BinaryReader
{
public:
	BinaryReader();
	~BinaryReader();

	void Open(std::wstring filePath);
	void Close();

	bool Bool();
	WORD Word();
	int Int();
	UINT UInt();
	float Float();
	double Double();

	Vector2 Vector2f();
	Vector3 Vector3f();
	Vector4 Vector4f();
	Color Color3f();
	Color Color4f();
	Matrix Matrixf();

	std::string String();
	void Byte(void** data, UINT dataSize);

protected:
	HANDLE fileHandle;
	DWORD size;
};