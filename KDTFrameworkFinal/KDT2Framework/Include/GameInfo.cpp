
#include "GameInfo.h"

int Clamp(int Value, int Min, int Max)
{
	if (Value < Min)
		Value = Min;

	else if (Value > Max)
		Value = Max;

	return Value;
}

float Clamp(float Value, float Min, float Max)
{
	if (Value < Min)
		Value = Min;

	else if (Value > Max)
		Value = Max;

	return Value;
}

// 랜덤 범위지정 난수 생성 기능
int RandomRange(int Min, int Max)
{
	return Min + rand() % (Max - Min + 1);
}

// 랜덤 범위지정 난수 생성 기능
float RandomRange(float Min, float Max)
{
	return Min + static_cast<float>(rand()) / RAND_MAX * (Max - Min);
}