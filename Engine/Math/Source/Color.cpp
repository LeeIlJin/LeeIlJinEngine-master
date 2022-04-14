#include <Windows.h>
#include <math.h>
//
#include "Color.h"

#include "Vector3.h"
#include "Vector4.h"

//
#include <d3dx9math.h>


///////////////////////////////////////////////////////////////////////////////

const Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);

const Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);

const Color Color::Cyan = Color(0.0f, 1.0f, 1.0f, 1.0f);
const Color Color::Yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
const Color Color::Magenta = Color(1.0f, 0.0f, 1.0f, 1.0f);

///////////////////////////////////////////////////////////////////////////////

Color::Color(float r, float g, float b, float a) noexcept
	:r(r), g(g), b(b), a(a)
{
	//	Empty
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) noexcept
{
	const float f = 1.0f / 255.0f;

	this->r = (float)r * f;
	this->g = (float)g * f;
	this->b = (float)b * f;
	this->a = (float)a * f;
}

Color::Color(unsigned int decimal) noexcept
{
	CONST FLOAT f = 1.0f / 255.0f;
	r = f * (FLOAT)(unsigned char)(decimal >> 16);
	g = f * (FLOAT)(unsigned char)(decimal >> 8);
	b = f * (FLOAT)(unsigned char)(decimal >> 0);
	a = f * (FLOAT)(unsigned char)(decimal >> 24);
}

Color::Color(const Vector4 & vector4) noexcept
	: r(vector4.x), g(vector4.y), b(vector4.z), a(vector4.w)
{
	//	Empty
}

Color::Color(const Vector3 & vector3, float a) noexcept
	: r(vector3.x), g(vector3.y), b(vector3.z), a(a)
{
	//	Empty
}

Color::Color(const Color & other) noexcept
{
	memcpy(this, &other, sizeof(other));
}

Color::Color(Color && other) noexcept
{
	memcpy(this, &other, sizeof(other));
	ZeroMemory(&other, sizeof(other));
}

///////////////////////////////////////////////////////////////////////////////

//	float* 변환
Color::operator float*() const noexcept
{
	return (float*)m;
}

//	UINT 변환
Color::operator unsigned int() const noexcept
{
	unsigned int result(0);

	result = ((unsigned int)((255.0f * a)) << 24)
		+ ((unsigned int)((255.0f * b)) << 16)
		+ ((unsigned int)((255.0f * g)) << 8)
		+ ((unsigned int)((255.0f * r)) << 0);

	return result;
}

Color::operator Vector4() const noexcept
{
	return Vector4(r, g, b, a);
}

Color::operator Vector3() const noexcept
{
	return Vector3(r, g, b);
}

///////////////////////////////////////////////////////////////////////////////

Color Color::operator+(const Color & other) const noexcept
{
	return Color(r + other.r, g + other.g, b + other.b, a + other.a);
}

Color Color::operator+(const float & other) const noexcept
{
	return Color(r + other, g + other, b + other, a + other);
}

Color Color::operator-(const Color & other) const noexcept
{
	return Color(r - other.r, g - other.g, b - other.b, a - other.a);
}

Color Color::operator-(const float & other) const noexcept
{
	return Color(r - other, g - other, b - other, a - other);
}

Color Color::operator*(const Color & other) const noexcept
{
	return Color(r * other.r, g * other.g, b * other.b, a * other.a);
}

Color Color::operator*(const float & other) const noexcept
{
	return Color(r * other, g * other, b * other, a * other);
}

Color Color::operator/(const Color & other) const noexcept
{
	return Color(r / other.r, g / other.g, b / other.b, a / other.a);
}

Color Color::operator/(const float & other) const noexcept
{
	return Color(r / other, g / other, b / other, a / other);
}

