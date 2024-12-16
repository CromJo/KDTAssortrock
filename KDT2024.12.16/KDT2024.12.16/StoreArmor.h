#pragma once
#include "Store.h"
#include "ObjectManager.h"

class CStoreArmor final : public CStore
{

public:
	bool Init();
};

/*
	1. 아이템 무기, 방어구로 클래스는 나누어 설계한다.
	2. 스킬클래스가 있고, 스킬을 상속받은 클래스를 설계하여 
		사용할 수 있는 스킬 1개를 만든다.
	3. 전투시
		3-1. 공격
		3-2. 스킬
		3-3. 뒤로가기
		를 표시한다.
*/