#pragma once
#include "../Share/Object.h"

/*
	abstract�� ���� �߻�Ŭ������ ������ش�.
		CAsset�� ���� �������� ���ϵ��� �ϱ� ����.

	SubSet : ��ü�� ���� Mesh�� ���� �ٸ� ���� �ִ�.
		(Ex : �����(���÷���, ��ü), ��(��, â��))
		�׷��� Mesh�� 1���� �ƴ� 2�� �̻� Mesh�� ����ϴ� ����̴�.

*/

class CAsset abstract : public CObject
{
public:
	CAsset();
	virtual ~CAsset();
};

