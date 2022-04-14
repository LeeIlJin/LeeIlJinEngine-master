#pragma once

#include <string>

struct D3DXVECTOR4;
class Vector2;
class Vector3;
class Matrix;
class Quaternion;

class Vector4
{
public:

	///////////////////////////////////////////////////////////////////////////
	///	생성자 / 복사 , 이동
	explicit Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) noexcept;
	explicit Vector4(const Vector2& vec2_xy, const Vector2& vec2_zw) noexcept;
	explicit Vector4(const Vector3& vec3_xyz, float w = 0.0f) noexcept;
	Vector4(const Vector4& other) noexcept;
	Vector4(Vector4&& other) noexcept;
	///////////////////////////////////////////////////////////////////////////

	inline float& operator[](unsigned int index) noexcept
	{
		return m[index];
	}


	inline Vector4 operator =(const Vector4& other) noexcept
	{
		memcpy(this, &other, sizeof(other));
		return *this;
	}

	inline Vector4 operator -() noexcept
	{
		return Vector4(-x, -y, -z, -w);
	}

	inline bool operator ==(const Vector4& other) const noexcept
	{
		return ((x == other.x) && (y == other.y) && (z == other.z) && (w == other.w));
	}

	inline bool operator !=(const Vector4& other) const noexcept
	{
		return ((x != other.x) || (y != other.y) || (z != other.z) || (w != other.w));
	}

	//	변환
	operator float*() const noexcept;

	//	연산자

	Vector4 operator +(const Vector4& other) const noexcept;
	Vector4 operator +(const float& other) const noexcept;
	Vector4 operator -(const Vector4& other) const noexcept;
	Vector4 operator -(const float& other) const noexcept;
	Vector4 operator *(const Vector4& other) const noexcept;
	Vector4 operator *(const float& other) const noexcept;
	Vector4 operator /(const Vector4& other) const noexcept;
	Vector4 operator /(const float& other) const noexcept;
	Vector4 operator %(const Vector4& other) const noexcept;
	Vector4 operator %(const float& other) const noexcept;

	void operator +=(const Vector4& other) noexcept;
	void operator +=(const float& other) noexcept;
	void operator -=(const Vector4& other) noexcept;
	void operator -=(const float& other) noexcept;
	void operator *=(const Vector4& other) noexcept;
	void operator *=(const float& other) noexcept;
	void operator /=(const Vector4& other) noexcept;
	void operator /=(const float& other) noexcept;
	void operator %=(const Vector4& other) noexcept;
	void operator %=(const float& other) noexcept;

	friend Vector4 operator +(const float& factor, const Vector4& other)
	{
		return other + factor;
	}
	friend Vector4 operator *(const float& factor, const Vector4& other)
	{
		return other * factor;
	}

	///////////////////////////////////////////////////////////////////////////

	std::string ToString();
	std::wstring ToStringW();
	D3DXVECTOR4 ToD3DXVECTOR4();

	float Length();
	float LengthSquared();

	const Vector4& Normalize();

	inline float Dot(const Vector4& value) { return Vector4::Dot(*this, value); }

	///////////////////////////////////////////////////////////////////////////

	static float Distance(const Vector4& position1, const Vector4& position2);
	static float DistanceSquared(const Vector4& position1, const Vector4& position2);

	static float Dot(const Vector4& value1, const Vector4& value2);
	static Vector4 Normalize(const Vector4& value);

	static Vector4 Min(const Vector4& value1, const Vector4& value2);
	static Vector4 Max(const Vector4& value1, const Vector4& value2);
	static Vector4 Clamp(const Vector4& value1, const Vector4& min, const Vector4& max);
	static Vector4 Clamp01(const Vector4& value1);

	static Vector4 Lerp(const Vector4& value1, const Vector4& value2, float amount);
	static Vector4 SmoothStep(const Vector4& value1, const Vector4& value2, float amount);
	static Vector4 CatmullRom(const Vector4& value1, const Vector4& value2, const Vector4& value3, const Vector4& value4, float amount);
	static Vector4 Hermite(const Vector4& value1, const Vector4& tangent1, const Vector4& value2, const Vector4& tangent2, float amount);

	static Vector4 Transform(const Vector2& position, const Matrix& matrix);
	static Vector4 Transform(const Vector3& position, const Matrix& matrix);
	static Vector4 Transform(const Vector4& position, const Matrix& matrix);
	static Vector4 Transform(const Vector2& value, const Quaternion& rotation);
	static Vector4 Transform(const Vector3& value, const Quaternion& rotation);
	static Vector4 Transform(const Vector4& value, const Quaternion& rotation);

public:
	const static Vector4 Zero;
	const static Vector4 One;
	
	const static Vector4 UnitX;
	const static Vector4 UnitY;
	const static Vector4 UnitZ;
	const static Vector4 UnitW;

	///////////////////////////////////////////////////////////////////////////
	///	X , Y , Z , W
	union
	{
		float m[4];
		struct
		{
			float x, y, z, w;
		};
	};
	///////////////////////////////////////////////////////////////////////////
};
