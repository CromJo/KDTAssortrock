#pragma once
#include "../GameInfo.h"

/*

	deltaTime �� Frame ���ϴ� ��ɸ� �����ϱ� ������,
	�ʿ�� ��𼭵��� ������ �;��ϹǷ�,
	1. �̱��� �۾����
	2. static member ���
	�����ϳ� ������� ��1

	������/�Ҹ��ڴ� �ʿ����.
	�ֳ��ϸ� ��𼭵��� �ҷ������� static Ŭ���� �̱� ������
*/

class CTimer
{
	// CGameManager�� ģ���� ������༭
	// CTimer�� private�� ���� ����������.
	friend class CGameManager;

private:
	static LARGE_INTEGER mSecond;
	static LARGE_INTEGER mTime;
	static float mDeltaTime;

public:
	static void Init();
	static float Update();
	// CGameManager�� �����ϰ� �̰ɷ� �帥�ð���
	// ������ �� �� �ֵ��� ���ش�.
	static float GetDeltaTime();

};

