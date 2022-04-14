#include <math.h>
//
#include "Quaternion.h"

//
#include <d3dx9math.h>
#include "Vector3.h"
#include "Matrix.h"



///////////////////////////////////////////////////////////////////////////////

Quaternion::Quaternion(float x, float y, float z, float w) noexcept
	:x(x), y(y), z(z), w(w)
{
	//	Empty
}

Quaternion::Quaternion(Vector3 vectorPart, float scalarPart) noexcept
	: x(vectorPart.x), y(vectorPart.y), z(vectorPart.z), w(scalarPart)
{
	//	Empty
}

Quaternion::Quaternion(const Quaternion & other) noexcept
{
	memcpy(this, &other, sizeof(other));
}

Quaternion::Quaternion(Quaternion && other) noexcept
{
	memcpy(this, &other, sizeof(other));
	ZeroMemory(&other, sizeof(other));
}

///////////////////////////////////////////////////////////////////////////////

Quaternion::operator float*() const noexcept
{
	return (float*)m;
}

///////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::operator+(const Quaternion & other) const noexcept
{
	return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);
}

Quaternion Quaternion::operator+(const float & other) const noexcept
{
	return Quaternion(x + other, y + other, z + other, w + other);
}

Quaternion Quaternion::operator-(const Quaternion & other) const noexcept
{
	return Quaternion(x - other.x, y - other.y, z - other.z, w - other.w);
}

Quaternion Quaternion::operator-(const float & other) const noexcept
{
	return Quaternion(x - other, y - other, z - other, w - other);
}

Quaternion Quaternion::operator*(const Quaternion & other) const noexcept
{
	float f1 = (y * other.z - z * other.y);
	float f2 = (z * other.x - x * other.z);
	float f3 = (x * other.y - y * other.x);
	float f4 = (x * other.x + y * other.y + z * other.z);

	Quaternion result;
	result.x = (x * other.w + other.x * w) + f1;
	result.y = (y * other.w + other.y * w) + f2;
	result.z = (z * other.w + other.z * w) + f3;
	result.w = w * other.w - f4;

	return result;
}

Quaternion Quaternion::operator*(const float & other) const noexcept
{
	return Quaternion(x * other, y * other, z * other, w * other);
}

Quaternion Quaternion::operator/(const Quaternion & other) const noexcept
{
	float f1 = 1.0f / (other.x * other.x + other.y * other.y + other.z * other.z + other.w * other.w);
	float f2 = -other.x * f1;
	float f3 = -other.y * f1;
	float f4 = -other.z * f1;
	float f5 = other.w * f1;

	float multiple1 = (y * f4 - z * f3);
	float multiple2 = (z * f2 - x * f4);
	float multiple3 = (x * f3 - y * f2);
	float multiple4 = (x * f2 + y * f3 + z * f4);

	Quaternion result;
	result.x = (x * f5 + f2 * w) + multiple1;
	result.y = (y * f5 + f3 * w) + multiple2;
	result.z = (z * f5 + f4 * w) + multiple3;
	result.w = w * f5 - multiple4;

	return result;
}

void Quaternion::operator+=(const Quaternion & other) noexcept
{
	*this = *this + other;
}

void Quaternion::operator+=(const float & other) noexcept
{
	*this = *this + other;
}

void Quaternion::operator-=(const Quaternion & other) noexcept
{
	*this = *this - other;
}

void Quaternion::operator-=(const float & other) noexcept
{
	*this = *this - other;
}

void Quaternion::operator*=(const Quaternion & other) noexcept
{
	*this = *this * other;
}

void Quaternion::operator*=(const float & other) noexcept
{
	*this = *this * other;
}

void Quaternion::operator/=(const Quaternion & other) noexcept
{
	*this = *this / other;
}

///////////////////////////////////////////////////////////////////////////////


std::string Quaternion::ToString()
{
	std::string temp;
	char val[255];

	sprintf_s(val, "{X:%#f ", x); temp += val;
	sprintf_s(val, "Y:%#f ", y); temp += val;
	sprintf_s(val, "Z:%#f ", z); temp += val;
	sprintf_s(val, "W:%#f}", w); temp += val;

	return temp;
}

std::wstring Quaternion::ToStringW()
{
	std::wstring temp;
	wchar_t val[255];

	wprintf_s(val, L"{X:%#f ", x); temp += val;
	wprintf_s(val, L"Y:%#f ", y); temp += val;
	wprintf_s(val, L"Z:%#f ", z); temp += val;
	wprintf_s(val, L"W:%#f}", w); temp += val;

	return temp;
}

