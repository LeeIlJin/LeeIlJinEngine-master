#include <math.h>
//
#include "MathHelper.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Plane.h"

///////////////////////////////////////////////////////////////////////////////

const float MathHelper::E = 2.718282f;
const float MathHelper::Log2E = 1.442695f;
const float MathHelper::Log10E = 0.4342945f;
const float MathHelper::Pi = 3.141593f;
const float MathHelper::TwoPi = 6.283185f;
const float MathHelper::PiOver2 = 1.570796f;
const float MathHelper::PiOver4 = 0.7853982f;
const float MathHelper::Epsilon = 1E-6f;

const int MathHelper::IntMin = INT_MIN;
const int MathHelper::IntMax = INT_MAX;
const float MathHelper::FloatMin = FLT_MIN;
const float MathHelper::FloatMax = FLT_MAX;

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//	0번째 소수점 자리의 수를 반올림합니다. (0.n) -> (1.0 or 0.0)
///////////////////////////////////////////////////////////////////////////////
float MathHelper::Round(float value)
{
	return Round(value, 0);
}

///////////////////////////////////////////////////////////////////////////////
//	소수점 자리(position)의 수를 반올림합니다.
///////////////////////////////////////////////////////////////////////////////
float MathHelper::Round(float value, int position)
{
	float temp;
	temp = value * powf(10.0f, (float)position); //원하는 소수점 자리만큼의 10의 누승
	temp = floorf(temp + 0.5f); //0.5를 더해서 가장 가까운 낮은값을 찾음( ex=floor(0.2+0.5)->1.0, floor(0.7+0.5)->1.0f)
	temp *= powf(10.0f, (float)-position); //역승해 원값으로 돌림

	return temp;
}

///////////////////////////////////////////////////////////////////////////////
//	Int 절댓값을 구합니다.
///////////////////////////////////////////////////////////////////////////////
int MathHelper::Abs(int value)
{
	if (value >= 0)
		return value;
	else
		return -value;
}

///////////////////////////////////////////////////////////////////////////////
//	Float 절댓값을 구합니다.
///////////////////////////////////////////////////////////////////////////////
float MathHelper::Abs(float value)
{
	if (value >= 0)
		return value;
	else
		return -value;
}

///////////////////////////////////////////////////////////////////////////////
//	Double 절댓값을 구합니다.
///////////////////////////////////////////////////////////////////////////////
double MathHelper::Abs(double value)
{
	if (value >= 0)
		return value;
	else
		return -value;
}

///////////////////////////////////////////////////////////////////////////////
//	Degree를 Radian으로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
float MathHelper::ToRadian(float degree)
{
	return degree * 0.01745329f;
}

///////////////////////////////////////////////////////////////////////////////
//	Degree Vector2를 Radian Vector2로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
Vector2 MathHelper::ToRadian(const Vector2 & degree)
{
	return Vector2(ToRadian(degree.x), ToRadian(degree.y));
}

///////////////////////////////////////////////////////////////////////////////
//	Degree Vector3를 Radian Vector3로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 MathHelper::ToRadian(const Vector3 & degree)
{
	return Vector3(ToRadian(degree.x), ToRadian(degree.y), ToRadian(degree.z));
}

///////////////////////////////////////////////////////////////////////////////
//	Degree Vector4를 Radian Vector4로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
Vector4 MathHelper::ToRadian(const Vector4 & degree)
{
	return Vector4(ToRadian(degree.x), ToRadian(degree.y), ToRadian(degree.z), ToRadian(degree.w));
}

///////////////////////////////////////////////////////////////////////////////
//	Quaternion을 Radian Vector3로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 MathHelper::ToRadian(const Quaternion & quaternion)
{
	float pitch = 0.0f, yaw = 0.0f, roll = 0.0f;

	float qxx = quaternion.x * quaternion.x;
	float qyy = quaternion.y * quaternion.y;
	float qzz = quaternion.z * quaternion.z;

	float sinr_cosp = 2.0f * (quaternion.w * quaternion.x + quaternion.y * quaternion.z);
	float cosr_cosp = 1.0f - 2.0f * (qxx + qyy);
	pitch = atan2f(sinr_cosp, cosr_cosp);

	float sinp = 2.0f * (quaternion.w * quaternion.y - quaternion.z * quaternion.x);
	yaw = (fabsf(sinp) >= 1.0f) ? (copysign(MathHelper::Pi / 2.0f, sinp)) : (asinf(sinp));

	float siny_cosp = 2.0f * (quaternion.w * quaternion.z + quaternion.x * quaternion.y);
	float cosy_cosp = 1.0f - 2.0f * (qyy + qzz);
	roll = atan2f(siny_cosp, cosy_cosp);

	return Vector3(pitch, yaw, roll);
}

