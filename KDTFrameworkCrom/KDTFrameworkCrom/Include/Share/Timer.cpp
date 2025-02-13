#include "Timer.h"

LARGE_INTEGER CTimer::mSecond = {};
LARGE_INTEGER CTimer::mTime = {};
float CTimer::mDeltaTime = 0.f;

void CTimer::Init()
{
	// 초당 고해상도 시간 매개변수에 대입
	QueryPerformanceFrequency(&mSecond);
	QueryPerformanceCounter(&mTime);
}

float CTimer::Update()
{
	LARGE_INTEGER Time;

	// 고해상도 시간을 변수에 대입함
	QueryPerformanceCounter(&Time);

	mDeltaTime = (Time.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;

	// 매번 다시 구하기 위함
	mTime = Time;

	return mDeltaTime;
}

float CTimer::GetDeltaTime()
{
	return mDeltaTime;
}