Color Color::operator%(const Color & other) const noexcept
{
	Color vec(fabsf(other.r), fabsf(other.g), fabsf(other.b), fabsf(other.a));
	Color result(fabsf(r), fabsf(g), fabsf(b), fabsf(a));
	while (result.r >= vec.r)
		result.r -= vec.r;
	while (result.g >= vec.g)
		result.g -= vec.g;
	while (result.b >= vec.b)
		result.b -= vec.b;
	while (result.a >= vec.a)
		result.a -= vec.a;

	if (r < 0.0f)
		result.r *= -1.0f;
	if (g < 0.0f)
		result.g *= -1.0f;
	if (b < 0.0f)
		result.b *= -1.0f;
	if (a < 0.0f)
		result.a *= -1.0f;

	return result;
}

Color Color::operator%(const float & other) const noexcept
{
	float f(fabsf(other));
	Color result(fabsf(r), fabsf(g), fabsf(b), fabsf(a));
	while (result.r >= f)
		result.r -= f;
	while (result.g >= f)
		result.g -= f;
	while (result.b >= f)
		result.b -= f;
	while (result.a >= f)
		result.a -= f;

	if (r < 0.0f)
		result.r *= -1.0f;
	if (g < 0.0f)
		result.g *= -1.0f;
	if (b < 0.0f)
		result.b *= -1.0f;
	if (a < 0.0f)
		result.a *= -1.0f;

	return result;
}

void Color::operator+=(const Color & other) noexcept
{
	r += other.r;
	g += other.g;
	b += other.b;
	a += other.a;
}

void Color::operator+=(const float & other) noexcept
{
	r += other;
	g += other;
	b += other;
	a += other;
}

void Color::operator-=(const Color & other) noexcept
{
	r -= other.r;
	g -= other.g;
	b -= other.b;
	a -= other.a;
}

void Color::operator-=(const float & other) noexcept
{
	r -= other;
	g -= other;
	b -= other;
	a -= other;
}

void Color::operator*=(const Color & other) noexcept
{
	r *= other.r;
	g *= other.g;
	b *= other.b;
	a *= other.a;
}

void Color::operator*=(const float & other) noexcept
{
	r *= other;
	g *= other;
	b *= other;
	a *= other;
}

void Color::operator/=(const Color & other) noexcept
{
	r /= other.r;
	g /= other.g;
	b /= other.b;
	a /= other.a;
}

void Color::operator/=(const float & other) noexcept
{
	r /= other;
	g /= other;
	b /= other;
	a /= other;
}

void Color::operator%=(const Color & other) noexcept
{
	*this = *this % other;
}

void Color::operator%=(const float & other) noexcept
{
	*this = *this % other;
}

///////////////////////////////////////////////////////////////////////////////


std::string Color::ToString()
{
	std::string temp;
	char val[255];

	sprintf_s(val, "{R:%#f ", r); temp += val;
	sprintf_s(val, "G:%#f ", g); temp += val;
	sprintf_s(val, "B:%#f ", b); temp += val;
	sprintf_s(val, "A:%#f}", a); temp += val;

	return temp;
}

std::wstring Color::ToStringW()
{
	std::wstring temp;
	wchar_t val[255];

	wprintf_s(val, L"{R:%#f ", r); temp += val;
	wprintf_s(val, L"G:%#f ", g); temp += val;
	wprintf_s(val, L"B:%#f ", b); temp += val;
	wprintf_s(val, L"A:%#f}", a); temp += val;

	return temp;
}

D3DXCOLOR Color::ToD3DXCOLOR()
{
	return D3DXCOLOR(r, g, b, a);
}

unsigned int Color::ToUINT() noexcept
{
	unsigned int result(0);

	result = ((unsigned int)((255.0f * a)) << 24)
		+ ((unsigned int)((255.0f * b)) << 16)
		+ ((unsigned int)((255.0f * g)) << 8)
		+ ((unsigned int)((255.0f * r)) << 0);

	return result;
}

void Color::ToBytes(unsigned char *& out_bytes) noexcept
{
	for (unsigned int i = 0; i < 4; i++)
		out_bytes[i] = (unsigned char)(m[i] * 255.0f);
}
