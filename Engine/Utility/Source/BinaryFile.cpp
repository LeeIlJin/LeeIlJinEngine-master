#include "BinaryFile.h"

#include "../Math/MyMath.h"
#include <assert.h>

//////////////////////////////////////////////////////////////////////////

using namespace std;

BinaryWriter::BinaryWriter()
	: fileHandle(NULL), size(0)
{

}

BinaryWriter::~BinaryWriter()
{

}

void BinaryWriter::Open(wstring filePath, UINT openOption)
{
	assert(filePath.length() > 0);
	fileHandle = CreateFile
	(
		filePath.c_str()
		, GENERIC_WRITE
		, 0
		, NULL
		, openOption
		, FILE_ATTRIBUTE_NORMAL
		, NULL
	);


	bool isChecked = fileHandle != INVALID_HANDLE_VALUE;
	assert(isChecked);
}

void BinaryWriter::Close()
{
	if (fileHandle != NULL)
	{
		CloseHandle(fileHandle);
		fileHandle = NULL;
	}
}

void BinaryWriter::Bool(bool data)
{
	WriteFile(fileHandle, &data, sizeof(bool), &size, NULL);
}

void BinaryWriter::Word(WORD data)
{
	WriteFile(fileHandle, &data, sizeof(WORD), &size, NULL);
}

void BinaryWriter::Int(int data)
{
	WriteFile(fileHandle, &data, sizeof(int), &size, NULL);
}

void BinaryWriter::UInt(UINT data)
{
	WriteFile(fileHandle, &data, sizeof(UINT), &size, NULL);
}

void BinaryWriter::Float(float data)
{
	WriteFile(fileHandle, &data, sizeof(float), &size, NULL);
}

void BinaryWriter::Double(double data)
{
	WriteFile(fileHandle, &data, sizeof(double), &size, NULL);
}

void BinaryWriter::Vector2f(const Vector2& data)
{
	WriteFile(fileHandle, &data, sizeof(Vector2), &size, NULL);
}

void BinaryWriter::Vector3f(const Vector3& data)
{
	WriteFile(fileHandle, &data, sizeof(Vector3), &size, NULL);
}

void BinaryWriter::Vector4f(const Vector4& data)
{
	WriteFile(fileHandle, &data, sizeof(Vector4), &size, NULL);
}

void BinaryWriter::Color3f(const Color& data)
{
	WriteFile(fileHandle, &data, sizeof(Color) - 4, &size, NULL);
}

void BinaryWriter::Color4f(const Color& data)
{
	WriteFile(fileHandle, &data, sizeof(Color), &size, NULL);
}

void BinaryWriter::Matrixf(const Matrix& data)
{
	WriteFile(fileHandle, &data, sizeof(Matrix), &size, NULL);
}

void BinaryWriter::String(const string & data)
{
	UInt(data.size());

	const char* str = data.c_str();
	WriteFile(fileHandle, str, data.size(), &size, NULL);
}

void BinaryWriter::Byte(void * data, UINT dataSize)
{
	WriteFile(fileHandle, data, dataSize, &size, NULL);
}

//////////////////////////////////////////////////////////////////////////

BinaryReader::BinaryReader()
	: fileHandle(NULL), size(0)
{

}

BinaryReader::~BinaryReader()
{

}

void BinaryReader::Open(wstring filePath)
{
	assert(filePath.length() > 0);
	fileHandle = CreateFile
	(
		filePath.c_str()
		, GENERIC_READ
		, FILE_SHARE_READ
		, NULL
		, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL
		, NULL
	);


	bool isChecked = fileHandle != INVALID_HANDLE_VALUE;
	assert(isChecked);
}

void BinaryReader::Close()
{
	if (fileHandle != NULL)
	{
		CloseHandle(fileHandle);
		fileHandle = NULL;
	}
}

bool BinaryReader::Bool()
{
	bool temp = false;
	ReadFile(fileHandle, &temp, sizeof(bool), &size, NULL);

	return temp;
}

WORD BinaryReader::Word()
{
	WORD temp = 0;
	ReadFile(fileHandle, &temp, sizeof(WORD), &size, NULL);

	return temp;
}

int BinaryReader::Int()
{
	int temp = 0;
	ReadFile(fileHandle, &temp, sizeof(int), &size, NULL);

	return temp;
}

UINT BinaryReader::UInt()
{
	UINT temp = 0;
	ReadFile(fileHandle, &temp, sizeof(UINT), &size, NULL);

	return temp;
}

float BinaryReader::Float()
{
	float temp = 0.0f;
	ReadFile(fileHandle, &temp, sizeof(float), &size, NULL);

	return temp;
}

double BinaryReader::Double()
{
	double temp = 0.0f;
	ReadFile(fileHandle, &temp, sizeof(double), &size, NULL);

	return temp;
}

Vector2 BinaryReader::Vector2f()
{
	float x = Float();
	float y = Float();

	return Vector2(x, y);
}

Vector3 BinaryReader::Vector3f()
{
	float x = Float();
	float y = Float();
	float z = Float();

	return Vector3(x, y, z);
}

Vector4 BinaryReader::Vector4f()
{
	float x = Float();
	float y = Float();
	float z = Float();
	float w = Float();

	return Vector4(x, y, z, w);
}

Color BinaryReader::Color3f()
{
	float r = Float();
	float g = Float();
	float b = Float();

	return Color(r, g, b, 1.0f);
}

Color BinaryReader::Color4f()
{
	float r = Float();
	float g = Float();
	float b = Float();
	float a = Float();

	return Color(r, g, b, a);
}

Matrix BinaryReader::Matrixf()
{
	Matrix matrix;
	matrix.m_11 = Float();	matrix.m_12 = Float();	matrix.m_13 = Float();	matrix.m_14 = Float();
	matrix.m_21 = Float();	matrix.m_22 = Float();	matrix.m_23 = Float();	matrix.m_24 = Float();
	matrix.m_31 = Float();	matrix.m_32 = Float();	matrix.m_33 = Float();	matrix.m_34 = Float();
	matrix.m_41 = Float();	matrix.m_42 = Float();	matrix.m_43 = Float();	matrix.m_44 = Float();

	return matrix;
}

string BinaryReader::String()
{
	UINT size = Int();

	//char* temp = new char[size + 1];
	string str;
	ReadFile(fileHandle, &str, sizeof(char) * size, &this->size, NULL); //������ �б�
	//temp[size] = '\0';
	//string returnStr = temp;
	//SAFE_DELETE_ARRAY(temp);

	return str;
}

void BinaryReader::Byte(void ** data, UINT dataSize)
{
	ReadFile(fileHandle, *data, dataSize, &size, NULL);
}
