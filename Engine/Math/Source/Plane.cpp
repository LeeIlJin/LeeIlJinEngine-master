#include <Windows.h>
#include <math.h>
//
#include "Plane.h"

//
#include <d3dx9math.h>

#include "Matrix.h"
#include "Quaternion.h"



///////////////////////////////////////////////////////////////////////////////

Plane::Plane(float a, float b, float c, float d) noexcept
	:a(a), b(b), c(c), d(d)
{
	//	Empty
}

Plane::Plane(const Vector3& normal, float d) noexcept
	: normal(normal), d(d)
{
	//	Empty
}

Plane::Plane(const Vector4& value) noexcept
	: a(value.x), b(value.y), c(value.z), d(value.w)
{
	//	Empty
}

///////////////////////////////////////////////////////////////////////////////
//@(left_top)
//l
//(up vector)
//l
//@(center)----(right vector)---@(right_bottom)
//Normal(a,b,c) = Forward Vector (ȭ�� �������� ���� ����)
///////////////////////////////////////////////////////////////////////////////
Plane::Plane(const Vector3& point_center, const Vector3& point_left_top, const Vector3& point_right_bottom) noexcept
{
	Vector3 up = point_left_top - point_center;
	Vector3 right = point_right_bottom - point_center;

	Vector3 forward = right.Cross(up);
	float len = 1.0f / sqrt(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z);

	this->normal = forward * len;
	this->d = -(this->a * point_center.x + this->b * point_center.y + this->c * point_center.z);
}

Plane::Plane(const Plane & other) noexcept
{
	memcpy(this, &other, sizeof(other));
}

Plane::Plane(Plane && other) noexcept
{
	memcpy(this, &other, sizeof(other));
	ZeroMemory(&other, sizeof(other));
}

///////////////////////////////////////////////////////////////////////////////

Plane::operator float*() const noexcept
{
	return (float*)m;
}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//	�÷����� ������ String���� ��ȯ�մϴ�.
///////////////////////////////////////////////////////////////////////////////
std::string Plane::ToString()
{
	std::string temp;
	char val[255];

	temp += "{Normal:" + normal.ToString();
	sprintf_s(val, " D:%#f}", d); temp += val;

	return temp;
}

///////////////////////////////////////////////////////////////////////////////
//	�÷����� ������ Wstring���� ��ȯ�մϴ�.
///////////////////////////////////////////////////////////////////////////////
std::wstring Plane::ToStringW()
{
	std::wstring temp;
	wchar_t val[255];

	temp += L"{Normal:" + normal.ToStringW();
	wprintf_s(val, L" D:%#f}", d); temp += val;

	return temp;
}

///////////////////////////////////////////////////////////////////////////////
//	Plane�� D3DXPLANE ���� ��ȯ�մϴ�.
///////////////////////////////////////////////////////////////////////////////
D3DXPLANE Plane::ToD3DXPLANE()
{
	return D3DXPLANE(a, b, c, d);
}