D3DXQUATERNION Quaternion::ToD3DXQUATERNION()
{
	return D3DXQUATERNION(x, y, z, w);
}

float Quaternion::Length()
{
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

float Quaternion::LengthSquared()
{
	return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;
}

const Quaternion & Quaternion::Normalize()
{
	float len = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);

	x /= len;
	y /= len;
	z /= len;
	w /= len;

	return *this;
}

const Quaternion & Quaternion::Conjugate()
{
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;

	return *this;
}

const Quaternion & Quaternion::Inverse()
{
	*this = Quaternion::Inverse(*this);
	return *this;
}


///////////////////////////////////////////////////////////////////////////////

Quaternion Quaternion::Normalize(const Quaternion & quaternion)
{
	float len = sqrtf(quaternion.x * quaternion.x + quaternion.y * quaternion.y + quaternion.z * quaternion.z + quaternion.w * quaternion.w);

	return Quaternion(quaternion.x / len, quaternion.y / len, quaternion.z / len, quaternion.w / len);
}

Quaternion Quaternion::Conjugate(const Quaternion & quaternion)
{
	return Quaternion(-quaternion.x, -quaternion.y, -quaternion.z, quaternion.w);
}

Quaternion Quaternion::Inverse(const Quaternion & quaternion)
{
	float len = (quaternion.x * quaternion.x + quaternion.y * quaternion.y + quaternion.z * quaternion.z + quaternion.w * quaternion.w);

	return Quaternion(-quaternion.x / len, -quaternion.y / len, -quaternion.z / len, quaternion.w / len);
}

Quaternion Quaternion::CreateFromAxisAngle(const Vector3 & axis, float angle)
{
	float sinValue = sinf(angle * 0.5f);
	float cosValue = cosf(angle * 0.5f);

	Quaternion quaternion;
	quaternion.x = axis.x * sinValue;
	quaternion.y = axis.y * sinValue;
	quaternion.z = axis.z * sinValue;
	quaternion.w = cosValue;

	return quaternion;
}

Quaternion Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
	float roll1 = roll * 0.5f;
	float roll2 = sinf(roll1);
	float roll3 = cosf(roll1);

	float pitch1 = pitch * 0.5f;
	float pitch2 = sinf(pitch1);
	float pitch3 = cosf(pitch1);

	float yaw1 = yaw * 0.5f;
	float yaw2 = sinf(yaw1);
	float yaw3 = cosf(yaw1);

	Quaternion result;
	result.x = (yaw3 * pitch2 * roll3 + yaw2 * pitch3 * roll2);
	result.y = (yaw2 * pitch3 * roll3 - yaw3 * pitch2 * roll2);
	result.z = (yaw3 * pitch3 * roll2 - yaw2 * pitch2 * roll3);
	result.w = (yaw3 * pitch3 * roll3 + yaw2 * pitch2 * roll2);

	return result;
}

Quaternion Quaternion::CreateFromMatrix(const Matrix & matrix)
{
	float f1 = matrix.m_11 + matrix.m_22 + matrix.m_33;

	Quaternion result;
	if (f1 > 0.0)
	{
		float f2 = sqrtf(f1 + 1.0f);
		result.w = f2 * 0.5f;

		float f3 = 0.5f / f2;
		result.x = (matrix.m_23 - matrix.m_32)* f3;
		result.y = (matrix.m_31 - matrix.m_13)* f3;
		result.z = (matrix.m_12 - matrix.m_21)* f3;
	}
	else if (matrix.m_11 >= matrix.m_22 && matrix.m_11 >= matrix.m_33)
	{
		float f2 = sqrtf(1.0f + matrix.m_11 - matrix.m_22 - matrix.m_33);

		float f3 = 0.5f / f2;
		result.x = 0.5f * f2;
		result.y = (matrix.m_12 + matrix.m_21)* f3;
		result.z = (matrix.m_13 + matrix.m_31)* f3;
		result.w = (matrix.m_23 - matrix.m_32)* f3;
	}
	else if (matrix.m_22 > matrix.m_33)
	{
		float f2 = sqrtf(1.0f + matrix.m_22 - matrix.m_11 - matrix.m_33);

		float f3 = 0.5f / f2;
		result.x = (matrix.m_21 + matrix.m_12)* f3;
		result.y = 0.5f * f2;
		result.z = (matrix.m_32 + matrix.m_23)* f3;
		result.w = (matrix.m_31 - matrix.m_13)* f3;
	}
	else
	{
		float f2 = sqrtf(1.0f + matrix.m_33 - matrix.m_11 - matrix.m_22);

		float f3 = 0.5f / f2;
		result.x = (matrix.m_31 + matrix.m_13)* f3;
		result.y = (matrix.m_32 + matrix.m_23)* f3;
		result.z = 0.5f * f2;
		result.w = (matrix.m_12 - matrix.m_21)* f3;
	}

	return result;
}

