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
	CSceneObject* Obj = CreateObject<CPlayerObject>("Player");
	return true;
}
