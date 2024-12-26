#include "ObjectManager.h"
#include "Player.h"

DEFINITION_SINGLE(CObjectManager)

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
}

bool CObjectManager::Init()
{
	CreateObj<CPlayer>();

	return true;
}

void CObjectManager::Update(float DeltaTime)
{
	std::list<CObject*>::iterator iter;
	std::list<CObject*>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd; iter++)
	{
		(*iter)->Update(DeltaTime);
	}
}

void CObjectManager::Output()
{
	std::list<CObject*>::iterator iter;
	std::list<CObject*>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd; iter++)
	{
		(*iter)->Output();
	}
}

