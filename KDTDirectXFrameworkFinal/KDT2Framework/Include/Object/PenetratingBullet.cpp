#include "PenetratingBullet.h"

/*
	관통 샷
	1. 플레이어가 스킬을 쓴다.
	2. 관통을 하는 총알이 나간다
	3. 캐릭터 2개를 관통하면 제거된다
		(한발에 두놈)
	
	만들기능
	1. 스킬버튼 및 스킬 펑션 이벤트 추가
	2. 맞춘 오브젝트 카운트하는 변수 추가
	3. 카운트 0일 시 총알 오브젝트 제거.
*/

CPenetratingBullet::CPenetratingBullet()
{
}

CPenetratingBullet::CPenetratingBullet(const CPenetratingBullet& Obj)
{
}

CPenetratingBullet::CPenetratingBullet(CPenetratingBullet&& Obj)
{
}

CPenetratingBullet::~CPenetratingBullet()
{
}

bool CPenetratingBullet::Init()
{
	return true;
}

void CPenetratingBullet::Update(float DeltaTime)
{
}
