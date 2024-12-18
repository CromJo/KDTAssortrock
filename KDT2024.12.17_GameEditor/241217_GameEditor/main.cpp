
#include "ItemWeapon.h"
#include "ItemArmor.h"
#include "Monster.h"
#include "Player.h"

enum class EMenu
{
	None,
	ItemAdd,
	ItemDelete,
	ItemOutput,
	ItemSave,
	ItemLoad,
	Exit
};

CItem** gItemList;
CCharacter** gCharacterList;

// 실제 추가된 아이템 수
int		gArrayCount = 0;

// 실제 할당된 배열의 수
int		gArrayCapacity = 4;

void AddItem()
{
	// 현재 배열이 꽉 찼는지 판단한다.
	if (gArrayCount == gArrayCapacity)
	{
		// 새로운 배열을 전체 배열 수의 2배만큼
		// 할당해준다.
		gArrayCapacity *= 2;
		CItem** Array = new CItem*[gArrayCapacity];

		// 원래 있던 배열에서 데이터를 옮겨준다.
		for (int i = 0; i < gArrayCount; ++i)
		{
			Array[i] = gItemList[i];
		}

		// 원래 배열을 제거한다.
		delete[] gItemList;

		// 새로운 배열의 주소를 저장한다.
		gItemList = Array;
	}

	EItemType	ItemType;

	while (true)
	{
		system("cls");
		// 무기, 방어구 둘중 어떤것을 생성할지 선택
		std::cout << "1. 무기" << std::endl;
		std::cout << "2. 방어구" << std::endl;
		std::cout << "선택 : ";
		int	Input;
		std::cin >> Input;

		if (Input < 1 || Input > 2)
			continue;

		ItemType = (EItemType)(Input - 1);
		break;
	}

	switch (ItemType)
	{
	case EItemType::Weapon:
		gItemList[gArrayCount] = new CItemWeapon;
		break;
	case EItemType::Armor:
		gItemList[gArrayCount] = new CItemArmor;
		break;
	}

	gItemList[gArrayCount]->Init();
	++gArrayCount;
}

void DeleteItem()
{
}

void OutputItem()
{
	system("cls");
	for (int i = 0; i < gArrayCount; ++i)
	{
		gItemList[i]->Output();
	}

	system("pause");
}

void SaveItem()
{
	FILE* File = nullptr;
	int WeaponCount = 0;

	fopen_s(&File, "WeaponStore.sto", "wb");

	if (WeaponCount > 0)
	{
		if (!File)
			return;

		// 전체 수만큼 반복하여 무기의 수를 구한다.
		for (int i = 0; i < gArrayCount; i++)
		{
			if (gItemList[i]->GetItemType() == EItemType::Weapon)
			{
				WeaponCount++;
			}
		}

		// 아이템이 생성된 수를 저장한다.
		fwrite(&gArrayCount, sizeof(int), 1, File);

		for (int i = 0; i < gArrayCount; i++)
		{
			if (gItemList[i]->GetItemType() == EItemType::Weapon)
			{
				gItemList[i]->Save(File);
			}
		}

		fclose(File);
	}

	int ArmorCount = gArrayCount - WeaponCount;
	fopen_s(&File, "ArmorStore.sto", "wb");

	if (ArmorCount > 0)
	{
		if (!File)
			return;

		// 전체 수만큼 반복하여 무기의 수를 구한다.
		for (int i = 0; i < gArrayCount; i++)
		{
			if (gItemList[i]->GetItemType() == EItemType::Armor)
			{
				ArmorCount++;
			}
		}

		// 아이템이 생성된 수를 저장한다.
		fwrite(&gArrayCount, sizeof(int), 1, File);

		for (int i = 0; i < gArrayCount; i++)
		{
			if (gItemList[i]->GetItemType() == EItemType::Armor)
			{
				gItemList[i]->Save(File);
			}
		}

		fclose(File);
	}
}

void LoadItem()
{
}