///////////////////////////////////////////////////////////////////////////////
//	Radian을 Degree로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
float MathHelper::ToDegree(float radian)
{
	return radian * 57.29578f;
}

///////////////////////////////////////////////////////////////////////////////
//	Radian Vector2를 Degree Vector2로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
Vector2 MathHelper::ToDegree(const Vector2 & radian)
{
	return Vector2(ToDegree(radian.x), ToDegree(radian.y));
}

///////////////////////////////////////////////////////////////////////////////
//	Radian Vector3를 Degree Vector3로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 MathHelper::ToDegree(const Vector3 & radian)
{
	return Vector3(ToDegree(radian.x), ToDegree(radian.y), ToDegree(radian.z));
}

///////////////////////////////////////////////////////////////////////////////
//	Radian Vector4를 Degree Vector4로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
Vector4 MathHelper::ToDegree(const Vector4 & radian)
{
	return Vector4(ToDegree(radian.x), ToDegree(radian.y), ToDegree(radian.z), ToDegree(radian.w));
}

///////////////////////////////////////////////////////////////////////////////
//	Quaternion을 Degree Vector3로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 MathHelper::ToDegree(const Quaternion & quaternion)
{
	return MathHelper::ToDegree(MathHelper::ToRadian(quaternion));
}

///////////////////////////////////////////////////////////////////////////////
//	value1 , value2 사이 길이를 구합니다.
///////////////////////////////////////////////////////////////////////////////
float MathHelper::Distance(float value1, float value2)
{
	return Abs(value1 - value2);
}

///////////////////////////////////////////////////////////////////////////////
//	value1 , value2 중 작은값을 구합니다.
///////////////////////////////////////////////////////////////////////////////
float MathHelper::Min(float value1, float value2)
{
	return value1 > value2 ? value2 : value1;
}

///////////////////////////////////////////////////////////////////////////////
//	value1 , value2 중 큰값을 구합니다.
///////////////////////////////////////////////////////////////////////////////
float MathHelper::Max(float value1, float value2)
{
	return value1 > value2 ? value1 : value2;
}

///////////////////////////////////////////////////////////////////////////////
//	value 를 min < value < max 로 고정합니다.
///////////////////////////////////////////////////////////////////////////////
float MathHelper::Clamp(float value, float min, float max)
{
	value = value > max ? max : value;
	value = value < min ? min : value;

	return value;
}

///////////////////////////////////////////////////////////////////////////////
//	제곱 함수 (a ^b)
///////////////////////////////////////////////////////////////////////////////
float MathHelper::Pow(float a, float b)
{
	return powf(a, b);
}

///////////////////////////////////////////////////////////////////////////////
//	지수 함수 (E ^a)
///////////////////////////////////////////////////////////////////////////////
float MathHelper::Exp(float a)
{
	return expf(a);
}

///////////////////////////////////////////////////////////////////////////////
//	선형 보간
///////////////////////////////////////////////////////////////////////////////
float MathHelper::Lerp(float value1, float value2, float amount)
{
	return value1 + (value2 - value1) * amount;
}

///////////////////////////////////////////////////////////////////////////////
//	스무스 보간
///////////////////////////////////////////////////////////////////////////////
float MathHelper::SmoothStep(float value1, float value2, float amount)
{
	float num = Clamp(amount, 0.0f, 1.0f);

	return Lerp(value1, value2, (num * num * (3.0f - 2.0f * num)));
}

