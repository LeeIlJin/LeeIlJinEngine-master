#include <Windows.h>
#include <assert.h>
#include <math.h>
//
#include "Matrix.h"

//
#include "Quaternion.h"
#include "Plane.h"

#include <d3dx9math.h>

///////////////////////////////////////////////////////////////////////////////

const Matrix Matrix::Identity = Matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

///////////////////////////////////////////////////////////////////////////////

Matrix::Matrix(bool identity) noexcept
{
	if(identity == true)
		*this = Matrix::Identity;
}

Matrix::Matrix(const Vector3 & right, const Vector3 & up, const Vector3 & forward, const Vector3 & position, float size) noexcept
	:m_right(right), m_up(up), m_forward(forward), m_position(position), m_44(1.0f)
{
	m_right *= size;
	m_up *= size;
	m_forward *= size;
}

Matrix::Matrix(const Vector3 & right, const Vector3 & up, const Vector3 & forward, const Vector3 & position, const Vector3 & size) noexcept
	:m_right(right), m_up(up), m_forward(forward), m_position(position), m_44(1.0f)
{
	m_right *= size.x;
	m_up *= size.y;
	m_forward *= size.z;
}

Matrix::Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44) noexcept
	:m_11(m11), m_12(m12), m_13(m13), m_14(m14)
	, m_21(m21), m_22(m22), m_23(m23), m_24(m24)
	, m_31(m31), m_32(m32), m_33(m33), m_34(m34)
	, m_41(m41), m_42(m42), m_43(m43), m_44(m44)
{
	//	Empty
}

//	Float 배열(16) 으로 생성
Matrix::Matrix(float * arr_16) noexcept
{
	memcpy(data, arr_16, sizeof(arr_16));
}

Matrix::Matrix(const Matrix & other) noexcept
{
	memcpy(this, &other, sizeof(other));
}

Matrix::Matrix(Matrix && other) noexcept
{
	memcpy(this, &other, sizeof(other));
	ZeroMemory(&other, sizeof(other));
}

///////////////////////////////////////////////////////////////////////////////

Matrix::operator float*() const noexcept
{
	return (float*)m;
}

///////////////////////////////////////////////////////////////////////////////

Matrix Matrix::operator+(const Matrix & other) const noexcept
{
	Matrix result;
	for (unsigned int i = 0; i < 16; i++)
		result.data[i] = data[i] + other.data[i];

	return result;
}

Matrix Matrix::operator+(const float & other) const noexcept
{
	Matrix result;
	for (unsigned int i = 0; i < 16; i++)
		result.data[i] = data[i] + other;

	return result;
}

Matrix Matrix::operator-(const Matrix & other) const noexcept
{
	Matrix result;
	for (unsigned int i = 0; i < 16; i++)
		result.data[i] = data[i] - other.data[i];

	return result;
}

Matrix Matrix::operator-(const float & other) const noexcept
{
	Matrix result;
	for (unsigned int i = 0; i < 16; i++)
		result.data[i] = data[i] - other;

	return result;
}

Matrix Matrix::operator*(const Matrix & other) const noexcept
{
	Matrix result;
	result.m_11 = this->m_11 * other.m_11 + this->m_12 * other.m_21 + this->m_13 * other.m_31 + this->m_14 * other.m_41;
	result.m_12 = this->m_11 * other.m_12 + this->m_12 * other.m_22 + this->m_13 * other.m_32 + this->m_14 * other.m_42;
	result.m_13 = this->m_11 * other.m_13 + this->m_12 * other.m_23 + this->m_13 * other.m_33 + this->m_14 * other.m_43;
	result.m_14 = this->m_11 * other.m_14 + this->m_12 * other.m_24 + this->m_13 * other.m_34 + this->m_14 * other.m_44;
	result.m_21 = this->m_21 * other.m_11 + this->m_22 * other.m_21 + this->m_23 * other.m_31 + this->m_24 * other.m_41;
	result.m_22 = this->m_21 * other.m_12 + this->m_22 * other.m_22 + this->m_23 * other.m_32 + this->m_24 * other.m_42;
	result.m_23 = this->m_21 * other.m_13 + this->m_22 * other.m_23 + this->m_23 * other.m_33 + this->m_24 * other.m_43;
	result.m_24 = this->m_21 * other.m_14 + this->m_22 * other.m_24 + this->m_23 * other.m_34 + this->m_24 * other.m_44;
	result.m_31 = this->m_31 * other.m_11 + this->m_32 * other.m_21 + this->m_33 * other.m_31 + this->m_34 * other.m_41;
	result.m_32 = this->m_31 * other.m_12 + this->m_32 * other.m_22 + this->m_33 * other.m_32 + this->m_34 * other.m_42;
	result.m_33 = this->m_31 * other.m_13 + this->m_32 * other.m_23 + this->m_33 * other.m_33 + this->m_34 * other.m_43;
	result.m_34 = this->m_31 * other.m_14 + this->m_32 * other.m_24 + this->m_33 * other.m_34 + this->m_34 * other.m_44;
	result.m_41 = this->m_41 * other.m_11 + this->m_42 * other.m_21 + this->m_43 * other.m_31 + this->m_44 * other.m_41;
	result.m_42 = this->m_41 * other.m_12 + this->m_42 * other.m_22 + this->m_43 * other.m_32 + this->m_44 * other.m_42;
	result.m_43 = this->m_41 * other.m_13 + this->m_42 * other.m_23 + this->m_43 * other.m_33 + this->m_44 * other.m_43;
	result.m_44 = this->m_41 * other.m_14 + this->m_42 * other.m_24 + this->m_43 * other.m_34 + this->m_44 * other.m_44;

	return result;
}

