#pragma once
#include "Scene.h"


/*
    공유 구조의 문제 : 댕글리 포인터
        1. 오브젝트의 경우 갤리의 끝에서 
*/

// 부모 : CScene | 자식 : SceneMain
class CSceneMain :
    public CScene
{
private:
    CSceneMain();
    virtual ~CSceneMain();

public:
    bool Init();

};

