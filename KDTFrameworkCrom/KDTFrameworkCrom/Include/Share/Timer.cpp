#include "Timer.h"

LARGE_INTEGER CTimer::mSecond = {};
LARGE_INTEGER CTimer::mTime = {};
float CTimer::mDeltaTime = 0.f;

void CTimer::Init()
{
	// �ʴ� ���ػ� �ð� �Ű������� ����
	QueryPerformanceFrequency(&mSecond);
	QueryPerformanceCounter(&mTime);
}

float CTimer::Update()
{
	LARGE_INTEGER Time;

	// ���ػ� �ð��� ������ ������
	QueryPerformanceCounter(&Time);

	mDeltaTime = (Time.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;

	// �Ź� �ٽ� ���ϱ� ����
	mTime = Time;

	return mDeltaTime;
}

float CTimer::GetDeltaTime()
{
	return mDeltaTime;
}
