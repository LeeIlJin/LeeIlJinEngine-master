#include <Windows.h>
#include <math.h>
//
#include "Vector2.h"

//
#include <d3dx9math.h>

#include "Matrix.h"
#include "Quaternion.h"

///////////////////////////////////////////////////////////////////////////////

const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
const Vector2 Vector2::Up = Vector2(0.0f, 1.0f);
const Vector2 Vector2::Left = Vector2(-1.0f, 0.0f);
const Vector2 Vector2::Down = Vector2(0.0f, -1.0f);

const Vector2 Vector2::UnitX = Vector2(1.0f, 0.0f);
const Vector2 Vector2::UnitY = Vector2(0.0f, 1.0f);

///////////////////////////////////////////////////////////////////////////////

Vector2::Vector2() noexcept
	:x(0.0f), y(0.0f)
{
	//	Empty
}

Vector2::Vector2(float x, float y) noexcept
	: x(x), y(y)
{
	//	Empty
}

Vector2::Vector2(const Vector2 & other) noexcept
	: x(other.x), y(other.y)
{
	// Empty
}

Vector2::Vector2(Vector2 && other) noexcept
	: x(other.x), y(other.y)
{
	other.x = 0.0f;
	other.y = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////

Vector2::operator float*() const noexcept
{
	return (float*)m;
}

///////////////////////////////////////////////////////////////////////////////

Vector2 Vector2::operator+(const Vector2 & other) const noexcept
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator+(const float & other) const noexcept
{
	return Vector2(x + other, y + other);
}

Vector2 Vector2::operator-(const Vector2 & other) const noexcept
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator-(const float & other) const noexcept
{
	return Vector2(x - other, y - other);
}

Vector2 Vector2::operator*(const Vector2 & other) const noexcept
{
	return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::operator*(const float & other) const noexcept
{
	return Vector2(x * other, y * other);
}

Vector2 Vector2::operator/(const Vector2 & other) const noexcept
{
	return Vector2(x / other.x, y / other.y);
}

Vector2 Vector2::operator/(const float & other) const noexcept
{
	return Vector2(x / other, y / other);
}

Vector2 Vector2::operator%(const Vector2 & other) const noexcept
{
	Vector2 vec(fabsf(other.x), fabsf(other.y));
	Vector2 result(fabsf(x), fabsf(y));
	while (result.x >= vec.x)
		result.x -= vec.x;
	while (result.y >= vec.y)
		result.y -= vec.y;

	if (x < 0.0f)
		result.x *= -1.0f;
	if (y < 0.0f)
		result.y *= -1.0f;
		
	return result;
}

Vector2 Vector2::operator%(const float & other) const noexcept
{
	float f(fabsf(other));
	Vector2 result(fabsf(x), fabsf(y));
	while (result.x >= f)
		result.x -= f;
	while (result.y >= f)
		result.y -= f;

	if (x < 0.0f)
		result.x *= -1.0f;
	if (y < 0.0f)
		result.y *= -1.0f;

	return result;
}

void Vector2::operator+=(const Vector2 & other) noexcept
{
	x += other.x;
	y += other.y;
}

void Vector2::operator+=(const float & other) noexcept
{
	x += other;
	y += other;
}

void Vector2::operator-=(const Vector2 & other) noexcept
{
	x -= other.x;
	y -= other.y;
}

void Vector2::operator-=(const float & other) noexcept
{
	x -= other;
	y -= other;
}

void Vector2::operator*=(const Vector2 & other) noexcept
{
	x *= other.x;
	y *= other.y;
}

void Vector2::operator*=(const float & other) noexcept
{
	x *= other;
	y *= other;
}

void Vector2::operator/=(const Vector2 & other) noexcept
{
	x /= other.x;
	y /= other.y;
}

void Vector2::operator/=(const float & other) noexcept
{
	x /= other;
	y /= other;
}

void Vector2::operator%=(const Vector2 & other) noexcept
{
	*this = *this % other;
}

void Vector2::operator%=(const float & other) noexcept
{
	*this = *this % other;
}


///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//	Vector2의 정보를 String으로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
std::string Vector2::ToString()
{
	std::string temp;
	char val[255];

	sprintf_s(val, "{X:%#f ", x); temp += val;
	sprintf_s(val, "Y:%#f}", y); temp += val;

	return temp;
}

///////////////////////////////////////////////////////////////////////////////
//	Vector2의 정보를 Wstring으로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
std::wstring Vector2::ToStringW()
{
	std::wstring temp;
	wchar_t val[255];

	wprintf_s(val, L"{X:%#f ", x); temp += val;
	wprintf_s(val, L"Y:%#f}", y); temp += val;

	return temp;
}

///////////////////////////////////////////////////////////////////////////////
//	Vector2를 D3DXVECTOR2 로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
D3DXVECTOR2 Vector2::ToD3DXVECTOR2()
{
	return D3DXVECTOR2(x, y);
}

///////////////////////////////////////////////////////////////////////////////
//	벡터의 길이를 구합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector2::Length()
{
	return sqrtf(this->x * this->x + this->y * this->y);
}

///////////////////////////////////////////////////////////////////////////////
//	벡터의 길이의 제곱을 구합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector2::LengthSquared()
{
	return this->x * this->x + this->y * this->y;
}

///////////////////////////////////////////////////////////////////////////////
//	벡터를 정규화하고 자기자신을 반환합니다.
///////////////////////////////////////////////////////////////////////////////
const Vector2 & Vector2::Normalize()
{
	float len = sqrtf(this->x * this->x + this->y * this->y);

	x /= len;
	y /= len;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//	position1 ~ position2 사이의 길이를 구합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector2::Distance(const Vector2 & position1, const Vector2 & position2)
{
	Vector2 vec = position1 - position2;

	return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

///////////////////////////////////////////////////////////////////////////////
//	position1 ~ position2 사이의 길이의 제곱을 구합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector2::DistanceSquared(const Vector2 & position1, const Vector2 & position2)
{
	Vector2 vec = position1 - position2;

	return vec.x * vec.x + vec.y * vec.y;
}

///////////////////////////////////////////////////////////////////////////////
//	value1 , value2 를 내적합니다.
///////////////////////////////////////////////////////////////////////////////
float Vector2::Dot(const Vector2 & value1, const Vector2 & value2)
{
	return value1.x * value2.x + value1.y * value2.y;
}

///////////////////////////////////////////////////////////////////////////////
//	value를 정규화한 값을 반환합니다.
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::Normalize(const Vector2 & value)
{
	float len = sqrtf(value.x * value.x + value.y * value.y);

	return Vector2(value.x / len, value.y / len);
}

///////////////////////////////////////////////////////////////////////////////
//	value의 수직 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::Cross(const Vector2 & value)
{
	return Vector2(-value.y, value.x);
}

///////////////////////////////////////////////////////////////////////////////
//	normal 에 대한 vector의 반사 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::Reflect(const Vector2 & vector, const Vector2 & normal)
{
	float d = vector.x * normal.x + vector.y * normal.y;

	return Vector2(vector.x - 2.0f * d * normal.x, vector.y - 2.0f * d * normal.y);
}

///////////////////////////////////////////////////////////////////////////////
//	value1 과 value2 의 값들중 작은 값들로만 이루어진 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::Min(const Vector2 & value1, const Vector2 & value2)
{
	return Vector2((value1.x < value2.x) ? value1.x : value2.x, (value1.y < value2.y) ? value1.y : value2.y);
}

///////////////////////////////////////////////////////////////////////////////
//	value1 과 value2 의 값들중 큰 값들로만 이루어진 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::Max(const Vector2 & value1, const Vector2 & value2)
{
	return Vector2((value1.x > value2.x) ? value1.x : value2.x, (value1.y > value2.y) ? value1.y : value2.y);
}

///////////////////////////////////////////////////////////////////////////////
//	value1을 min < value1 < max 로 고정한 값을 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::Clamp(const Vector2 & value1, const Vector2 & min, const Vector2 & max)
{
	Vector2 result(value1);

	result.x = (result.x < min.x) ? min.x : (result.x > max.x) ? max.x : result.x;
	result.y = (result.y < min.y) ? min.y : (result.y > max.y) ? max.y : result.y;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	value1을 0 < value1 < 1 으로 고정한 값을 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::Clamp01(const Vector2 & value1)
{
	return Vector2::Clamp(value1, Vector2::Zero, Vector2::One);
}

///////////////////////////////////////////////////////////////////////////////
//	선형 보간
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::Lerp(const Vector2 & value1, const Vector2 & value2, float amount)
{
	Vector2 result;
	result.x = value1.x + (value2.x - value1.x) * amount;
	result.y = value1.y + (value2.y - value1.y) * amount;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	스무스 보간
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::SmoothStep(const Vector2 & value1, const Vector2 & value2, float amount)
{
	amount = (amount > 1.0f) ? 1.0f : ((amount < 0.0f) ? 0.0f : amount);
	amount = (amount * amount * (3.0f - 2.0f * amount));

	Vector2 result;
	result.x = value1.x + (value2.x - value1.x) * amount;
	result.y = value1.y + (value2.y - value1.y) * amount;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	카트뮬-롬 보간
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::CatmullRom(const Vector2 & value1, const Vector2 & value2, const Vector2 & value3, const Vector2 & value4, float amount)
{
	float amountSquare = amount * amount;
	float amountCube = amount * amountSquare;

	Vector2 result;
	result.x = 0.5f * (2.0f * value2.x + (-value1.x + value3.x)* amount + (2.0f * value1.x - 5.0f * value2.x + 4.0f * value3.x - value4.x)* amountSquare + (-value1.x + 3.0f * value2.x - 3.0f * value3.x + value4.x)* amountCube);
	result.y = 0.5f * (2.0f * value2.y + (-value1.y + value3.y)* amount + (2.0f * value1.y - 5.0f * value2.y + 4.0f * value3.y - value4.y)* amountSquare + (-value1.y + 3.0f * value2.y - 3.0f * value3.y + value4.y)* amountCube);

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	에르미트 보간
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::Hermite(const Vector2 & value1, const Vector2 & tangent1, const Vector2 & value2, const Vector2 & tangent2, float amount)
{
	float amountSquare = amount * amount;
	float amountCube = amount * amountSquare;

	float f1 = (2.0f * amountCube - 3.0f * amountSquare + 1.0f);
	float f2 = (-2.0f * amountCube + 3.0f * amountSquare);
	float f3 = amountCube - 2.0f * amountSquare + amount;
	float f4 = amountCube - amountSquare;

	Vector2 result;
	result.x = value1.x * f1 + value2.x * f2 + tangent1.x * f3 + tangent2.x * f4;
	result.y = value1.y * f1 + value2.y * f2 + tangent1.y * f3 + tangent2.y * f4;

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	메트릭스에 의해 변환된 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::Transform(const Vector2 & position, const Matrix & matrix)
{
	float f1 = (position.x * matrix.m_11 + position.y * matrix.m_21) + matrix.m_41;
	float f2 = (position.x * matrix.m_12 + position.y * matrix.m_22) + matrix.m_42;

	Vector2 vector2;
	vector2.x = f1;
	vector2.y = f2;
	
	return vector2;
}

///////////////////////////////////////////////////////////////////////////////
//	쿼터니언에 의해 변환된 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::Transform(const Vector2 & value, const Quaternion & rotation)
{
	float f1 = rotation.x + rotation.x;
	float f2 = rotation.y + rotation.y;
	float f3 = rotation.z + rotation.z;

	float f4 = rotation.w * f3;
	float f5 = rotation.x * f1;
	float f6 = rotation.x * f2;
	float f7 = rotation.y * f2;
	float f8 = rotation.z * f3;

	float f9 = (value.x * (1.0f - f7 - f8) + value.y * (f6 - f4));
	float f10 = (value.x * (f6 + f4) + value.y * (1.0f - f5 - f8));

	Vector2 vector2;
	vector2.x = f9;
	vector2.y = f10;

	return vector2;
}

///////////////////////////////////////////////////////////////////////////////
//	메트릭스에 의해 변환된 방향 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector2 Vector2::TransformNormal(const Vector2 & normal, const Matrix & matrix)
{
	float f1 = (normal.x * matrix.m_11 + normal.y * matrix.m_21);
	float f2 = (normal.x * matrix.m_12 + normal.y * matrix.m_22);

	Vector2 vector2;
	vector2.x = f1;
	vector2.y = f2;

	return vector2;
}

///////////////////////////////////////////////////////////////////////////////

