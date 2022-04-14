#pragma once

#include <string>

struct D3DXCOLOR;

class Vector4;
class Vector3;

class Color
{
public:

	///////////////////////////////////////////////////////////////////////////
	///	생성자 / 복사 , 이동
	explicit Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f) noexcept;
	explicit Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) noexcept;
	explicit Color(unsigned int decimal) noexcept;
	explicit Color(const Vector4& vector4) noexcept;
	explicit Color(const Vector3& vector3, float a) noexcept;

	Color(const Color& other) noexcept;
	Color(Color&& other) noexcept;
	///////////////////////////////////////////////////////////////////////////

	inline float& operator[](unsigned int index) noexcept
	{
		return m[index];
	}


	inline Color operator =(const Color& other) noexcept
	{
		memcpy(this, &other, sizeof(other));
		return *this;
	}

	inline Color operator -() noexcept
	{
		return Color(-r, -g, -b, -a);
	}

	inline bool operator ==(const Color& other) const noexcept
	{
		return ((r == other.r) && (g == other.g) && (b == other.b) && (a == other.a));
	}

	inline bool operator !=(const Color& other) const noexcept
	{
		return ((r != other.r) || (g != other.g) || (b != other.b) || (a != other.a));
	}

	//	변환
	operator float*() const noexcept;
	operator unsigned int() const noexcept;
	operator Vector4() const noexcept;
	operator Vector3() const noexcept;

	//	연산자

	Color operator +(const Color& other) const noexcept;
	Color operator +(const float& other) const noexcept;
	Color operator -(const Color& other) const noexcept;
	Color operator -(const float& other) const noexcept;
	Color operator *(const Color& other) const noexcept;
	Color operator *(const float& other) const noexcept;
	Color operator /(const Color& other) const noexcept;
	Color operator /(const float& other) const noexcept;
	Color operator %(const Color& other) const noexcept;
	Color operator %(const float& other) const noexcept;

	void operator +=(const Color& other) noexcept;
	void operator +=(const float& other) noexcept;
	void operator -=(const Color& other) noexcept;
	void operator -=(const float& other) noexcept;
	void operator *=(const Color& other) noexcept;
	void operator *=(const float& other) noexcept;
	void operator /=(const Color& other) noexcept;
	void operator /=(const float& other) noexcept;
	void operator %=(const Color& other) noexcept;
	void operator %=(const float& other) noexcept;


	friend Color operator +(const float& factor, const Color& other)
	{
		return other + factor;
	}
	friend Color operator *(const float& factor, const Color& other)
	{
		return other * factor;
	}

	///////////////////////////////////////////////////////////////////////////

	std::string ToString();
	std::wstring ToStringW();
	D3DXCOLOR ToD3DXCOLOR();

	unsigned int ToUINT() noexcept;
	void ToBytes(unsigned char *& out_bytes) noexcept;

	///////////////////////////////////////////////////////////////////////////
public:
	const static Color Black;
	const static Color White;

	const static Color Red;
	const static Color Green;
	const static Color Blue;

	const static Color Cyan;
	const static Color Yellow;
	const static Color Magenta;


	///////////////////////////////////////////////////////////////////////////
	///	X , Y , Z , W  ||  R , G , B , A
	union
	{
		float m[4];
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
	};
	///////////////////////////////////////////////////////////////////////////

};