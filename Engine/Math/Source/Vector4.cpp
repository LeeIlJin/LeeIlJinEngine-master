#include <Windows.h>
#include <math.h>
//
#include "Vector4.h"

//
#include <d3dx9math.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix.h"
#include "Quaternion.h"


///////////////////////////////////////////////////////////////////////////////

const Vector4 Vector4::Zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::One = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

const Vector4 Vector4::UnitX = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UnitY = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::UnitZ = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::UnitW = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

///////////////////////////////////////////////////////////////////////////////


Vector4::Vector4(float x, float y, float z, float w) noexcept
	:x(x), y(y), z(z), w(w)
{
	//	Empty
}

Vector4::Vector4(const Vector2 & vec2_xy, const Vector2 & vec2_zw) noexcept
	: x(vec2_xy.x), y(vec2_xy.y), z(vec2_zw.x), w(vec2_zw.y)
{
	//	Empty
}

Vector4::Vector4(const Vector3 & vec3_xyz, float w) noexcept
	: x(vec3_xyz.x), y(vec3_xyz.y), z(vec3_xyz.z), w(w)
{
	//	Empty
}

Vector4::Vector4(const Vector4 & other) noexcept
{
	memcpy(this, &other, sizeof(other));
}

Vector4::Vector4(Vector4 && other) noexcept
{
	memcpy(this, &other, sizeof(other));
	ZeroMemory(&other, sizeof(other));
}


///////////////////////////////////////////////////////////////////////////////

Vector4::operator float*() const noexcept
{
	return (float*)m;
}

///////////////////////////////////////////////////////////////////////////////

Vector4 Vector4::operator+(const Vector4 & other) const noexcept
{
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4 Vector4::operator+(const float & other) const noexcept
{
	return Vector4(x + other, y + other, z + other, w + other);
}

Vector4 Vector4::operator-(const Vector4 & other) const noexcept
{
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4 Vector4::operator-(const float & other) const noexcept
{
	return Vector4(x - other, y - other, z - other, w - other);
}

Vector4 Vector4::operator*(const Vector4 & other) const noexcept
{
	return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}

Vector4 Vector4::operator*(const float & other) const noexcept
{
	return Vector4(x * other, y * other, z * other, w * other);
}

Vector4 Vector4::operator/(const Vector4 & other) const noexcept
{
	return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
}

Vector4 Vector4::operator/(const float & other) const noexcept
{
	return Vector4(x / other, y / other, z / other, w / other);
}

Vector4 Vector4::operator%(const Vector4 & other) const noexcept
{
	Vector4 vec(fabsf(other.x), fabsf(other.y), fabsf(other.z), fabsf(other.w));
	Vector4 result(fabsf(x), fabsf(y), fabsf(z), fabsf(w));
	while (result.x >= vec.x)
		result.x -= vec.x;
	while (result.y >= vec.y)
		result.y -= vec.y;
	while (result.z >= vec.z)
		result.z -= vec.z;
	while (result.w >= vec.w)
		result.w -= vec.w;

	if (x < 0.0f)
		result.x *= -1.0f;
	if (y < 0.0f)
		result.y *= -1.0f;
	if (z < 0.0f)
		result.z *= -1.0f;
	if (w < 0.0f)
		result.w *= -1.0f;

	return result;
}

Vector4 Vector4::operator%(const float & other) const noexcept
{
	float f(fabsf(other));
	Vector4 result(fabsf(x), fabsf(y), fabsf(z), fabsf(w));
	while (result.x >= f)
		result.x -= f;
	while (result.y >= f)
		result.y -= f;
	while (result.z >= f)
		result.z -= f;
	while (result.w >= f)
		result.w -= f;

	if (x < 0.0f)
		result.x *= -1.0f;
	if (y < 0.0f)
		result.y *= -1.0f;
	if (z < 0.0f)
		result.z *= -1.0f;
	if (w < 0.0f)
		result.w *= -1.0f;

	return result;
}

void Vector4::operator+=(const Vector4 & other) noexcept
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
}

void Vector4::operator+=(const float & other) noexcept
{
	x += other;
	y += other;
	z += other;
	w += other;
}

void Vector4::operator-=(const Vector4 & other) noexcept
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
}

