#pragma once

#include "Random.h"

class Vector2;
class Vector3;
class Vector4;

//////////////////////////////////////////////////////////////////////////
///@brief ·£´ý ÇïÆÛ
//////////////////////////////////////////////////////////////////////////
class RandomHelper
{
private:
	RandomHelper(void);
	~RandomHelper(void);
public:

	static Random randomGenerator;

	static Random GenerateNewRandom();
	static int RandomInt(int max);
	static int RandomInt(int min, int max);
	static float RandomFloat(float min, float max);
	static char RandomByte(char min, char max);
	static Vector2 RandomVector2(float min, float max);
	static Vector3 RandomVector3(float min, float max);
	static Vector4 RandomVector4(float min, float max);
	static Vector2 RandomNormalVector2();
	static Vector3 RandomNormalVector3();
	static Vector4 RandomNormalVector4();
};