#pragma once
#include "../GameInfo.h"

/*

	deltaTime 및 Frame 구하는 기능만 구현하기 떄문에,
	필요시 어디서든지 가지고 와야하므로,
	1. 싱글톤 작업방식
	2. static member 방식
	둘중하나 방식으로 택1

	생성자/소멸자는 필요없다.
	왜냐하면 어디서든지 불러와지는 static 클래스 이기 때문에
*/

class CTimer
{
	// CGameManager를 친구로 만들어줘서
	// CTimer의 private에 접근 가능해진다.
	friend class CGameManager;

private:
	static LARGE_INTEGER mSecond;
	static LARGE_INTEGER mTime;
	static float mDeltaTime;

public:
	static void Init();
	static float Update();
	// CGameManager를 제외하곤 이걸로 흐른시간만
	// 가지고 올 수 있도록 해준다.
	static float GetDeltaTime();

};

