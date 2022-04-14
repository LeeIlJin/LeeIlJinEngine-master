#include <Windows.h>
#include <math.h>
//
#include "Vector3.h"

//
#include <d3dx9math.h>

#include "Vector2.h"
#include "Matrix.h"
#include "Quaternion.h"

///////////////////////////////////////////////////////////////////////////////

const Vector3 Vector3::Zero = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::One = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::Right = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Up = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::Forward = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Left = Vector3(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Down = Vector3(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::Backward = Vector3(0.0f, 0.0f, -1.0f);

const Vector3 Vector3::UnitX = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ = Vector3(0.0f, 0.0f, 1.0f);

///////////////////////////////////////////////////////////////////////////////

Vector3::Vector3(float x, float y, float z) noexcept
	:x(x), y(y), z(z)
{
	//	Empty
}

Vector3::Vector3(const Vector2 & vec2_xy, float z) noexcept
	: x(vec2_xy.x), y(vec2_xy.y), z(z)
{
	//	Empty
}

Vector3::Vector3(const Vector3 & other) noexcept
{
	memcpy(this, &other, sizeof(other));
}

Vector3::Vector3(Vector3 && other) noexcept
{
	memcpy(this, &other, sizeof(other));
	ZeroMemory(&other, sizeof(other));
}


///////////////////////////////////////////////////////////////////////////////

Vector3::operator float*() const noexcept
{
	return (float*)m;
}

///////////////////////////////////////////////////////////////////////////////

Vector3 Vector3::operator+(const Vector3 & other) const noexcept
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator+(const float & other) const noexcept
{
	return Vector3(x + other, y + other, z + other);
}

Vector3 Vector3::operator-(const Vector3 & other) const noexcept
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator-(const float & other) const noexcept
{
	return Vector3(x - other, y - other, z - other);
}

Vector3 Vector3::operator*(const Vector3 & other) const noexcept
{
	return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator*(const float & other) const noexcept
{
	return Vector3(x * other, y * other, z * other);
}

Vector3 Vector3::operator/(const Vector3 & other) const noexcept
{
	return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator/(const float & other) const noexcept
{
	return Vector3(x / other, y / other, z / other);
}

Vector3 Vector3::operator%(const Vector3 & other) const noexcept
{
	Vector3 vec(fabsf(other.x), fabsf(other.y), fabsf(other.z));
	Vector3 result(fabsf(x), fabsf(y), fabsf(z));
	while (result.x >= vec.x)
		result.x -= vec.x;
	while (result.y >= vec.y)
		result.y -= vec.y;
	while (result.z >= vec.z)
		result.z -= vec.z;

	if (x < 0.0f)
		result.x *= -1.0f;
	if (y < 0.0f)
		result.y *= -1.0f;
	if (z < 0.0f)
		result.z *= -1.0f;

	return result;
}

Vector3 Vector3::operator%(const float & other) const noexcept
{
	float f(fabsf(other));
	Vector3 result(fabsf(x), fabsf(y), fabsf(z));
	while (result.x >= f)
		result.x -= f;
	while (result.y >= f)
		result.y -= f;
	while (result.z >= f)
		result.z -= f;

	if (x < 0.0f)
		result.x *= -1.0f;
	if (y < 0.0f)
		result.y *= -1.0f;
	if (z < 0.0f)
		result.z *= -1.0f;

	return result;
}

void Vector3::operator+=(const Vector3 & other) noexcept
{
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vector3::operator+=(const float & other) noexcept
{
	x += other;
	y += other;
	z += other;
}

void Vector3::operator-=(const Vector3 & other) noexcept
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

void Vector3::operator-=(const float & other) noexcept
{
	x -= other;
	y -= other;
	z -= other;
}

void Vector3::operator*=(const Vector3 & other) noexcept
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
}

void Vector3::operator*=(const float & other) noexcept
{
	x *= other;
	y *= other;
	z *= other;
}

void Vector3::operator/=(const Vector3 & other) noexcept
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
}

void Vector3::operator/=(const float & other) noexcept
{
	x /= other;
	y /= other;
	z /= other;
}

void Vector3::operator%=(const Vector3 & other) noexcept
{
	*this = *this % other;
}

void Vector3::operator%=(const float & other) noexcept
{
	*this = *this % other;
}


///////////////////////////////////////////////////////////////////////////////
//	Vector3의 정보를 String으로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
std::string Vector3::ToString()
{
	std::string temp;
	char val[255];

	sprintf_s(val, "{X:%#f ", x); temp += val;
	sprintf_s(val, "Y:%#f ", y); temp += val;
	sprintf_s(val, "Z:%#f}", z); temp += val;

	return temp;
}

///////////////////////////////////////////////////////////////////////////////
//	Vector3의 정보를 Wstring으로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
std::wstring Vector3::ToStringW()
{
	std::wstring temp;
	wchar_t val[255];

	wprintf_s(val, L"{X:%#f ", x); temp += val;
	wprintf_s(val, L"Y:%#f ", y); temp += val;
	wprintf_s(val, L"Z:%#f}", z); temp += val;

	return temp;
}

///////////////////////////////////////////////////////////////////////////////
//	Vector3를 D3DXVECTOR3 로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 Vector3::ToD3DXVECTOR3()
{
	return D3DXVECTOR3(x, y, z);
}

///////////////////////////////////////////////////////////////////////////////
//	벡터의 길이를 구합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector3::Length()
{
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}

///////////////////////////////////////////////////////////////////////////////
//	벡터의 길이의 제곱을 구합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector3::LengthSquared()
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

///////////////////////////////////////////////////////////////////////////////
//	벡터를 정규화하고 자기자신을 반환합니다.
///////////////////////////////////////////////////////////////////////////////
const Vector3 & Vector3::Normalize()
{
	float len = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);

	x /= len;
	y /= len;
	z /= len;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//	position1 ~ position2 사이의 길이를 구합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector3::Distance(const Vector3 & position1, const Vector3 & position2)
{
	Vector3 vec = position1 - position2;

	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

///////////////////////////////////////////////////////////////////////////////
//	position1 ~ position2 사이의 길이의 제곱을 구합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector3::DistanceSquared(const Vector3 & position1, const Vector3 & position2)
{
	Vector3 vec = position1 - position2;

	return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

///////////////////////////////////////////////////////////////////////////////
//	value1 , value2 를 내적합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector3::Dot(const Vector3 & value1, const Vector3 & value2)
{
	return value1.x * value2.x + value1.y * value2.y + value1.z * value2.z;
}

///////////////////////////////////////////////////////////////////////////////
//	value를 정규화한 값을 반환합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Normalize(const Vector3 & value)
{
	float len = sqrtf(value.x * value.x + value.y * value.y + value.z * value.z);

	return Vector3(value.x / len, value.y / len, value.z / len);
}

///////////////////////////////////////////////////////////////////////////////
//	value1 , value2 를 외적합니다. (왼손 좌표계일 경우, up 벡터를 구할때 forward , right 순서입니다.)
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Cross(const Vector3& value1, const Vector3& value2)
{
	Vector3 result;
	result.x = (value1.y * value2.z - value1.z * value2.y);
	result.y = (value1.z * value2.x - value1.x * value2.z);
	result.z = (value1.x * value2.y - value1.y * value2.x);

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	normal 에 대한 vector의 반사 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Reflect(const Vector3 & vector, const Vector3 & normal)
{
	float d = vector.x * normal.x + vector.y * normal.y + vector.z * normal.z;

	return Vector3(vector.x - 2.0f * d * normal.x, vector.y - 2.0f * d * normal.y, vector.z - 2.0f * d * normal.z);
}

///////////////////////////////////////////////////////////////////////////////
//	value1 과 value2 의 값들중 작은 값들로만 이루어진 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Min(const Vector3 & value1, const Vector3 & value2)
{
	return Vector3((value1.x < value2.x) ? value1.x : value2.x, (value1.y < value2.y) ? value1.y : value2.y, (value1.z < value2.z) ? value1.z : value2.z);
}

///////////////////////////////////////////////////////////////////////////////
//	value1 과 value2 의 값들중 큰 값들로만 이루어진 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Max(const Vector3 & value1, const Vector3 & value2)
{
	return Vector3((value1.x > value2.x) ? value1.x : value2.x, (value1.y > value2.y) ? value1.y : value2.y, (value1.z > value2.z) ? value1.z : value2.z);
}

///////////////////////////////////////////////////////////////////////////////
//	value1을 min < value1 < max 로 고정한 값을 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Clamp(const Vector3 & value1, const Vector3 & min, const Vector3 & max)
{
	Vector3 result(value1);

	result.x = (result.x < min.x) ? min.x : (result.x > max.x) ? max.x : result.x;
	result.y = (result.y < min.y) ? min.y : (result.y > max.y) ? max.y : result.y;
	result.z = (result.z < min.z) ? min.z : (result.z > max.z) ? max.z : result.z;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	value1을 0 < value1 < 1 으로 고정한 값을 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Clamp01(const Vector3 & value1)
{
	return Vector3::Clamp(value1, Vector3::Zero, Vector3::One);
}

///////////////////////////////////////////////////////////////////////////////
//	선형 보간
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Lerp(const Vector3 & value1, const Vector3 & value2, float amount)
{
	Vector3 result;
	result.x = value1.x + (value2.x - value1.x) * amount;
	result.y = value1.y + (value2.y - value1.y) * amount;
	result.z = value1.z + (value2.z - value1.z) * amount;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	스무스 보간
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::SmoothStep(const Vector3 & value1, const Vector3 & value2, float amount)
{
	amount = (amount > 1.0f) ? 1.0f : ((amount < 0.0f) ? 0.0f : amount);
	amount = (amount * amount * (3.0f - 2.0f * amount));

	Vector3 result;
	result.x = value1.x + (value2.x - value1.x) * amount;
	result.y = value1.y + (value2.y - value1.y) * amount;
	result.z = value1.z + (value2.z - value1.z) * amount;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	카트뮬-롬 보간
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::CatmullRom(const Vector3 & value1, const Vector3 & value2, const Vector3 & value3, const Vector3 & value4, float amount)
{
	float amountSquare = amount * amount;
	float amountCube = amount * amountSquare;

	Vector3 result;
	result.x = 0.5f * (2.0f * value2.x + (-value1.x + value3.x)* amount + (2.0f * value1.x - 5.0f * value2.x + 4.0f * value3.x - value4.x)* amountSquare + (-value1.x + 3.0f * value2.x - 3.0f * value3.x + value4.x)* amountCube);
	result.y = 0.5f * (2.0f * value2.y + (-value1.y + value3.y)* amount + (2.0f * value1.y - 5.0f * value2.y + 4.0f * value3.y - value4.y)* amountSquare + (-value1.y + 3.0f * value2.y - 3.0f * value3.y + value4.y)* amountCube);
	result.z = 0.5f * (2.0f * value2.z + (-value1.z + value3.z)* amount + (2.0f * value1.z - 5.0f * value2.z + 4.0f * value3.z - value4.z)* amountSquare + (-value1.z + 3.0f * value2.z - 3.0f * value3.z + value4.z)* amountCube);

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	에르미트 보간
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Hermite(const Vector3 & value1, const Vector3 & tangent1, const Vector3 & value2, const Vector3 & tangent2, float amount)
{
	float amountSquare = amount * amount;
	float amountCube = amount * amountSquare;

	float f1 = (2.0f * amountCube - 3.0f * amountSquare + 1.0f);
	float f2 = (-2.0f * amountCube + 3.0f * amountSquare);
	float f3 = amountCube - 2.0f * amountSquare + amount;
	float f4 = amountCube - amountSquare;

	Vector3 result;
	result.x = value1.x * f1 + value2.x * f2 + tangent1.x * f3 + tangent2.x * f4;
	result.y = value1.y * f1 + value2.y * f2 + tangent1.y * f3 + tangent2.y * f4;
	result.z = value1.z * f1 + value2.z * f2 + tangent1.z * f3 + tangent2.z * f4;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	메트릭스에 의해 변환된 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Transform(const Vector3 & position, const Matrix & matrix)
{
	float f1 = (float)(position.x * matrix.m_11 + position.y * matrix.m_21 + position.z * matrix.m_31) + matrix.m_41;
	float f2 = (float)(position.x * matrix.m_12 + position.y * matrix.m_22 + position.z * matrix.m_32) + matrix.m_42;
	float f3 = (float)(position.x * matrix.m_13 + position.y * matrix.m_23 + position.z * matrix.m_33) + matrix.m_43;

	Vector3 vector3;
	vector3.x = f1;
	vector3.y = f2;
	vector3.z = f3;

	return vector3;
}

///////////////////////////////////////////////////////////////////////////////
//	쿼터니언에 의해 변환된 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Transform(const Vector3 & value, const Quaternion & rotation)
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

	float f13 = (value.x * (1.0f - f10 - f12) + value.y * (f8 - f6) + value.z * (f9 + f5));
	float f14 = (value.x * (f8 + f6) + value.y * (1.0f - f7 - f12) + value.z * (f11 - f4));
	float f15 = (value.x * (f9 - f5) + value.y * (f11 + f4) + value.z * (1.0f - f7 - f10));

	Vector3 vector3;
	vector3.x = f13;
	vector3.y = f14;
	vector3.z = f15;

	return vector3;
}

///////////////////////////////////////////////////////////////////////////////
//	메트릭스에 의해 변환된 방향 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::TransformNormal(const Vector3 & normal, const Matrix & matrix)
{
	float f1 = (float)(normal.x * matrix.m_11 + normal.y * matrix.m_21 + normal.z * matrix.m_31);
	float f2 = (float)(normal.x * matrix.m_12 + normal.y * matrix.m_22 + normal.z * matrix.m_32);
	float f3 = (float)(normal.x * matrix.m_13 + normal.y * matrix.m_23 + normal.z * matrix.m_33);

	Vector3 vector3;
	vector3.x = f1;
	vector3.y = f2;
	vector3.z = f3;

	return vector3;
}

///////////////////////////////////////////////////////////////////////////////
//	메트릭스에 의해 변환된 위치 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 Vector3::TransformCoord(const Vector3 & position, const Matrix & matrix)
{
	float f1 = (matrix.m_11 * position.x) + (matrix.m_21 * position.y) + (matrix.m_31 * position.z) + matrix.m_41;
	float f2 = (matrix.m_12 * position.x) + (matrix.m_22 * position.y) + (matrix.m_32 * position.z) + matrix.m_42;
	float f3 = (matrix.m_13 * position.x) + (matrix.m_23 * position.y) + (matrix.m_33 * position.z) + matrix.m_43;
	float f4 = (matrix.m_14 * position.x) + (matrix.m_24 * position.y) + (matrix.m_34 * position.z) + matrix.m_44;

	return Vector3((f1 / f4), (f2 / f4), (f3 / f4));
}


///////////////////////////////////////////////////////////////////////////////

