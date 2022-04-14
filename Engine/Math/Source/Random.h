#pragma once

#include <wtypes.h>

//////////////////////////////////////////////////////////////////////////
///@brief 난수 발생(Knuth's Subtractive Method)
//////////////////////////////////////////////////////////////////////////
class Random
{
public:
	Random(void);
	Random(int seed);
	~Random(void);

	virtual int Next();
	virtual int Next(int minValue, int maxValue);
	virtual int Next(int maxValue);

	virtual double NextDouble();
	virtual void NextBytes(BYTE* buffer, UINT size);

protected:
	virtual double Sample();

private:
	void BuildSeed(int seed);

	int InternalSample();
	double GetSampleForLargeRange();

	int next;///< 다음시드
	int nextP;///< 다음시드 지점

	int seedArray[56];///< 시드값을 저장할 배열

	const static int MaxBig;
	const static int MaxSeed;
};