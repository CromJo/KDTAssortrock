#pragma once
#include "../Share/Object.h"

/*
	abstract로 만들어서 추상클래스로 만들어준다.
		CAsset을 직접 생성하지 못하도록 하기 위함.

	SubSet : 물체에 따라 Mesh의 색이 다를 수가 있다.
		(Ex : 모니터(디스플레이, 몸체), 집(벽, 창문))
		그래서 Mesh를 1개가 아닌 2개 이상 Mesh를 사용하는 방법이다.

*/

class CAsset abstract : public CObject
{
public:
	CAsset();
	virtual ~CAsset();
};