float Quaternion::Dot(const Quaternion & quaternion1, const Quaternion & quaternion2)
{
	return quaternion1.x * quaternion2.x + quaternion1.y * quaternion2.y + quaternion1.z * quaternion2.z + quaternion1.w * quaternion2.w;
}

Quaternion Quaternion::Slerp(const Quaternion & quaternion1, const Quaternion & quaternion2, float amount)
{
	float d = quaternion1.x * quaternion2.x + quaternion1.y * quaternion2.y + quaternion1.z * quaternion2.z + quaternion1.w * quaternion2.w;

	bool flag = false;
	if (d < 0.0f)
	{
		flag = true;
		d = -d;
	}

	float f1, f2;
	if (d > 0.999998986721039f)
	{
		f1 = 1.0f - amount;
		f2 = flag ? -amount : amount;
	}
	else
	{
		float f3 = acosf(d);
		float f4 = (1.0f / sinf(f3));

		f1 = sinf((1.0f - amount)* f3)* f4;
		f2 = flag ? -sinf(amount * f3)* f4 : sinf(amount * f3)* f4;
	}
	Quaternion result;
	result.x = (f1 * quaternion1.x + f2 * quaternion2.x);
	result.y = (f1 * quaternion1.y + f2 * quaternion2.y);
	result.z = (f1 * quaternion1.z + f2 * quaternion2.z);
	result.w = (f1 * quaternion1.w + f2 * quaternion2.w);

	return result;
}

Quaternion Quaternion::Lerp(const Quaternion & quaternion1, const Quaternion & quaternion2, float amount)
{
	float amountInv = 1.0f - amount;
	Quaternion result;

	if (quaternion1.x * quaternion2.x + quaternion1.y * quaternion2.y + quaternion1.z * quaternion2.z + quaternion1.w * quaternion2.w >= 0.0)
	{
		result.x = (amountInv * quaternion1.x + amount * quaternion2.x);
		result.y = (amountInv * quaternion1.y + amount * quaternion2.y);
		result.z = (amountInv * quaternion1.z + amount * quaternion2.z);
		result.w = (amountInv * quaternion1.w + amount * quaternion2.w);
	}
	else
	{
		result.x = (amountInv * quaternion1.x - amount * quaternion2.x);
		result.y = (amountInv * quaternion1.y - amount * quaternion2.y);
		result.z = (amountInv * quaternion1.z - amount * quaternion2.z);
		result.w = (amountInv * quaternion1.w - amount * quaternion2.w);
	}

	float length = 1.0f / sqrtf(result.x * result.x + result.y * result.y + result.z * result.z + result.w * result.w);
	result.x *= length;
	result.y *= length;
	result.z *= length;
	result.w *= length;

	return result;
}

Quaternion Quaternion::Concatenate(const Quaternion & quaternion1, const Quaternion & quaternion2)
{
	float f1 = (quaternion2.y * quaternion1.z - quaternion2.z * quaternion1.y);
	float f2 = (quaternion2.z * quaternion1.x - quaternion2.x * quaternion1.z);
	float f3 = (quaternion2.x * quaternion1.y - quaternion2.y * quaternion1.x);
	float f4 = (quaternion2.x * quaternion1.x + quaternion2.y * quaternion1.y + quaternion2.z * quaternion1.z);

	Quaternion result;
	result.x = (quaternion2.x * quaternion1.w + quaternion1.x * quaternion2.w) + f1;
	result.y = (quaternion2.y * quaternion1.w + quaternion1.y * quaternion2.w) + f2;
	result.z = (quaternion2.z * quaternion1.w + quaternion1.z * quaternion2.w) + f3;
	result.w = quaternion2.w * quaternion1.w - f4;

	return result;
}

//