void Vector4::operator-=(const float & other) noexcept
{
	x -= other;
	y -= other;
	z -= other;
	w -= other;
}

void Vector4::operator*=(const Vector4 & other) noexcept
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;
}

void Vector4::operator*=(const float & other) noexcept
{
	x *= other;
	y *= other;
	z *= other;
	w *= other;
}

void Vector4::operator/=(const Vector4 & other) noexcept
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;
}

void Vector4::operator/=(const float & other) noexcept
{
	x /= other;
	y /= other;
	z /= other;
	w /= other;
}

void Vector4::operator%=(const Vector4 & other) noexcept
{
	*this = *this % other;
}

void Vector4::operator%=(const float & other) noexcept
{
	*this = *this % other;
}

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//	Vector4의 정보를 String으로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
std::string Vector4::ToString()
{
	std::string temp;
	char val[255];

	sprintf_s(val, "{X:%#f ", x); temp += val;
	sprintf_s(val, "Y:%#f ", y); temp += val;
	sprintf_s(val, "Z:%#f ", z); temp += val;
	sprintf_s(val, "W:%#f}", w); temp += val;

	return temp;
}

///////////////////////////////////////////////////////////////////////////////
//	Vector4의 정보를 Wstring으로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
std::wstring Vector4::ToStringW()
{
	std::wstring temp;
	wchar_t val[255];

	wprintf_s(val, L"{X:%#f ", x); temp += val;
	wprintf_s(val, L"Y:%#f ", y); temp += val;
	wprintf_s(val, L"Z:%#f ", z); temp += val;
	wprintf_s(val, L"W:%#f}", w); temp += val;

	return temp;
}

///////////////////////////////////////////////////////////////////////////////
//	Vector4를 D3DXVECTOR4 로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
D3DXVECTOR4 Vector4::ToD3DXVECTOR4()
{
	return D3DXVECTOR4(x, y, z, w);
}

