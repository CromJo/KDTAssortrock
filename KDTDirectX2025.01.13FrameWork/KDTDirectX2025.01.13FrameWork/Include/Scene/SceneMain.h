#pragma once
#include "Scene.h"

class CSceneMain : public CScene
{
	friend class CSceneManager;

private:
	CSceneMain();
	virtual ~CSceneMain();
	// Ŭ���� �������踦 �� �� ���ϴ� ������Ʈ�� ���� �� ��ġ�� �� �� �־���Ѵ�.
public:
	// ������ ���鶧�� FileName�� Init�� �߰��ϵ��� ����.
	virtual bool Init();
};

