#pragma once
#include "Scene.h"


/*
    ���� ������ ���� : ��۸� ������
        1. ������Ʈ�� ��� ������ ������ 
*/

// �θ� : CScene | �ڽ� : SceneMain
class CSceneMain :
    public CScene
{
private:
    CSceneMain();
    virtual ~CSceneMain();

public:
    bool Init();

};