Matrix Matrix::operator*(const float & other) const noexcept
{
	Matrix result;
	for (unsigned int i = 0; i < 16; i++)
		result.data[i] = data[i] * other;

	return result;
}

Matrix Matrix::operator/(const Matrix & other) const noexcept
{
	Matrix result;
	for (unsigned int i = 0; i < 16; i++)
		result.data[i] = data[i] / other.data[i];

	return result;
}

Matrix Matrix::operator/(const float & other) const noexcept
{
	Matrix result;
	for (unsigned int i = 0; i < 16; i++)
		result.data[i] = data[i] / other;

	return result;
}

void Matrix::operator+=(const Matrix & other) noexcept
{
	for (unsigned int i = 0; i < 16; i++)
		data[i] = data[i] + other.data[i];
}

void Matrix::operator+=(const float & other) noexcept
{
	for (unsigned int i = 0; i < 16; i++)
		data[i] = data[i] + other;
}

void Matrix::operator-=(const Matrix & other) noexcept
{
	for (unsigned int i = 0; i < 16; i++)
		data[i] = data[i] - other.data[i];
}

void Matrix::operator-=(const float & other) noexcept
{
	for (unsigned int i = 0; i < 16; i++)
		data[i] = data[i] - other;
}

void Matrix::operator*=(const Matrix & other) noexcept
{
	*this = *this * other;
}

void Matrix::operator*=(const float & other) noexcept
{
	for (unsigned int i = 0; i < 16; i++)
		data[i] = data[i] * other;
}

void Matrix::operator/=(const Matrix & other) noexcept
{
	for (unsigned int i = 0; i < 16; i++)
		data[i] = data[i] / other.data[i];
}

void Matrix::operator/=(const float & other) noexcept
{
	for (unsigned int i = 0; i < 16; i++)
		data[i] = data[i] / other;
}


