#pragma once
#include "Store.h"
#include "ObjectManager.h"

class CStoreArmor final : public CStore
{

public:
	bool Init();
};

/*
	1. ������ ����, ���� Ŭ������ ������ �����Ѵ�.
	2. ��ųŬ������ �ְ�, ��ų�� ��ӹ��� Ŭ������ �����Ͽ� 
		����� �� �ִ� ��ų 1���� �����.
	3. ������
		3-1. ����
		3-2. ��ų
		3-3. �ڷΰ���
		�� ǥ���Ѵ�.
*/