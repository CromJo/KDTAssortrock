#pragma once
#include "GameInfo.h"

// Ŭ������ final�� �ٿ��� ��� �θ�Ŭ������ ����� �� ����.
// �� Ŭ������ �� �̻� ����� ���� �� ���� Ŭ������ �ȴ�.
class CObject1 final
{
public:
	CObject1();
	~CObject1();

public: 
	virtual bool Init();
	virtual bool Init(FILE* File);
};

