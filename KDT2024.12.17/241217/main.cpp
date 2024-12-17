
#include "GameManager.h"

class CTest
{
public:
	CTest()	:
		mNumber(20)
	{
	}

	~CTest()
	{
	}

public:
	int	mNumber = 10;
};



int main()
{
	/*CTest	test;

	std::cout << test.mNumber << std::endl;

	return 0;*/

	if (!CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		return 0;
	}

	CGameManager::GetInst()->Run();

	CGameManager::DestroyInst();

	return 0;
}
