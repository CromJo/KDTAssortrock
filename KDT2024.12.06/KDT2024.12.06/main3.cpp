#include "Function.h"
#include "GameManager.h"

int main()
{
	FPlayer Player;

	//OutputFunction();
	//���� ������ �ʱ�ȭ�Ѵ�.

	if (!Init(&Player))
		return 0;
	
	// �ʱ�ȭ ������ ������ �����Ų��.
	Run(); 

	return 0;
}