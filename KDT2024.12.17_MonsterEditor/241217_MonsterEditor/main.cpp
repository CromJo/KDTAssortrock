
#include "Monster.h"

enum class EMenu
{
	None,
	MonsterAdd,
	MonsterDelete,
	MonsterModify,
	MonsterOutput,
	MonsterSave,
	MonsterLoad,
	Exit
};

CMonster** gMonsterList;

// 실제 추가된 아이템 수
int		gMonsterCount = 0;

// 실제 할당된 배열의 수
int		gMonsterCapacity = 4;

void AddMonster()
{
	// 현재 배열이 꽉 찼는지 판단한다.
	if (gMonsterCount == gMonsterCapacity)
	{
		// 새로운 배열을 전체 배열 수의 2배만큼
		// 할당해준다.
		gMonsterCapacity *= 2;
		CMonster** Array = new CMonster*[gMonsterCapacity];

		// 원래 있던 배열에서 데이터를 옮겨준다.
		for (int i = 0; i < gMonsterCount; ++i)
		{
			Array[i] = gMonsterList[i];
		}

		// 원래 배열을 제거한다.
		delete[] gMonsterList;

		// 새로운 배열의 주소를 저장한다.
		gMonsterList = Array;
	}

	gMonsterList[gMonsterCount] = new CMonster;

	gMonsterList[gMonsterCount]->Init();

	++gMonsterCount;
}

void OutputMonster()
{
	system("cls");

	for (int i = 0; i < gMonsterCount; ++i)
	{
		gMonsterList[i]->Output();
	}

	system("pause");
}

void SaveMonster()
{
	FILE* File = nullptr;

	fopen_s(&File, "MonsterList.mls", "wb");

	if (!File)
		return;

	fwrite(&gMonsterCount, sizeof(int), 1, File);

	for (int i = 0; i < gMonsterCount; ++i)
	{
		EBattleType BattleType =
			gMonsterList[i]->GetBattleType();

		fwrite(&BattleType, sizeof(EBattleType),
			1, File);

		gMonsterList[i]->Save(File);
	}

	fclose(File);
}

void LoadMonster()
{
	FILE* File = nullptr;

	fopen_s(&File, "MonsterList.mls", "rb");

	if (!File)
		return;

	// 현재 배열에 다른 몬스터가 들어가 있을 수 있기 때문에
	// 몬스터 수를 다른 변수에 저장한다.
	int	MonsterCount = 0;

	fread(&MonsterCount, sizeof(int), 1, File);

	// 읽어온 몬스터의 수가 배열 수보다 클 경우
	// 배열을 다시 만들어준다.
	if (MonsterCount > gMonsterCapacity)
	{
		// 기존 배열에 들어가있던 몬스터를 제거한다.
		for (int i = 0; i < gMonsterCount; ++i)
		{
			delete gMonsterList[i];
		}

		gMonsterCapacity = MonsterCount;

		delete[]	gMonsterList;

		gMonsterList = new CMonster*[gMonsterCapacity];
	}

	gMonsterCount = MonsterCount;

	for (int i = 0; i < gMonsterCount; ++i)
	{
		gMonsterList[i] = new CMonster;

		EBattleType BattleType;

		fread(&BattleType, sizeof(EBattleType),
			1, File);

		gMonsterList[i]->Init(File);
	}

	fclose(File);
}

int main()
{
	// 처음에 배열을 4개 할당한다.
	gMonsterList = new CMonster*[gMonsterCapacity];

	while (true)
	{
		system("cls");
		std::cout << "1. 몬스터추가" << std::endl;
		std::cout << "2. 몬스터삭제" << std::endl;
		std::cout << "3. 몬스터수정" << std::endl;
		std::cout << "4. 몬스터출력" << std::endl;
		std::cout << "5. 몬스터저장" << std::endl;
		std::cout << "6. 몬스터불러오기" << std::endl;
		std::cout << "7. 종료" << std::endl;
		std::cout << "메뉴를 선택하세요 : ";
		int	Input;
		std::cin >> Input;

		if (Input == (int)EMenu::Exit)
			break;

		else if (Input <= (int)EMenu::None ||
			Input > (int)EMenu::Exit)
			continue;

		switch ((EMenu)Input)
		{
		case EMenu::MonsterAdd:
			AddMonster();
			break;
		case EMenu::MonsterDelete:
			//DeleteMonster();
			break;
		case EMenu::MonsterModify:
			break;
		case EMenu::MonsterOutput:
			OutputMonster();
			break;
		case EMenu::MonsterSave:
			SaveMonster();
			break;
		case EMenu::MonsterLoad:
			LoadMonster();
			break;
		}
	}

	for (int i = 0; i < gMonsterCount; ++i)
	{
		delete gMonsterList[i];
	}

	delete[] gMonsterList;

	return 0;
}
