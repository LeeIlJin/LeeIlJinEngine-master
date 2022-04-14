#pragma once

#include <string>

struct D3DXVECTOR2;
class Matrix;
class Quaternion;

class Vector2
{
public:
	
	///////////////////////////////////////////////////////////////////////////
	///	생성자 / 복사 , 이동
	Vector2() noexcept;
	explicit Vector2(float x, float y) noexcept;
	Vector2(const Vector2& other) noexcept;
	Vector2(Vector2&& other) noexcept;
	///////////////////////////////////////////////////////////////////////////

	inline float& operator[](unsigned int index) noexcept
	{
		return m[index];
	}


	inline const Vector2& operator =(const Vector2& other) noexcept
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	inline Vector2 operator -() noexcept
	{
		return Vector2(-x, -y);
	}

	inline bool operator ==(const Vector2& other) const noexcept
	{
		return ((x == other.x) && (y == other.y));
	}

	inline bool operator !=(const Vector2& other) const noexcept
	{
		return ((x != other.x) || (y != other.y));
	}

	//	변환
	operator float*() const noexcept;

	//	연산자
	
	Vector2 operator +(const Vector2& other) const noexcept;
	Vector2 operator +(const float& other) const noexcept;
	Vector2 operator -(const Vector2& other) const noexcept;
	Vector2 operator -(const float& other) const noexcept;
	Vector2 operator *(const Vector2& other) const noexcept;
	Vector2 operator *(const float& other) const noexcept;
	Vector2 operator /(const Vector2& other) const noexcept;
	Vector2 operator /(const float& other) const noexcept;
	Vector2 operator %(const Vector2& other) const noexcept;
	Vector2 operator %(const float& other) const noexcept;

	void operator +=(const Vector2& other) noexcept;
	void operator +=(const float& other) noexcept;
	void operator -=(const Vector2& other) noexcept;
	void operator -=(const float& other) noexcept;
	void operator *=(const Vector2& other) noexcept;
	void operator *=(const float& other) noexcept;
	void operator /=(const Vector2& other) noexcept;
	void operator /=(const float& other) noexcept;
	void operator %=(const Vector2& other) noexcept;
	void operator %=(const float& other) noexcept;

	friend Vector2 operator +(const float& factor, const Vector2& other)
	{
		return other + factor;
	}
	friend Vector2 operator *(const float& factor, const Vector2& other)
	{
		return other * factor;
	}

	///////////////////////////////////////////////////////////////////////////

	std::string ToString();
	std::wstring ToStringW();
	D3DXVECTOR2 ToD3DXVECTOR2();

	float Length();
	float LengthSquared();

	const Vector2& Normalize();

	inline float Dot(const Vector2& value) { return Vector2::Dot(*this, value); }
	inline Vector2 Cross() { return Vector2::Cross(*this); }

	///////////////////////////////////////////////////////////////////////////

	static float Distance(const Vector2& position1, const Vector2& position2);
	static float DistanceSquared(const Vector2& position1, const Vector2& position2);

	static float Dot(const Vector2& value1, const Vector2& value2);
	static Vector2 Normalize(const Vector2& value);

	static Vector2 Cross(const Vector2& value);
	static Vector2 Reflect(const Vector2& vector, const Vector2& normal);

	static Vector2 Min(const Vector2& value1, const Vector2& value2);
	static Vector2 Max(const Vector2& value1, const Vector2& value2);
	static Vector2 Clamp(const Vector2& value1, const Vector2& min, const Vector2& max);
	static Vector2 Clamp01(const Vector2& value1);

	static Vector2 Lerp(const Vector2& value1, const Vector2& value2, float amount);
	static Vector2 SmoothStep(const Vector2& value1, const Vector2& value2, float amount);
	static Vector2 CatmullRom(const Vector2& value1, const Vector2& value2, const Vector2& value3, const Vector2& value4, float amount);
	static Vector2 Hermite(const Vector2& value1, const Vector2& tangent1, const Vector2& value2, const Vector2& tangent2, float amount);

	static Vector2 Transform(const Vector2& position, const Matrix& matrix);
	static Vector2 Transform(const Vector2& value, const Quaternion& rotation);
	static Vector2 TransformNormal(const Vector2& normal, const Matrix& matrix);

public:
	const static Vector2 Zero;
	const static Vector2 One;
	const static Vector2 Right;
	const static Vector2 Up;
	const static Vector2 Left;
	const static Vector2 Down;

	const static Vector2 UnitX;
	const static Vector2 UnitY;

	///////////////////////////////////////////////////////////////////////////
	///	X , Y
	union
	{
		float m[2];
		struct
		{
			float x, y;
		};
	};
	///////////////////////////////////////////////////////////////////////////
};