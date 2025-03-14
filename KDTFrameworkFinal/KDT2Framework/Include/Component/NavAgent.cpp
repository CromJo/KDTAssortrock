#include "NavAgent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Navigation.h"

CNavAgent::CNavAgent()
{
}

CNavAgent::CNavAgent(const CNavAgent& Com)
{
}

CNavAgent::CNavAgent(CNavAgent&& Com)
{
}

CNavAgent::~CNavAgent()
{
}

/// <summary>
/// 길 찾기 기능
/// </summary>
/// <param name="Start"></param>
/// <param name="End"></param>
/// <returns></returns>
bool CNavAgent::FindPath(const FVector2D& Start, 
	const FVector2D& End)
{
	// 현재 씬을 받아와서
	CScene* Scene = CSceneManager::GetInst()->GetCurrentScene();
	
	// 현재씬의 길찾기 기능ㅁㄴㅇㅁㄴㅇㅁㄴㅇㅁㅇ
	return Scene->GetNavigation()->FindPath(Start, End, mPathList);
}

bool CNavAgent::FindPath(const FVector3D& Start, 
	const FVector2D& End)
{
	FVector2D	_Start;
	_Start.x = Start.x;
	_Start.y = Start.y;

	return FindPath(_Start, End);
}

bool CNavAgent::FindPath(const FVector3D& Start,
	const FVector3D& End)
{
	FVector2D	_Start;
	_Start.x = Start.x;
	_Start.y = Start.y;

	FVector2D	_End;
	_End.x = End.x;
	_End.y = End.y;

	return FindPath(_Start, _End);
}