///////////////////////////////////////////////////////////////////////////////
//	카트뮬-롬 보간
///////////////////////////////////////////////////////////////////////////////
float MathHelper::CatmullRom(float value1, float value2, float value3, float value4, float amount)
{
	float f1 = amount * amount;
	float f2 = amount * f1;

	return (float)(0.5f * (2.0f * value2 + (-value1 + value3)* amount + (2.0f * value1 - 5.0f * value2 + 4.0f * value3 - value4)* f1 + (-value1 + 3.0f * value2 - 3.0f * value3 + value4)* f2));
}

///////////////////////////////////////////////////////////////////////////////
//	에르미트 보간
///////////////////////////////////////////////////////////////////////////////
float MathHelper::Hermite(float value1, float tangent1, float value2, float tangent2, float amount)
{
	float f1 = amount;
	float f2 = f1 * f1;
	float f3 = f1 * f2;
	float f4 = (float)(2.0f * f3 - 3.0f * f2 + 1.0f);
	float f5 = (float)(-2.0f * f3 + 3.0f * f2);
	float f6 = f3 - 2.0f * f2 + f1;
	float f7 = f3 - f2;

	return (float)(value1 * f4 + value2 * f5 + tangent1 * f6 + tangent2 * f7);
}

///////////////////////////////////////////////////////////////////////////////
//	Angle(Radian) 을 -180도 ~ 180도 바깥을 넘지 못하게 합니다.
///////////////////////////////////////////////////////////////////////////////
float MathHelper::WrapAngle(float angle)
{
	angle = fmodf(angle, 6.283185f);

	if (angle <= -3.141592f)
		angle += 6.283185f;
	else if (angle > 3.141592)
		angle -= 6.283185f;

	return angle;
}

///////////////////////////////////////////////////////////////////////////////
//	3D Position 을 2D 스크린 좌표로 변환합니다.
///////////////////////////////////////////////////////////////////////////////
Vector2 MathHelper::Convert3DPointTo2D(const Vector3 & position, const Matrix & viewProjection, unsigned int width, unsigned int height)
{
	Vector4 temp = Vector4::Transform(position, viewProjection);

	if (temp.w == 0.0f)
		temp.w = 0.000001f;

	Vector3 result = Vector3(temp.x / temp.w, temp.y / temp.w, temp.z / temp.w);

	return Vector2(
		MathHelper::Round(+result.x * (width / 2)) + (width / 2),
		MathHelper::Round(-result.y * (height / 2)) + (height / 2));
}

///////////////////////////////////////////////////////////////////////////////
//	Position 이 Camera의 앞쪽에 위치한지 확인합니다.
///////////////////////////////////////////////////////////////////////////////
bool MathHelper::IsInFrontOfCamera(const Vector3 & position, float nearPlane, const Matrix & viewProjection)
{
	Vector4 temp = Vector4::Transform(Vector4(position.x, position.y, position.z, 1.0f), viewProjection);

	return temp.z > temp.w - nearPlane;
}

///////////////////////////////////////////////////////////////////////////////
//	Position -> Line 까지의 최단거리 벡터를 구합니다.
///////////////////////////////////////////////////////////////////////////////
Vector3 MathHelper::VectorToLine(const Vector3 & position, const Vector3 & line_start, const Vector3 & line_end, Vector3* out_pointOnLine)
{
	Vector3 line = line_end - line_start;
	Vector3 point = position - line_start;

	Vector3 pointOnLine = Vector3::Normalize(line) * Vector3::Dot(line, point);
	Vector3 toLine = pointOnLine - position;

	if (out_pointOnLine != 0)
		*out_pointOnLine = pointOnLine;

	return toLine;
}

///////////////////////////////////////////////////////////////////////////////
//	Position -> Line 까지의 최단거리를 구합니다.
///////////////////////////////////////////////////////////////////////////////
float MathHelper::DistanceToLine(const Vector3 & position, const Vector3 & line_start, const Vector3 & line_end, Vector3* out_pointOnLine)
{
	Vector3 line = line_end - line_start;
	Vector3 point = position - line_start;

	if (out_pointOnLine != 0)
		*out_pointOnLine = Vector3::Normalize(line) * Vector3::Dot(line, point);

	return Vector3::Cross(line, point).Length() / line.Length();
}
