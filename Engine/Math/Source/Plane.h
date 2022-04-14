#pragma once

#include "../Math/Source/Vector3.h"
#include "../Math/Source/Vector4.h"

struct D3DXPLANE;
class Matrix;
class Quaternion;

class Plane
{
public:

	///////////////////////////////////////////////////////////////////////////
	///	������ / ���� , �̵�

	explicit Plane(float a = 0.0f, float b = 0.0f, float c = 0.0f, float d = 0.0f) noexcept;
	explicit Plane(const Vector3& normal, float d) noexcept;
	explicit Plane(const Vector4& value) noexcept;

	///////////////////////////////////////////////////////////////////////////////
	//@(left_top)
	//l
	//(up vector)
	//l
	//@(center)----(right vector)---@(right_bottom)
	//Normal(a,b,c) = Forward Vector (ȭ�� �������� ���� ����)
	///////////////////////////////////////////////////////////////////////////////
	explicit Plane(const Vector3& point_center, const Vector3& point_left_top, const Vector3& point_right_bottom) noexcept;

	Plane(const Plane& other) noexcept;
	Plane(Plane&& other) noexcept;
	///////////////////////////////////////////////////////////////////////////

	inline float& operator[](unsigned int index) noexcept
	{
		return m[index];
	}


	inline Plane operator =(const Plane& other) noexcept
	{
		memcpy(this, &other, sizeof(other));
		return *this;
	}

	inline bool operator ==(const Plane& other) const noexcept
	{
		return ((a == other.a) && (b == other.b) && (c == other.c) && (d == other.d));
	}

	inline bool operator !=(const Plane& other) const noexcept
	{
		return ((a != other.a) || (b != other.b) || (c != other.c) || (d != other.d));
	}

	//	��ȯ
	operator float*() const noexcept;

	//	������

	///////////////////////////////////////////////////////////////////////////////
	//	�÷����� ������ String���� ��ȯ�մϴ�.
	///////////////////////////////////////////////////////////////////////////////
	std::string ToString();

	///////////////////////////////////////////////////////////////////////////////
	//	�÷����� ������ Wstring���� ��ȯ�մϴ�.
	///////////////////////////////////////////////////////////////////////////////
	std::wstring ToStringW();

	///////////////////////////////////////////////////////////////////////////////
	//	Plane�� D3DXPLANE ���� ��ȯ�մϴ�.
	///////////////////////////////////////////////////////////////////////////////
	D3DXPLANE ToD3DXPLANE();


	///////////////////////////////////////////////////////////////////////////////
	//	�÷����� ����ȭ�մϴ�.
	///////////////////////////////////////////////////////////////////////////////
	const Plane& Normalize();

	///////////////////////////////////////////////////////////////////////////////
	//	Plane�� Vector4�� ������ŵ�ϴ�.
	///////////////////////////////////////////////////////////////////////////////
	float Dot(const Vector4& value);

	///////////////////////////////////////////////////////////////////////////////
	//	Plane�� Vector3(��ġ) �� ������ŵ�ϴ�. ( ����� d || d > 0 : Plane�� �� | d < 0 : Plane�� �� | d == 0 : Plane�� ��ħ )
	///////////////////////////////////////////////////////////////////////////////
	float DotCoordinate(const Vector3& value);

	///////////////////////////////////////////////////////////////////////////////
	//	Plane�� Vector3(����) �� ������ŵ�ϴ�. (�Ϲ� Vector3 ������ �����ϴ�.)
	///////////////////////////////////////////////////////////////////////////////
	float DotNormal(const Vector3& value);


	///////////////////////////////////////////////////////////////////////////////
	//	�÷����� ����ȭ�մϴ�.
	///////////////////////////////////////////////////////////////////////////////
	static Plane Normalize(const Plane& value);
	
	///////////////////////////////////////////////////////////////////////////////
	//	��Ʈ������ �÷����� ��ȯ��ŵ�ϴ�.
	///////////////////////////////////////////////////////////////////////////////
	static Plane Transform(const Plane& plane, const Matrix& matrix);
	
	///////////////////////////////////////////////////////////////////////////////
	//	���ʹϾ����� �÷����� ��ȯ��ŵ�ϴ�.
	///////////////////////////////////////////////////////////////////////////////
	static Plane Transform(const Plane& plane, const Quaternion& rotation);

public:


	///////////////////////////////////////////////////////////////////////////
	///	X , Y , Z , W
	union
	{
		float m[4];
		Vector4 vector4;

		struct
		{
			union
			{
				Vector3 normal;

				struct
				{
					float a, b, c;
				};
			};

			float d;
		};
	};
	///////////////////////////////////////////////////////////////////////////

};