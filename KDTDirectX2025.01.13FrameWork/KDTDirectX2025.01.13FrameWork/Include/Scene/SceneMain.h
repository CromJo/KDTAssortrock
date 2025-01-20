#pragma once
#include "Scene.h"

class CSceneMain : public CScene
{
	friend class CSceneManager;

private:
	CSceneMain();
	virtual ~CSceneMain();
	// 클래스 구조설계를 할 때 원하는 오브젝트를 생성 및 배치를 할 수 있어야한다.
public:
	// 에디터 만들때는 FileName을 Init에 추가하도록 하자.
	virtual bool Init();
};

