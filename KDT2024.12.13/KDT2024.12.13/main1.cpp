#include <iostream>
#include "Object.h"
#include "Player.h"
#include "Monster.h"

int main()
{
	CObject* ObjList[100] = {};

	ObjList[0] = new CPlayer;
	ObjList[1] = new CPlayer;
	ObjList[2] = new CMonster;
	ObjList[3] = new CCharacter;

	ObjList[0]->Init();
	ObjList[1]->Init();
	ObjList[2]->Init();
	ObjList[3]->Init();

	for (int i = 0; i < 4; i++)
	{
		ObjList[i]->Init();
	}

	ObjList[0]->SetName("¤±¤±");
	CPlayer* Char = dynamic_cast<CPlayer*>(ObjList[0]);

	if (nullptr != Char)
	{
		Char->SetCharacterInfo(10, 20, 30, 40);
		Char->SetJob(EJob::Knight);
	}

	for (int i = 0; i < 4; i++)
	{
		ObjList[i]->Output();
	}

	for (int i = 0; i < 100; i++)
	{
		if (ObjList[i])
			return 0;
	}

	return 0;

}