///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//	매트릭스의 값들을 String으로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
std::string Matrix::ToString()
{
	std::string temp;
	char val[255];

	sprintf_s(val, "{ {m_11:%#0.4f ", m_11); temp += val;
	sprintf_s(val, "m_12:%#0.4f ", m_12); temp += val;
	sprintf_s(val, "m_13:%#0.4f ", m_13); temp += val;
	sprintf_s(val, "m_14:%#0.4f} ", m_14); temp += val;

	sprintf_s(val, "{m_21:%#0.4f ", m_21); temp += val;
	sprintf_s(val, "m_22:%#0.4f ", m_22); temp += val;
	sprintf_s(val, "m_23:%#0.4f ", m_23); temp += val;
	sprintf_s(val, "m_24:%#0.4f} ", m_24); temp += val;

	sprintf_s(val, "{m_31:%#0.4f ", m_31); temp += val;
	sprintf_s(val, "m_32:%#0.4f ", m_32); temp += val;
	sprintf_s(val, "m_33:%#0.4f ", m_33); temp += val;
	sprintf_s(val, "m_34:%#0.4f} ", m_34); temp += val;

	sprintf_s(val, "{m_41:%#0.4f ", m_41); temp += val;
	sprintf_s(val, "m_42:%#0.4f ", m_42); temp += val;
	sprintf_s(val, "m_43:%#0.4f ", m_43); temp += val;
	sprintf_s(val, "m_44:%#0.4f} }", m_44); temp += val;

	return temp;
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스의 값들을 Wstring으로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
std::wstring Matrix::ToStringW()
{
	std::wstring temp;
	wchar_t val[255];

	wprintf_s(val, L"{ {M_11:%#0.4f ", m_11); temp += val;
	wprintf_s(val, L"M_12:%#0.4f ", m_12); temp += val;
	wprintf_s(val, L"M_13:%#0.4f ", m_13); temp += val;
	wprintf_s(val, L"M_14:%#0.4f} ", m_14); temp += val;

	wprintf_s(val, L"{M_21:%#0.4f ", m_21); temp += val;
	wprintf_s(val, L"M_22:%#0.4f ", m_22); temp += val;
	wprintf_s(val, L"M_23:%#0.4f ", m_23); temp += val;
	wprintf_s(val, L"M_24:%#0.4f} ", m_24); temp += val;

	wprintf_s(val, L"{M_31:%#0.4f ", m_31); temp += val;
	wprintf_s(val, L"M_32:%#0.4f ", m_32); temp += val;
	wprintf_s(val, L"M_33:%#0.4f ", m_33); temp += val;
	wprintf_s(val, L"M_34:%#0.4f} ", m_34); temp += val;

	wprintf_s(val, L"{M_41:%#0.4f ", m_41); temp += val;
	wprintf_s(val, L"M_42:%#0.4f ", m_42); temp += val;
	wprintf_s(val, L"M_43:%#0.4f ", m_43); temp += val;
	wprintf_s(val, L"M_44:%#0.4f} }", m_44); temp += val;

	return temp;
}

///////////////////////////////////////////////////////////////////////////////
//	Matrix 를 D3DXMATRIX 로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
D3DXMATRIX Matrix::ToD3DXMATRIX()
{
	return D3DXMATRIX(
		m_11, m_12, m_13, m_14,
		m_21, m_22, m_23, m_24,
		m_31, m_32, m_33, m_34,
		m_41, m_42, m_43, m_44
	);
}

///////////////////////////////////////////////////////////////////////////////
//	행렬식
///////////////////////////////////////////////////////////////////////////////
float Matrix::Determinant()
{
	float f1 = (m_33 * m_44 - m_34 * m_43);
	float f2 = (m_32 * m_44 - m_34 * m_42);
	float f3 = (m_32 * m_43 - m_33 * m_42);
	float f4 = (m_31 * m_44 - m_34 * m_41);
	float f5 = (m_31 * m_43 - m_33 * m_41);
	float f6 = (m_31 * m_42 - m_32 * m_41);

	float result =
		(m_11 * (m_22 * f1 - m_23 * f2 + m_24 * f3) -
		m_12 * (m_21 * f1 - m_23 * f4 + m_24 * f5) +
			m_13 * (m_21 * f2 - m_22 * f4 + m_24 * f6) -
			m_14 * (m_21 * f3 - m_22 * f5 + m_23 * f6));

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스의 (기하학적)크기를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 Matrix::GetScale()
{
	return Vector3(m_right.Length(), m_up.Length(), m_forward.Length());
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스의 위치를 정하고 자기자신을 반환합니다.
///////////////////////////////////////////////////////////////////////////////
const Matrix & Matrix::SetPosition(const Vector3 & position)
{
	memcpy(&this->m_position, &position, sizeof(position));
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스의 위치를 정하고 자기자신을 반환합니다.
///////////////////////////////////////////////////////////////////////////////
const Matrix & Matrix::SetPosition(float xPosition, float yPosition, float zPosition)
{
	m_position = Vector3(xPosition, yPosition, zPosition);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스를 X축으로 회전시킵니다.
///////////////////////////////////////////////////////////////////////////////
const Matrix & Matrix::SetRotationX(float radian)
{
	Vector3 scale = GetScale();

	float f1 = cosf(radian);
	float f2 = sinf(radian);

	m_11 = scale.x;	m_12 = 0.0f;			m_13 = 0.0f;			m_14 = 0.0f;
	m_21 = 0.0f;	m_22 = f1 * scale.y;	m_23 = f2 * scale.y;	m_24 = 0.0f;
	m_31 = 0.0f;	m_32 = -f2 * scale.z;	m_33 = f1 * scale.z;	m_34 = 0.0f;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스를 Y축으로 회전시킵니다.
///////////////////////////////////////////////////////////////////////////////
const Matrix & Matrix::SetRotationY(float radian)
{
	Vector3 scale = GetScale();

	float f1 = cosf(radian);
	float f2 = sinf(radian);

	m_11 = f1 * scale.x;	m_12 = 0.0f;		m_13 = -f2 * scale.x;	m_14 = 0.0f;
	m_21 = 0.0f;			m_22 = scale.y;		m_23 = 0.0f;			m_24 = 0.0f;
	m_31 = f2 * scale.z;	m_32 = 0.0f;		m_33 = f1 * scale.z;	m_34 = 0.0f;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스를 Z축으로 회전시킵니다.
///////////////////////////////////////////////////////////////////////////////
const Matrix & Matrix::SetRotationZ(float radian)
{
	Vector3 scale = GetScale();

	float f1 = cosf(radian);
	float f2 = sinf(radian);

	m_11 = f1 * scale.x;	m_12 = f2 * scale.x;	m_13 = 0.0f;		m_14 = 0.0f;
	m_21 = -f2 * scale.y;	m_22 = f1 * scale.y;	m_23 = 0.0f;		m_24 = 0.0f;
	m_31 = 0.0f;			m_32 = 0.0f;			m_33 = scale.z;		m_34 = 0.0f;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스를 axis축으로 회전시킵니다.
///////////////////////////////////////////////////////////////////////////////
const Matrix & Matrix::SetRotation(const Vector3 & axis, float angle)
{
	Vector3 scale = GetScale();

	float sinValue = sinf(angle);
	float cosValue = cosf(angle);

	float xx = axis.x * axis.x;
	float yy = axis.y * axis.y;
	float zz = axis.z * axis.z;

	float xy = axis.x * axis.y;
	float xz = axis.x * axis.z;
	float yz = axis.y * axis.z;

	m_11 = xx + cosValue * (1.0f - xx) * scale.x;
	m_12 = (float)(xy - cosValue * xy + sinValue * axis.z) * scale.x;
	m_13 = (float)(xz - cosValue * xz - sinValue * axis.y) * scale.x;
	m_14 = 0.0f;

	m_21 = (float)(xy - cosValue * xy - sinValue * axis.z) * scale.y;
	m_22 = yy + cosValue * (1.0f - yy) * scale.y;
	m_23 = (float)(yz - cosValue * yz + sinValue * axis.x) * scale.y;
	m_24 = 0.0f;

	m_31 = (float)(xz - cosValue * xz + sinValue * axis.y) * scale.z;
	m_32 = (float)(yz - cosValue * yz - sinValue * axis.x) * scale.z;
	m_33 = zz + cosValue * (1.0f - zz) * scale.z;
	m_34 = 0.0f;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스를 yaw(Y축) , pitch(X축) , roll(Z축) 로 회전시킵니다.
///////////////////////////////////////////////////////////////////////////////
const Matrix & Matrix::SetRotation(float yaw, float pitch, float roll)
{
	Quaternion quat;
	quat = Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);
	return this->SetRotation(quat);
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스를 쿼터니언으로 회전시킵니다.
///////////////////////////////////////////////////////////////////////////////
const Matrix & Matrix::SetRotation(const Quaternion & quaternion)
{
	Vector3 scale = GetScale();

	float xx = quaternion.x * quaternion.x;
	float yy = quaternion.y * quaternion.y;
	float zz = quaternion.z * quaternion.z;
	float xy = quaternion.x * quaternion.y;
	float zw = quaternion.z * quaternion.w;
	float zx = quaternion.z * quaternion.x;
	float yw = quaternion.y * quaternion.w;
	float yz = quaternion.y * quaternion.z;
	float xw = quaternion.x * quaternion.w;

	m_11 = (float)(1.0f - 2.0f * (yy + zz)) * scale.x;
	m_12 = (float)(2.0f * (xy + zw)) * scale.x;
	m_13 = (float)(2.0f * (zx - yw)) * scale.x;
	m_14 = 0.0f;

	m_21 = (float)(2.0f * (xy - zw)) * scale.y;
	m_22 = (float)(1.0f - 2.0f * (zz + xx)) * scale.y;
	m_23 = (float)(2.0f * (yz + xw)) * scale.y;
	m_24 = 0.0f;

	m_31 = (float)(2.0f * (zx + yw)) * scale.z;
	m_32 = (float)(2.0f * (yz - xw)) * scale.z;
	m_33 = (float)(1.0f - 2.0f * (yy + xx)) * scale.z;
	m_34 = 0.0f;


	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스의 (기하학적)크기를 정합니다.
///////////////////////////////////////////////////////////////////////////////
const Matrix & Matrix::SetScale(const Vector3 & scale)
{
	m_right.Normalize();
	m_up.Normalize();
	m_forward.Normalize();

	m_right *= scale.x;
	m_up *= scale.y;
	m_forward *= scale.z;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스의 (기하학적)크기를 정합니다.
///////////////////////////////////////////////////////////////////////////////
const Matrix & Matrix::SetScale(float xScale, float yScale, float zScale)
{
	m_right.Normalize();
	m_up.Normalize();
	m_forward.Normalize();

	m_right *= xScale;
	m_up *= yScale;
	m_forward *= zScale;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스의 (기하학적)크기를 정합니다.
///////////////////////////////////////////////////////////////////////////////
const Matrix & Matrix::SetScale(float scale)
{
	m_right.Normalize();
	m_up.Normalize();
	m_forward.Normalize();

	m_right *= scale;
	m_up *= scale;
	m_forward *= scale;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//	매트릭스의 방향들 , (기하학적)크기를 정규화합니다. ( 1 , 1 , 1 )
///////////////////////////////////////////////////////////////////////////////
const Matrix & Matrix::ScaleNormalize()
{
	m_up = m_forward.Cross(m_right);
	m_right = m_up.Cross(m_forward);

	m_right.Normalize();
	m_up.Normalize();
	m_forward.Normalize();

	return *this;
}


///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//	Position 매트릭스를 생성합니다.
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreatePosition(const Vector3 & position)
{
	return Matrix(Vector3::Right, Vector3::Up, Vector3::Forward, position);
}

///////////////////////////////////////////////////////////////////////////////
//	Position 매트릭스를 생성합니다.
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreatePosition(float xPosition, float yPosition, float zPosition)
{
	return Matrix(Vector3::Right, Vector3::Up, Vector3::Forward, Vector3(xPosition, yPosition, zPosition));
}

///////////////////////////////////////////////////////////////////////////////
//	Scale 매트릭스를 생성합니다.
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateScale(const Vector3 & scale)
{
	return Matrix(Vector3::Right, Vector3::Up, Vector3::Forward, Vector3::Zero, scale);
}

///////////////////////////////////////////////////////////////////////////////
//	Scale 매트릭스를 생성합니다.
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateScale(float xScale, float yScale, float zScale)
{
	return Matrix(Vector3::Right, Vector3::Up, Vector3::Forward, Vector3::Zero, Vector3(xScale, yScale, zScale));
}

///////////////////////////////////////////////////////////////////////////////
//	Scale 매트릭스를 생성합니다.
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateScale(float scale)
{
	return Matrix(Vector3::Right, Vector3::Up, Vector3::Forward, Vector3::Zero, scale);
}

///////////////////////////////////////////////////////////////////////////////
//	X축으로 회전시킨 매트릭스를 생성합니다.
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateRotationX(float radian)
{
	float f1 = cosf(radian);
	float f2 = sinf(radian);

	Matrix result(true);	//Identity Matrix
	result.m_22 = f1;	result.m_23 = f2;	
	result.m_32 = -f2;	result.m_33 = f1;	

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	Y축으로 회전시킨 매트릭스를 생성합니다.
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateRotationY(float radian)
{
	float f1 = cosf(radian);
	float f2 = sinf(radian);

	Matrix result(true);	//Identity Matrix
	result.m_11 = f1; result.m_13 = -f2;
	result.m_31 = f2; result.m_33 = f1;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	Z축으로 회전시킨 매트릭스를 생성합니다.
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateRotationZ(float radian)
{
	float f1 = cosf(radian);
	float f2 = sinf(radian);

	Matrix result(true);	//Identity Matrix
	result.m_11 = f1; result.m_12 = f2; 
	result.m_21 = -f2; result.m_22 = f1;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	axis축으로 회전시킨 매트릭스를 생성합니다.
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateFromAxisAngle(const Vector3 & axis, float angle)
{
	float sinValue = (float)sinf(angle);
	float cosValue = (float)cosf(angle);

	float xx = axis.x * axis.x;
	float yy = axis.y * axis.y;
	float zz = axis.z * axis.z;

	float xy = axis.x * axis.y;
	float xz = axis.x * axis.z;
	float yz = axis.y * axis.z;

	Matrix result(true);	//Identity Matrix
	result.m_11 = xx + cosValue * (1.0f - xx);
	result.m_12 = (float)(xy - cosValue * xy + sinValue * axis.z);
	result.m_13 = (float)(xz - cosValue * xz - sinValue * axis.y);

	result.m_21 = (float)(xy - cosValue * xy - sinValue * axis.z);
	result.m_22 = yy + cosValue * (1.0f - yy);
	result.m_23 = (float)(yz - cosValue * yz + sinValue * axis.x);

	result.m_31 = (float)(xz - cosValue * xz + sinValue * axis.y);
	result.m_32 = (float)(yz - cosValue * yz - sinValue * axis.x);
	result.m_33 = zz + cosValue * (1.0f - zz);

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	쿼터니언으로 회전시킨 매트릭스를 생성합니다.
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateFromQuaternion(const Quaternion & quaternion)
{
	float xx = quaternion.x * quaternion.x;
	float yy = quaternion.y * quaternion.y;
	float zz = quaternion.z * quaternion.z;
	float xy = quaternion.x * quaternion.y;
	float zw = quaternion.z * quaternion.w;
	float zx = quaternion.z * quaternion.x;
	float yw = quaternion.y * quaternion.w;
	float yz = quaternion.y * quaternion.z;
	float xw = quaternion.x * quaternion.w;

	Matrix result(true);	//Identity Matrix
	result.m_11 = (float)(1.0f - 2.0f * (yy + zz));
	result.m_12 = (float)(2.0f * (xy + zw));
	result.m_13 = (float)(2.0f * (zx - yw));

	result.m_21 = (float)(2.0f * (xy - zw));
	result.m_22 = (float)(1.0f - 2.0f * (zz + xx));
	result.m_23 = (float)(2.0f * (yz + xw));

	result.m_31 = (float)(2.0f * (zx + yw));
	result.m_32 = (float)(2.0f * (yz - xw));
	result.m_33 = (float)(1.0f - 2.0f * (yy + xx));

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	yaw(Y축) , pitch(X축) , roll(Z축) 로 회전시킨 매트릭스를 생성합니다.
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
	Quaternion quat = Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);

	return Matrix::CreateFromQuaternion(quat);
}
//	World 매트릭스를 생성합니다.
Matrix Matrix::CreateWorld(const Vector3 & position, const Vector3 & forward, const Vector3 & up, const Vector3& scale)
{
	Vector3 right = Vector3::Cross(up, forward);

	return Matrix(right, up, forward, position, scale);
}


///////////////////////////////////////////////////////////////////////////////

//	View

///////////////////////////////////////////////////////////////////////////////
//	원근 투영 매트릭스를 생성합니다. (왼손 좌표계)
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreatePerspective(float fov, float width, float height, float nearPlane, float farPlane)
{
	assert(fov > 0.0f && fov < 3.14159274101257f);
	assert(nearPlane > 0.0f);
	assert(farPlane > 0.0f);
	assert(nearPlane < farPlane);
	assert(width > 0.0f && height > 0.0f);

	float aspectRatio = width / height;

	float h = 1.0f / tanf(fov * 0.5f);
	float w = h / aspectRatio;
	float n = farPlane / (farPlane - nearPlane);
	float f = -farPlane * nearPlane / (farPlane - nearPlane);

	Matrix result;
	result.m_11 = w;
	result.m_12 = result.m_13 = result.m_14 = 0.0f;

	result.m_22 = h;
	result.m_21 = result.m_23 = result.m_24 = 0.0f;

	result.m_33 = n;
	result.m_31 = result.m_32 = 0.0f;
	result.m_34 = 1.0f;

	result.m_43 = f;
	result.m_41 = result.m_42 = result.m_44 = 0.0f;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	직교 투영 매트릭스를 생성합니다. (왼손 좌표계)
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateOrthographic(float width, float height, float nearPlane, float farPlane)
{
	Matrix result;
	result.m_11 = 2.0f / width;
	result.m_12 = result.m_13 = result.m_14 = 0.0f;

	result.m_22 = 2.0f / height;
	result.m_21 = result.m_23 = result.m_24 = 0.0f;

	result.m_33 = (float)(1.0f / (farPlane - nearPlane));
	result.m_31 = result.m_32 = result.m_34 = 0.0f;

	result.m_41 = result.m_42 = 0.0f;
	result.m_43 = nearPlane / (nearPlane - farPlane);

	result.m_44 = 1.0f;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	뷰 매트릭스를 생성합니다. (왼손 좌표계)
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateView_LookTarget(const Vector3 & cameraPosition, const Vector3 & cameraTarget, const Vector3 & cameraUpVector)
{
	Vector3 cam_forward = Vector3::Normalize(cameraTarget - cameraPosition);
	Vector3 cam_right = Vector3::Cross(cameraUpVector, cam_forward).Normalize();
	Vector3 cam_up = Vector3::Cross(cam_forward, cam_right);

	Matrix result;
	result.m_11 = cam_right.x; result.m_12 = cam_up.x; result.m_13 = cam_forward.x; result.m_14 = 0.0f;
	result.m_21 = cam_right.y; result.m_22 = cam_up.y; result.m_23 = cam_forward.y; result.m_24 = 0.0f;
	result.m_31 = cam_right.z; result.m_32 = cam_up.z; result.m_33 = cam_forward.z; result.m_34 = 0.0f;

	result.m_41 = -Vector3::Dot(cam_right, cameraPosition);
	result.m_42 = -Vector3::Dot(cam_up, cameraPosition);
	result.m_43 = -Vector3::Dot(cam_forward, cameraPosition);
	result.m_44 = 1.0f;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	뷰 매트릭스를 생성합니다. (왼손 좌표계)
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateView_LookVector(const Vector3 & cameraPosition, const Vector3 & cameraForwardVector, const Vector3 & cameraUpVector)
{
	Vector3 cam_forward = Vector3::Normalize(cameraForwardVector);
	Vector3 cam_right = Vector3::Cross(cameraUpVector, cam_forward).Normalize();
	Vector3 cam_up = Vector3::Cross(cam_forward, cam_right);

	Matrix result;
	result.m_11 = cam_right.x; result.m_12 = cam_up.x; result.m_13 = cam_forward.x; result.m_14 = 0.0f;
	result.m_21 = cam_right.y; result.m_22 = cam_up.y; result.m_23 = cam_forward.y; result.m_24 = 0.0f;
	result.m_31 = cam_right.z; result.m_32 = cam_up.z; result.m_33 = cam_forward.z; result.m_34 = 0.0f;

	result.m_41 = -Vector3::Dot(cam_right, cameraPosition);
	result.m_42 = -Vector3::Dot(cam_up, cameraPosition);
	result.m_43 = -Vector3::Dot(cam_forward, cameraPosition);
	result.m_44 = 1.0f;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	쿼터니언으로 매트릭스를 변환시킵니다.
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::Transform(const Matrix & value, const Quaternion & rotation)
{
	float wxx = rotation.w * (rotation.x + rotation.x);
	float wyy = rotation.w * (rotation.y + rotation.y);
	float wzz = rotation.w * (rotation.z + rotation.z);

	float xxx = rotation.x * (rotation.x + rotation.x);
	float xyy = rotation.x * (rotation.y + rotation.y);
	float xzz = rotation.x * (rotation.z + rotation.z);

	float yyy = rotation.y * (rotation.y + rotation.y);
	float yzz = rotation.y * (rotation.z + rotation.z);
	float zzz = rotation.z * (rotation.z + rotation.z);

	float f1 = 1.0f - yyy - zzz;
	float f2 = xyy - wzz;
	float f3 = xzz + wyy;
	float f4 = xyy + wzz;

	float f5 = 1.0f - xxx - zzz;
	float f6 = yzz - wxx;
	float f7 = xzz - wyy;
	float f8 = yzz + wxx;

	float f9 = 1.0f - xxx - yyy;

	Matrix result;
	result.m_11 = (float)(value.m_11 * f1 + value.m_12 * f2 + value.m_13 * f3);
	result.m_12 = (float)(value.m_11 * f4 + value.m_12 * f5 + value.m_13 * f6);
	result.m_13 = (float)(value.m_11 * f7 + value.m_12 * f8 + value.m_13 * f9);
	result.m_14 = value.m_14;

	result.m_21 = (float)(value.m_21 * f1 + value.m_22 * f2 + value.m_23 * f3);
	result.m_22 = (float)(value.m_21 * f4 + value.m_22 * f5 + value.m_23 * f6);
	result.m_23 = (float)(value.m_21 * f7 + value.m_22 * f8 + value.m_23 * f9);
	result.m_24 = value.m_24;

	result.m_31 = (float)(value.m_31 * f1 + value.m_32 * f2 + value.m_33 * f3);
	result.m_32 = (float)(value.m_31 * f4 + value.m_32 * f5 + value.m_33 * f6);
	result.m_33 = (float)(value.m_31 * f7 + value.m_32 * f8 + value.m_33 * f9);
	result.m_34 = value.m_34;

	result.m_41 = (float)(value.m_41 * f1 + value.m_42 * f2 + value.m_43 * f3);
	result.m_42 = (float)(value.m_41 * f4 + value.m_42 * f5 + value.m_43 * f6);
	result.m_43 = (float)(value.m_41 * f7 + value.m_42 * f8 + value.m_43 * f9);
	result.m_44 = value.m_44;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	전치 행렬
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::Transpose(const Matrix & matrix)
{
	Matrix result;
	result.m_11 = matrix.m_11; result.m_12 = matrix.m_21; result.m_13 = matrix.m_31; result.m_14 = matrix.m_41;
	result.m_21 = matrix.m_12; result.m_22 = matrix.m_22; result.m_23 = matrix.m_32; result.m_24 = matrix.m_42;
	result.m_31 = matrix.m_13; result.m_32 = matrix.m_23; result.m_33 = matrix.m_33; result.m_34 = matrix.m_43;
	result.m_41 = matrix.m_14; result.m_42 = matrix.m_24; result.m_43 = matrix.m_34; result.m_44 = matrix.m_44;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	역행렬
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::Invert(const Matrix & matrix)
{
	Matrix result;
	float f5 = matrix.m_11; float f4 = matrix.m_12; float f3 = matrix.m_13; float f2 = matrix.m_14;
	float f9 = matrix.m_21; float f8 = matrix.m_22; float f7 = matrix.m_23; float f6 = matrix.m_24;
	float f17 = matrix.m_31; float f16 = matrix.m_32; float f15 = matrix.m_33; float f14 = matrix.m_34;
	float f13 = matrix.m_41; float f12 = matrix.m_42; float f11 = matrix.m_43; float f10 = matrix.m_44;

	float f23 = (f15 * f10) - (f14 * f11);
	float f22 = (f16 * f10) - (f14 * f12);
	float f21 = (f16 * f11) - (f15 * f12);
	float f20 = (f17 * f10) - (f14 * f13);
	float f19 = (f17 * f11) - (f15 * f13);
	float f18 = (f17 * f12) - (f16 * f13);
	float f39 = ((f8 * f23) - (f7 * f22)) + (f6 * f21);
	float f38 = -(((f9 * f23) - (f7 * f20)) + (f6 * f19));
	float f37 = ((f9 * f22) - (f8 * f20)) + (f6 * f18);
	float f36 = -(((f9 * f21) - (f8 * f19)) + (f7 * f18));
	float f = 1.0f / ((((f5 * f39) + (f4 * f38)) + (f3 * f37)) + (f2 * f36));

	result.m_11 = f39 * f;
	result.m_21 = f38 * f;
	result.m_31 = f37 * f;
	result.m_41 = f36 * f;

	result.m_12 = -(((f4 * f23) - (f3 * f22)) + (f2 * f21)) * f;
	result.m_22 = (((f5 * f23) - (f3 * f20)) + (f2 * f19)) * f;
	result.m_32 = -(((f5 * f22) - (f4 * f20)) + (f2 * f18)) * f;
	result.m_42 = (((f5 * f21) - (f4 * f19)) + (f3 * f18)) * f;

	float f35 = (f7 * f10) - (f6 * f11);
	float f34 = (f8 * f10) - (f6 * f12);
	float f33 = (f8 * f11) - (f7 * f12);
	float f32 = (f9 * f10) - (f6 * f13);
	float f31 = (f9 * f11) - (f7 * f13);
	float f30 = (f9 * f12) - (f8 * f13);

	result.m_13 = (((f4 * f35) - (f3 * f34)) + (f2 * f33)) * f;
	result.m_23 = -(((f5 * f35) - (f3 * f32)) + (f2 * f31)) * f;
	result.m_33 = (((f5 * f34) - (f4 * f32)) + (f2 * f30)) * f;
	result.m_43 = -(((f5 * f33) - (f4 * f31)) + (f3 * f30)) * f;

	float f29 = (f7 * f14) - (f6 * f15);
	float f28 = (f8 * f14) - (f6 * f16);
	float f27 = (f8 * f15) - (f7 * f16);
	float f26 = (f9 * f14) - (f6 * f17);
	float f25 = (f9 * f15) - (f7 * f17);
	float f24 = (f9 * f16) - (f8 * f17);

	result.m_14 = -(((f4 * f29) - (f3 * f28)) + (f2 * f27)) * f;
	result.m_24 = (((f5 * f29) - (f3 * f26)) + (f2 * f25)) * f;
	result.m_34 = -(((f5 * f28) - (f4 * f26)) + (f2 * f24)) * f;
	result.m_44 = (((f5 * f27) - (f4 * f25)) + (f3 * f24)) * f;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	선형 보간
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::Lerp(const Matrix & matrix1, const Matrix & matrix2, float amount)
{
	Matrix result;
	result.m_11 = matrix1.m_11 + (matrix2.m_11 - matrix1.m_11) * amount;
	result.m_12 = matrix1.m_12 + (matrix2.m_12 - matrix1.m_12) * amount;
	result.m_13 = matrix1.m_13 + (matrix2.m_13 - matrix1.m_13) * amount;
	result.m_14 = matrix1.m_14 + (matrix2.m_14 - matrix1.m_14) * amount;
	result.m_21 = matrix1.m_21 + (matrix2.m_21 - matrix1.m_21) * amount;
	result.m_22 = matrix1.m_22 + (matrix2.m_22 - matrix1.m_22) * amount;
	result.m_23 = matrix1.m_23 + (matrix2.m_23 - matrix1.m_23) * amount;
	result.m_24 = matrix1.m_24 + (matrix2.m_24 - matrix1.m_24) * amount;
	result.m_31 = matrix1.m_31 + (matrix2.m_31 - matrix1.m_31) * amount;
	result.m_32 = matrix1.m_32 + (matrix2.m_32 - matrix1.m_32) * amount;
	result.m_33 = matrix1.m_33 + (matrix2.m_33 - matrix1.m_33) * amount;
	result.m_34 = matrix1.m_34 + (matrix2.m_34 - matrix1.m_34) * amount;
	result.m_41 = matrix1.m_41 + (matrix2.m_41 - matrix1.m_41) * amount;
	result.m_42 = matrix1.m_42 + (matrix2.m_42 - matrix1.m_42) * amount;
	result.m_43 = matrix1.m_43 + (matrix2.m_43 - matrix1.m_43) * amount;
	result.m_44 = matrix1.m_44 + (matrix2.m_44 - matrix1.m_44) * amount;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	회전 구면보간 , 위치 선형보간
///////////////////////////////////////////////////////////////////////////////
Matrix Matrix::Interpolation(const Matrix & matrix1, const Matrix & matrix2, float amount)
{
	Matrix result;
	Quaternion quat, q2;
	quat = Quaternion::CreateFromMatrix(matrix1);
	q2 = Quaternion::CreateFromMatrix(matrix2);
	quat = Quaternion::Slerp(quat, q2, amount);

	result = Matrix::CreateFromQuaternion(quat);
	result.m_position = Vector3::Lerp(matrix1.m_position, matrix2.m_position, amount);

	return result;
}

///////////////////////////////////////////////////////////////////////////////