void AddCharacter()
{
	// 현재 배열이 꽉 찼는지 판단한다.
	if (gArrayCount == gArrayCapacity)
	{
		// 새로운 배열을 전체 배열 수의 2배만큼
		// 할당해준다.
		gArrayCapacity *= 2;
		CCharacter** Array = new CCharacter* [gArrayCapacity];

		// 원래 있던 배열에서 데이터를 옮겨준다.
		for (int i = 0; i < gArrayCount; ++i)
		{
			Array[i] = gCharacterList[i];
		}

		// 원래 배열을 제거한다.
		delete[] gCharacterList;

		// 새로운 배열의 주소를 저장한다.
		gCharacterList = Array;
	}

	ECharacterType	CharacterType;

	while (true)
	{
		system("cls");
		// 무기, 방어구 둘중 어떤것을 생성할지 선택
		std::cout << "1. 플레이어블 캐릭터" << std::endl;
		std::cout << "2. 몬스터 캐릭터" << std::endl;
		std::cout << "선택 : ";

		int	Input;
		std::cin >> Input;

		if (Input < 1 || Input > 2)
			continue;

		CharacterType = (ECharacterType)(Input - 1);
		break;
	}

	switch (CharacterType)
	{
	case ECharacterType::Monster:
		gCharacterList[gArrayCount] = new CMonster;
		break;
	case ECharacterType::Player:
		gCharacterList[gArrayCount] = new CPlayer;
		break;
	}

	gCharacterList[gArrayCount]->Init();
	++gArrayCount;
}
void DeleteCharacter()
{

}
void SaveCharacter()
{
	// 만들 파일 데이터 생성
	FILE* File = nullptr;
	int PlayerCount = 0;

	//"Playerable.char" 파일을 오픈 (없으면 파일 생성)
	fopen_s(&File, "Playerable.char", "wb");

	// 플레이어가 한개라도 존재하는지를 체크
	if (PlayerCount > 0)
	{
		if (!File)
			return;

		// 전체 수만큼 반복하여 무기의 수를 구한다.
		for (int i = 0; i < gArrayCount; i++)
		{
			if (gCharacterList[i]->GetCharacterType() == ECharacterType::Player)
			{
				PlayerCount++;
			}
		}

		// 아이템이 생성된 수를 저장한다.
		fwrite(&gArrayCount, sizeof(int), 1, File);

		for (int i = 0; i < gArrayCount; i++)
		{
			if (gCharacterList[i]->GetCharacterType() == ECharacterType::Player)
			{
				gCharacterList[i]->Save(File);
			}
		}

		fclose(File);
	}

	int MonsterCount = gArrayCount - PlayerCount;
	fopen_s(&File, "Monster.char", "wb");

	if (MonsterCount > 0)
	{
		if (!File)
			return;

		// 전체 수만큼 반복하여 무기의 수를 구한다.
		for (int i = 0; i < gArrayCount; i++)
		{
			if (gCharacterList[i]->GetCharacterType() == ECharacterType::Monster)
			{
				MonsterCount++;
			}
		}

		// 아이템이 생성된 수를 저장한다.
		fwrite(&gArrayCount, sizeof(int), 1, File);

		for (int i = 0; i < gArrayCount; i++)
		{
			if (gCharacterList[i]->GetCharacterType() == ECharacterType::Monster)
			{
				gCharacterList[i]->Save(File);
			}
		}

		fclose(File);
	}
}
void LoadCharacter()
{
	FILE* File = nullptr;

	fopen_s(&File, "Monster.char", "rb");

	if (File)
		return;

	// 현재 배열에 다른 몬스터가 들어가 있을 수 있기 때문에,
	// 몬스터 수를 다른 변수에 저장한다.
	int MonsterCount = 0;

	fread(&MonsterCount, sizeof(int), 1, File);

	// 읽어온 개체수가 배열 수보다 많으면,
	// 배열을 더 큰 크기로 재생성한다.
	if (MonsterCount > gArrayCapacity)
	{
		for (int i = 0; i < gArrayCount; i++)
		{
			delete gCharacterList[i];
		}

		gArrayCapacity = MonsterCount;

		delete[] gCharacterList;

		//gCharacterList = new CMonster[gArrayCapacity];
		// 만들때는 같은 형으로 넣어줘야함.
		gCharacterList = new CCharacter*[gArrayCapacity];
	}

}
void OutputCharacter()
{
	system("cls");

	for (int i = 0; i < gArrayCount; ++i)
	{
		gCharacterList[i]->Output();
	}

	system("pause");
}

// 아이템의 출력부분을 표시하는 기능
void ItemSmithy()
{
	// 처음에 배열을 4개 할당한다.
	gItemList = new CItem * [gArrayCapacity];

	while (true)
	{
		system("cls");
		std::cout << "1. 아이템추가" << std::endl;
		std::cout << "2. 아이템삭제" << std::endl;
		std::cout << "3. 아이템출력" << std::endl;
		std::cout << "4. 아이템저장" << std::endl;
		std::cout << "5. 아이템불러오기" << std::endl;
		std::cout << "6. 종료" << std::endl;
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
		case EMenu::ItemAdd:
			AddItem();
			break;
		case EMenu::ItemDelete:
			DeleteItem();
			break;
		case EMenu::ItemOutput:
			OutputItem();
			break;
		case EMenu::ItemSave:
			SaveItem();
			break;
		case EMenu::ItemLoad:
			LoadItem();
			break;
		}
	}

	for (int i = 0; i < gArrayCount; ++i)
	{
		delete gItemList[i];
	}
	delete[] gItemList;

}

// 캐릭터 출력부분을 표시하는 기능
void CharacterSmithy()
{
	gCharacterList = new CCharacter* [gArrayCapacity];

	while (true)
	{
		system("cls");
		std::cout << "1. 캐릭터 추가" << std::endl;
		std::cout << "2. 캐릭터 삭제" << std::endl;
		std::cout << "3. 캐릭터 출력" << std::endl;
		std::cout << "4. 캐릭터 저장" << std::endl;
		std::cout << "5. 캐릭터 불러오기" << std::endl;
		std::cout << "6. 종료" << std::endl;
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
		case EMenu::ItemAdd:
			AddCharacter();
			break;
		case EMenu::ItemDelete:
			DeleteCharacter();
			break;
		case EMenu::ItemOutput:
			OutputCharacter();
			break;
		case EMenu::ItemSave:
			SaveCharacter();
			break;
		case EMenu::ItemLoad:
			LoadCharacter();
			break;
		}
	}

	for (int i = 0; i < gArrayCount; ++i)
	{
		delete gCharacterList[i];
	}
	delete[] gCharacterList;

}

int main()
{
	CharacterSmithy();

	return 0;
}