///////////////////////////////////////////////////////////////////////////////
//	벡터의 길이를 구합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector4::Length()
{
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

///////////////////////////////////////////////////////////////////////////////
//	벡터의 길이의 제곱을 구합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector4::LengthSquared()
{
	return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;
}

///////////////////////////////////////////////////////////////////////////////
//	벡터를 정규화하고 자기자신을 반환합니다.
///////////////////////////////////////////////////////////////////////////////
const Vector4 & Vector4::Normalize()
{
	float len = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);

	x /= len;
	y /= len;
	z /= len;
	w /= len;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//	position1 ~ position2 사이의 길이를 구합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector4::Distance(const Vector4 & position1, const Vector4 & position2)
{
	Vector4 vec = position1 - position2;

	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

///////////////////////////////////////////////////////////////////////////////
//	position1 ~ position2 사이의 길이의 제곱을 구합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector4::DistanceSquared(const Vector4 & position1, const Vector4 & position2)
{
	Vector4 vec = position1 - position2;

	return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

///////////////////////////////////////////////////////////////////////////////
//	value1 , value2 를 내적합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector4::Dot(const Vector4 & value1, const Vector4 & value2)
{
	return value1.x * value2.x + value1.y * value2.y + value1.z * value2.z + value1.w * value2.w;
}

///////////////////////////////////////////////////////////////////////////////
//	value를 정규화한 값을 반환합니다.
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Normalize(const Vector4 & value)
{
	float len = sqrtf(value.x * value.x + value.y * value.y + value.z * value.z + value.w * value.w);

	return Vector4(value.x / len, value.y / len, value.z / len, value.w / len);
}

///////////////////////////////////////////////////////////////////////////////
//	value1 과 value2 의 값들중 작은 값들로만 이루어진 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Min(const Vector4 & value1, const Vector4 & value2)
{
	return Vector4((value1.x < value2.x) ? value1.x : value2.x, (value1.y < value2.y) ? value1.y : value2.y, (value1.z < value2.z) ? value1.z : value2.z, (value1.w < value2.w) ? value1.w : value2.w);
}

///////////////////////////////////////////////////////////////////////////////
//	value1 과 value2 의 값들중 큰 값들로만 이루어진 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Max(const Vector4 & value1, const Vector4 & value2)
{
	return Vector4((value1.x > value2.x) ? value1.x : value2.x, (value1.y > value2.y) ? value1.y : value2.y, (value1.z > value2.z) ? value1.z : value2.z, (value1.w > value2.w) ? value1.w : value2.w);
}

///////////////////////////////////////////////////////////////////////////////
//	value1을 min < value1 < max 로 고정한 값을 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Clamp(const Vector4 & value1, const Vector4 & min, const Vector4 & max)
{
	Vector4 result(value1);

	result.x = (result.x < min.x) ? min.x : (result.x > max.x) ? max.x : result.x;
	result.y = (result.y < min.y) ? min.y : (result.y > max.y) ? max.y : result.y;
	result.z = (result.z < min.z) ? min.z : (result.z > max.z) ? max.z : result.z;
	result.w = (result.w < min.w) ? min.w : (result.w > max.w) ? max.w : result.w;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	value1을 0 < value1 < 1 으로 고정한 값을 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Clamp01(const Vector4 & value1)
{
	return Vector4::Clamp(value1, Vector4::Zero, Vector4::One);
}

///////////////////////////////////////////////////////////////////////////////
//	선형 보간
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Lerp(const Vector4 & value1, const Vector4 & value2, float amount)
{
	Vector4 result;
	result.x = value1.x + (value2.x - value1.x) * amount;
	result.y = value1.y + (value2.y - value1.y) * amount;
	result.z = value1.z + (value2.z - value1.z) * amount;
	result.w = value1.w + (value2.w - value1.w) * amount;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	스무스 보간
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::SmoothStep(const Vector4 & value1, const Vector4 & value2, float amount)
{
	amount = (amount > 1.0f) ? 1.0f : ((amount < 0.0f) ? 0.0f : amount);
	amount = (amount * amount * (3.0f - 2.0f * amount));

	Vector4 result;
	result.x = value1.x + (value2.x - value1.x) * amount;
	result.y = value1.y + (value2.y - value1.y) * amount;
	result.z = value1.z + (value2.z - value1.z) * amount;
	result.w = value1.w + (value2.w - value1.w) * amount;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	카트뮬-롬 보간
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::CatmullRom(const Vector4 & value1, const Vector4 & value2, const Vector4 & value3, const Vector4 & value4, float amount)
{
	float amountSquare = amount * amount;
	float amountCube = amount * amountSquare;

	Vector4 result;
	result.x = 0.5f * (2.0f * value2.x + (-value1.x + value3.x)* amount + (2.0f * value1.x - 5.0f * value2.x + 4.0f * value3.x - value4.x)* amountSquare + (-value1.x + 3.0f * value2.x - 3.0f * value3.x + value4.x)* amountCube);
	result.y = 0.5f * (2.0f * value2.y + (-value1.y + value3.y)* amount + (2.0f * value1.y - 5.0f * value2.y + 4.0f * value3.y - value4.y)* amountSquare + (-value1.y + 3.0f * value2.y - 3.0f * value3.y + value4.y)* amountCube);
	result.z = 0.5f * (2.0f * value2.z + (-value1.z + value3.z)* amount + (2.0f * value1.z - 5.0f * value2.z + 4.0f * value3.z - value4.z)* amountSquare + (-value1.z + 3.0f * value2.z - 3.0f * value3.z + value4.z)* amountCube);
	result.w = 0.5f * (2.0f * value2.w + (-value1.w + value3.w)* amount + (2.0f * value1.w - 5.0f * value2.w + 4.0f * value3.w - value4.w)* amountSquare + (-value1.w + 3.0f * value2.w - 3.0f * value3.w + value4.w)* amountCube);

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	에르미트 보간
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Hermite(const Vector4 & value1, const Vector4 & tangent1, const Vector4 & value2, const Vector4 & tangent2, float amount)
{
	float amountSquare = amount * amount;
	float amountCube = amount * amountSquare;

	float f1 = (2.0f * amountCube - 3.0f * amountSquare + 1.0f);
	float f2 = (-2.0f * amountCube + 3.0f * amountSquare);
	float f3 = amountCube - 2.0f * amountSquare + amount;
	float f4 = amountCube - amountSquare;

	Vector4 result;
	result.x = value1.x * f1 + value2.x * f2 + tangent1.x * f3 + tangent2.x * f4;
	result.y = value1.y * f1 + value2.y * f2 + tangent1.y * f3 + tangent2.y * f4;
	result.z = value1.z * f1 + value2.z * f2 + tangent1.z * f3 + tangent2.z * f4;
	result.w = value1.w * f1 + value2.w * f2 + tangent1.w * f3 + tangent2.w * f4;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	Vector2를 이용하여 메트릭스에 의해 변환된 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Transform(const Vector2 & position, const Matrix & matrix)
{
	float f1 = (float)(position.x * matrix.m_11 + position.y * matrix.m_21) + matrix.m_41;
	float f2 = (float)(position.x * matrix.m_12 + position.y * matrix.m_22) + matrix.m_42;
	float f3 = (float)(position.x * matrix.m_13 + position.y * matrix.m_23) + matrix.m_43;
	float f4 = (float)(position.x * matrix.m_14 + position.y * matrix.m_24) + matrix.m_44;

	Vector4 vector4;
	vector4.x = f1;
	vector4.y = f2;
	vector4.z = f3;
	vector4.w = f4;

	return vector4;
}

///////////////////////////////////////////////////////////////////////////////
//	Vector3를 이용하여 메트릭스에 의해 변환된 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Transform(const Vector3 & position, const Matrix & matrix)
{
	float f1 = (float)(position.x * matrix.m_11 + position.y * matrix.m_21 + position.z * matrix.m_31) + matrix.m_41;
	float f2 = (float)(position.x * matrix.m_12 + position.y * matrix.m_22 + position.z * matrix.m_32) + matrix.m_42;
	float f3 = (float)(position.x * matrix.m_13 + position.y * matrix.m_23 + position.z * matrix.m_33) + matrix.m_43;
	float f4 = (float)(position.x * matrix.m_14 + position.y * matrix.m_24 + position.z * matrix.m_34) + matrix.m_44;

	Vector4 vector4;
	vector4.x = f1;
	vector4.y = f2;
	vector4.z = f3;
	vector4.w = f4;

	return vector4;
}

///////////////////////////////////////////////////////////////////////////////
//	메트릭스에 의해 변환된 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Transform(const Vector4 & position, const Matrix & matrix)
{
	float f1 = (float)(position.x * matrix.m_11 + position.y * matrix.m_21 + position.z * matrix.m_31 + position.w * matrix.m_41);
	float f2 = (float)(position.x * matrix.m_12 + position.y * matrix.m_22 + position.z * matrix.m_32 + position.w * matrix.m_42);
	float f3 = (float)(position.x * matrix.m_13 + position.y * matrix.m_23 + position.z * matrix.m_33 + position.w * matrix.m_43);
	float f4 = (float)(position.x * matrix.m_14 + position.y * matrix.m_24 + position.z * matrix.m_34 + position.w * matrix.m_44);

	Vector4 vector4;
	vector4.x = f1;
	vector4.y = f2;
	vector4.z = f3;
	vector4.w = f4;

	return vector4;
}

///////////////////////////////////////////////////////////////////////////////
//	Vector2를 이용하여 쿼터니언에 의해 변환된 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Transform(const Vector2 & value, const Quaternion & rotation)
{
	float f1 = rotation.x + rotation.x;
	float f2 = rotation.y + rotation.y;
	float f3 = rotation.z + rotation.z;

	float f4 = rotation.w * f1;
	float f5 = rotation.w * f2;
	float f6 = rotation.w * f3;
	float f7 = rotation.x * f1;
	float f8 = rotation.x * f2;
	float f9 = rotation.x * f3;

	float f10 = rotation.y * f2;
	float f11 = rotation.y * f3;
	float f12 = rotation.z * f3;

	float f13 = (float)(value.x * (1.0f - f10 - f12) + value.y * (f8 - f6));
	float f14 = (float)(value.x * (f8 + f6) + value.y * (1.0f - f7 - f12));
	float f15 = (float)(value.x * (f9 - f5) + value.y * (f11 + f4));

	Vector4 vector4;
	vector4.x = f13;
	vector4.y = f14;
	vector4.z = f15;
	vector4.w = 1.0f;
	return vector4;
}

///////////////////////////////////////////////////////////////////////////////
//	Vector3를 이용하여 쿼터니언에 의해 변환된 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Transform(const Vector3 & value, const Quaternion & rotation)
{
	float f1 = rotation.x + rotation.x;
	float f2 = rotation.y + rotation.y;
	float f3 = rotation.z + rotation.z;

	float f4 = rotation.w * f1;
	float f5 = rotation.w * f2;
	float f6 = rotation.w * f3;
	float f7 = rotation.x * f1;
	float f8 = rotation.x * f2;
	float f9 = rotation.x * f3;

	float f10 = rotation.y * f2;
	float f11 = rotation.y * f3;
	float f12 = rotation.z * f3;

	float f13 = (float)(value.x * (1.0f - f10 - f12) + value.y * (f8 - f6) + value.z * (f9 + f5));
	float f14 = (float)(value.x * (f8 + f6) + value.y * (1.0f - f7 - f12) + value.z * (f11 - f4));
	float f15 = (float)(value.x * (f9 - f5) + value.y * (f11 + f4) + value.z * (1.0f - f7 - f10));

	Vector4 vector4;
	vector4.x = f13;
	vector4.y = f14;
	vector4.z = f15;
	vector4.w = 1.0f;

	return vector4;
}

///////////////////////////////////////////////////////////////////////////////
//	쿼터니언에 의해 변환된 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Transform(const Vector4 & value, const Quaternion & rotation)
{
	float f1 = rotation.x + rotation.x;
	float f2 = rotation.y + rotation.y;
	float f3 = rotation.z + rotation.z;

	float f4 = rotation.w * f1;
	float f5 = rotation.w * f2;
	float f6 = rotation.w * f3;
	float f7 = rotation.x * f1;
	float f8 = rotation.x * f2;
	float f9 = rotation.x * f3;

	float f10 = rotation.y * f2;
	float f11 = rotation.y * f3;
	float f12 = rotation.z * f3;

	float f13 = (float)(value.x * (1.0f - f10 - f12) + value.y * (f8 - f6) + value.z * (f9 + f5));
	float f14 = (float)(value.x * (f8 + f6) + value.y * (1.0f - f7 - f12) + value.z * (f11 - f4));
	float f15 = (float)(value.x * (f9 - f5) + value.y * (f11 + f4) + value.z * (1.0f - f7 - f10));

	Vector4 vector4;
	vector4.x = f13;
	vector4.y = f14;
	vector4.z = f15;
	vector4.w = value.w;

	return vector4;
}


///////////////////////////////////////////////////////////////////////////////



