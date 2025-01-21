#include "SceneMain.h"
#include "../Object/PlayerObject.h"
#include "../Component/StaticMeshComponent.h"

CSceneMain::CSceneMain()
{
}

CSceneMain::~CSceneMain()
{
}

bool CSceneMain::Init()
{
	if (!CScene::Init())
		return false;

	CSceneObject* Obj = CreateObject<CPlayerObject>("Player");
	return true;
}
