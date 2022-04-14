#pragma once

class Vector2;
class Vector3;
class Vector4;

class Matrix;
class Quaternion;
class Plane;

class MathHelper
{
private:
	MathHelper() {}
public:
	static float Round(float value);
	static float Round(float value, int position);

	static int Abs(int value);
	static float Abs(float value);
	static double Abs(double value);

	static float ToRadian(float degree);
	static Vector2 ToRadian(const Vector2& degree);
	static Vector3 ToRadian(const Vector3& degree);
	static Vector4 ToRadian(const Vector4& degree);
	static Vector3 ToRadian(const Quaternion& quaternion);

	static float ToDegree(float radian);
	static Vector2 ToDegree(const Vector2& radian);
	static Vector3 ToDegree(const Vector3& radian);
	static Vector4 ToDegree(const Vector4& radian);
	static Vector3 ToDegree(const Quaternion& quaternion);

	static float Distance(float value1, float value2);

	static float Min(float value1, float value2);
	static float Max(float value1, float value2);
	static float Clamp(float value, float min, float max);

	static float Pow(float a, float b);
	static float Exp(float a);

	static float Lerp(float value1, float value2, float amount);
	static float SmoothStep(float value1, float value2, float amount);
	static float CatmullRom(float value1, float value2, float value3, float value4, float amount);
	static float Hermite(float value1, float tangent1, float value2, float tangent2, float amount);
	static float WrapAngle(float angle);

	static Vector2 Convert3DPointTo2D(const Vector3& position, const Matrix& viewProjection, unsigned int width, unsigned int height);

	static bool IsInFrontOfCamera(const Vector3& position, float nearPlane, const Matrix& viewProjection);
	static Vector3 VectorToLine(const Vector3& position, const Vector3& line_start, const Vector3& line_end,Vector3* out_pointOnLine = 0);
	static float DistanceToLine(const Vector3& position, const Vector3& line_start, const Vector3& line_end, Vector3* out_pointOnLine = 0);


public:
	const static float E;///< 자연로그의 밑수
	const static float Log2E;///< 자연로그의 밑수 2
	const static float Log10E;///< 자연로그의 밑수 10
	const static float Pi;///< PI
	const static float TwoPi;///< PI * 2
	const static float PiOver2;///< PI / 2
	const static float PiOver4;///< PI / 4
	const static float Epsilon;///< 0.000001f

	const static int IntMin;///< Int형의 최소값
	const static int IntMax;///< Int형의 최대값
	const static float FloatMin;///< Flaot형의 최소값
	const static float FloatMax;///< Float형의 최대값
};