///////////////////////////////////////////////////////////////////////////////
//	�÷����� ����ȭ�մϴ�.
///////////////////////////////////////////////////////////////////////////////
const Plane& Plane::Normalize()
{
	float f1 = (normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
	float f2 = f1 - 1.0f;

	float _abs_f2 = (f2 >= 0) ? f2 : -f2;

	if (_abs_f2 >= 1.19209289550781E-07f)
	{
		float f3 = 1.0f / sqrtf(f1);
		normal.x *= f3;
		normal.y *= f3;
		normal.z *= f3;
		d *= f3;
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//	Plane�� Vector4�� ������ŵ�ϴ�.
///////////////////////////////////////////////////////////////////////////////
float Plane::Dot(const Vector4 & value)
{
	return Vector4::Dot(vector4, value);
}

///////////////////////////////////////////////////////////////////////////////
//	Plane�� Vector3(��ġ) �� ������ŵ�ϴ�. ( ����� d || d > 0 : Plane�� �� | d < 0 : Plane�� �� | d == 0 : Plane�� ��ħ )
///////////////////////////////////////////////////////////////////////////////
float Plane::DotCoordinate(const Vector3 & value)
{
	return Vector3::Dot(normal, value) + d;
}

///////////////////////////////////////////////////////////////////////////////
//	Plane�� Vector3(����) �� ������ŵ�ϴ�. (�Ϲ� Vector3 ������ �����ϴ�.)
///////////////////////////////////////////////////////////////////////////////
float Plane::DotNormal(const Vector3 & value)
{
	return Vector3::Dot(normal, value);
}

///////////////////////////////////////////////////////////////////////////////
//	�÷����� ����ȭ�մϴ�.
///////////////////////////////////////////////////////////////////////////////
Plane Plane::Normalize(const Plane & value)
{
	float f1 = (value.normal.x * value.normal.x + value.normal.y * value.normal.y + value.normal.z * value.normal.z);
	float f2 = f1 - 1.0f;

	float _abs_f2 = (f2 >= 0) ? f2 : -f2;

	if (_abs_f2 < 1.19209289550781E-07f)
	{
		return Plane(value);
	}
	else
	{
		float f3 = 1.0f / (float)sqrt((double)f1);

		return Plane(value.normal * f3, value.d * f3);
	}
}

///////////////////////////////////////////////////////////////////////////////
//	��Ʈ������ �÷����� ��ȯ��ŵ�ϴ�.
///////////////////////////////////////////////////////////////////////////////
Plane Plane::Transform(const Plane & plane, const Matrix & matrix)
{
	Matrix invMat;
	invMat = Matrix::Invert(matrix);

	Plane result;
	result.normal.x = (float)(plane.normal.x * invMat.m_11 + plane.normal.y * invMat.m_12 + plane.normal.z * invMat.m_13 + plane.d * invMat.m_14);
	result.normal.y = (float)(plane.normal.x * invMat.m_21 + plane.normal.y * invMat.m_22 + plane.normal.z * invMat.m_23 + plane.d * invMat.m_24);
	result.normal.z = (float)(plane.normal.x * invMat.m_31 + plane.normal.y * invMat.m_32 + plane.normal.z * invMat.m_33 + plane.d * invMat.m_34);
	result.d = (float)(plane.normal.x * invMat.m_41 + plane.normal.y * invMat.m_42 + plane.normal.z * invMat.m_43 + plane.d * invMat.m_44);

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//	���ʹϾ����� �÷����� ��ȯ��ŵ�ϴ�.
///////////////////////////////////////////////////////////////////////////////
Plane Plane::Transform(const Plane & plane, const Quaternion & rotation)
{
	float wxx = rotation.w * (rotation.x + rotation.x);
	float wyy = rotation.w * (rotation.y + rotation.y);
	float wzz = rotation.w * (rotation.z + rotation.z);

	float xxx = rotation.x * (rotation.x + rotation.x);
	float xyy = rotation.x * (rotation.y + rotation.y);
	float xzz = rotation.x * (rotation.z + rotation.z);

	float yyy = rotation.y * (rotation.y + rotation.y);
	float yzz = rotation.y * (rotation.z + rotation.z);
	float zzz = rotation.z * (rotation.z + rotation.z);

	float f1 = 1.0f - yyy - zzz;
	float f2 = xyy - wzz;
	float f3 = xzz + wyy;
	float f4 = xyy + wzz;

	float f5 = 1.0f - xxx - zzz;
	float f6 = yzz - wxx;
	float f7 = xzz - wyy;
	float f8 = yzz + wxx;

	float f9 = 1.0f - xxx - yyy;
	float f10 = plane.normal.x;
	float f11 = plane.normal.y;
	float f12 = plane.normal.z;

	Plane result;
	result.normal.x = (float)(f10 * f1 + f11 * f2 + f12 * f3);
	result.normal.y = (float)(f10 * f4 + f11 * f5 + f12 * f6);
	result.normal.z = (float)(f10 * f7 + f11 * f8 + f12 * f9);
	result.d = plane.d;

	return result;
}
