#pragma once

#include <string>

struct D3DXVECTOR3;
class Vector2;
class Matrix;
class Quaternion;

class Vector3
{
public:

	///////////////////////////////////////////////////////////////////////////
	///	생성자 / 복사 , 이동
	explicit Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) noexcept;
	explicit Vector3(const Vector2& vec2_xy, float z = 0.0f) noexcept;
	Vector3(const Vector3& other) noexcept;
	Vector3(Vector3&& other) noexcept;
	///////////////////////////////////////////////////////////////////////////

	inline float& operator[](unsigned int index) noexcept
	{
		return m[index];
	}


	inline Vector3 operator =(const Vector3& other) noexcept
	{
		memcpy(this, &other, sizeof(other));
		return *this;
	}

	inline Vector3 operator -() noexcept
	{
		return Vector3(-x, -y, -z);
	}

	inline bool operator ==(const Vector3& other) const noexcept
	{
		return ((x == other.x) && (y == other.y) && (z == other.z));
	}

	inline bool operator !=(const Vector3& other) const noexcept
	{
		return ((x != other.x) || (y != other.y) || (z != other.z));
	}

	//	변환
	operator float*() const noexcept;

	//	연산자

	Vector3 operator +(const Vector3& other) const noexcept;
	Vector3 operator +(const float& other) const noexcept;
	Vector3 operator -(const Vector3& other) const noexcept;
	Vector3 operator -(const float& other) const noexcept;
	Vector3 operator *(const Vector3& other) const noexcept;
	Vector3 operator *(const float& other) const noexcept;
	Vector3 operator /(const Vector3& other) const noexcept;
	Vector3 operator /(const float& other) const noexcept;
	Vector3 operator %(const Vector3& other) const noexcept;
	Vector3 operator %(const float& other) const noexcept;

	void operator +=(const Vector3& other) noexcept;
	void operator +=(const float& other) noexcept;
	void operator -=(const Vector3& other) noexcept;
	void operator -=(const float& other) noexcept;
	void operator *=(const Vector3& other) noexcept;
	void operator *=(const float& other) noexcept;
	void operator /=(const Vector3& other) noexcept;
	void operator /=(const float& other) noexcept;
	void operator %=(const Vector3& other) noexcept;
	void operator %=(const float& other) noexcept;

	friend Vector3 operator +(const float& factor, const Vector3& other)
	{
		return other + factor;
	}
	friend Vector3 operator *(const float& factor, const Vector3& other)
	{
		return other * factor;
	}

	///////////////////////////////////////////////////////////////////////////

	std::string ToString();
	std::wstring ToStringW();
	D3DXVECTOR3 ToD3DXVECTOR3();

	float Length();
	float LengthSquared();

	const Vector3& Normalize();

	inline float Dot(const Vector3& value) { return Vector3::Dot(*this, value); }
	inline Vector3 Cross(const Vector3& value) { return Vector3::Cross(*this, value); }

	///////////////////////////////////////////////////////////////////////////

	static float Distance(const Vector3& position1, const Vector3& position2);
	static float DistanceSquared(const Vector3& position1, const Vector3& position2);

	static float Dot(const Vector3& value1, const Vector3& value2);
	static Vector3 Normalize(const Vector3& value);

	static Vector3 Cross(const Vector3& value1, const Vector3& value2);
	static Vector3 Reflect(const Vector3& vector, const Vector3& normal);

	static Vector3 Min(const Vector3& value1, const Vector3& value2);
	static Vector3 Max(const Vector3& value1, const Vector3& value2);
	static Vector3 Clamp(const Vector3& value1, const Vector3& min, const Vector3& max);
	static Vector3 Clamp01(const Vector3& value1);

	static Vector3 Lerp(const Vector3& value1, const Vector3& value2, float amount);
	static Vector3 SmoothStep(const Vector3& value1, const Vector3& value2, float amount);
	static Vector3 CatmullRom(const Vector3& value1, const Vector3& value2, const Vector3& value3, const Vector3& value4, float amount);
	static Vector3 Hermite(const Vector3& value1, const Vector3& tangent1, const Vector3& value2, const Vector3& tangent2, float amount);

	static Vector3 Transform(const Vector3& position, const Matrix& matrix);
	static Vector3 Transform(const Vector3& value, const Quaternion& rotation);
	static Vector3 TransformNormal(const Vector3& normal, const Matrix& matrix);
	static Vector3 TransformCoord(const Vector3& position, const Matrix& matrix);

public:
	const static Vector3 Zero;
	const static Vector3 One;
	const static Vector3 Right;
	const static Vector3 Up;
	const static Vector3 Forward;
	const static Vector3 Left;
	const static Vector3 Down;
	const static Vector3 Backward;

	const static Vector3 UnitX;
	const static Vector3 UnitY;
	const static Vector3 UnitZ;

	///////////////////////////////////////////////////////////////////////////
	///	X , Y , Z
	union
	{
		float m[3];
		struct
		{
			float x, y, z;
		};
	};
	///////////////////////////////////////////////////////////////////////////
};

