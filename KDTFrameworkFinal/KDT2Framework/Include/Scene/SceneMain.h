#pragma once

#include "Scene.h"

class CSceneMain :
    public CScene
{
	friend class CSceneManager;

private:
	CSharedPtr<class CSpriteComponent>  mRoot;

private:
	CSceneMain();
	virtual ~CSceneMain();

protected:
	virtual bool InitAsset();
	virtual bool InitObject();
	virtual bool InitWidget();
};

