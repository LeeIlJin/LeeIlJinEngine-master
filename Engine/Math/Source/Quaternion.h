#pragma once

#include <string>

struct D3DXQUATERNION;
class Vector3;
class Matrix;

class Quaternion
{
public:
	explicit Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) noexcept;
	explicit Quaternion(Vector3 vectorPart, float scalarPart) noexcept;
	Quaternion(const Quaternion& other) noexcept;
	Quaternion(Quaternion&& other) noexcept;

	//
	inline float& operator[](unsigned int index) noexcept
	{
		return m[index];
	}


	inline Quaternion operator =(const Quaternion& other) noexcept
	{
		memcpy(this, &other, sizeof(other));
		return *this;
	}

	inline Quaternion operator -() noexcept
	{
		return Quaternion(-x, -y, -z);
	}

	inline bool operator ==(const Quaternion& other) const noexcept
	{
		return ((x == other.x) && (y == other.y) && (z == other.z));
	}

	inline bool operator !=(const Quaternion& other) const noexcept
	{
		return ((x != other.x) || (y != other.y) || (z != other.z));
	}

	//	변환
	operator float*() const noexcept;

	//	연산자

	Quaternion operator +(const Quaternion& other) const noexcept;
	Quaternion operator +(const float& other) const noexcept;
	Quaternion operator -(const Quaternion& other) const noexcept;
	Quaternion operator -(const float& other) const noexcept;
	Quaternion operator *(const Quaternion& other) const noexcept;
	Quaternion operator *(const float& other) const noexcept;
	Quaternion operator /(const Quaternion& other) const noexcept;

	void operator +=(const Quaternion& other) noexcept;
	void operator +=(const float& other) noexcept;
	void operator -=(const Quaternion& other) noexcept;
	void operator -=(const float& other) noexcept;
	void operator *=(const Quaternion& other) noexcept;
	void operator *=(const float& other) noexcept;
	void operator /=(const Quaternion& other) noexcept;


	friend Quaternion operator +(const float& factor, const Quaternion& other)
	{
		return other + factor;
	}
	friend Quaternion operator *(const float& factor, const Quaternion& other)
	{
		return other * factor;
	}

	///////////////////////////////////////////////////////////////////////////

	std::string ToString();
	std::wstring ToStringW();
	D3DXQUATERNION ToD3DXQUATERNION();

	float Length();
	float LengthSquared();

	const Quaternion& Normalize();
	const Quaternion& Conjugate();
	const Quaternion& Inverse();

	inline void SetFromAxisAngle(const Vector3& axis, float angle) { *this = Quaternion::CreateFromAxisAngle(axis, angle); }
	inline void SetYawPitchRoll(float yaw, float pitch, float roll) { *this = Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll); }
	inline void SetFromMatrix(const Matrix& matrix) { *this = Quaternion::CreateFromMatrix(matrix); }

	inline float Dot(const Quaternion& quaternion) { return Quaternion::Dot(*this, quaternion); }

	static Quaternion Normalize(const Quaternion& quaternion);
	static Quaternion Conjugate(const Quaternion& quaternion);
	static Quaternion Inverse(const Quaternion& quaternion);

	static Quaternion CreateFromAxisAngle(const Vector3& axis, float angle);
	static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	static Quaternion CreateFromMatrix(const Matrix& matrix);

	static float Dot(const Quaternion& quaternion1, const Quaternion& quaternion2);

	static Quaternion Slerp(const Quaternion& quaternion1, const Quaternion& quaternion2, float amount);
	static Quaternion Lerp(const Quaternion& quaternion1, const Quaternion& quaternion2, float amount);

	//	회전을 연결합니다. quaternion1 회전을 한 후, quaternion2 회전을 더합니다.
	static Quaternion Concatenate(const Quaternion& quaternion1, const Quaternion& quaternion2);

public:
	const static Quaternion Identity;

	///////////////////////////////////////////////////////////////////////////
	///	X , Y , Z
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

