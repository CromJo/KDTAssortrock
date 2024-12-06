#include <iostream>
#include <time.h>

int main()
{
	/*
	if문			: 여러 조건 중 특정한 하나를 처리하는 기능
		if(조건)
		{
			조건 체크 후 true시 실행문
		}
	switch문		: 
	*/

#pragma region 조건문
	{
		int BossHP = 29;

		if (BossHP <= 30)
			std::cout << "어 트루야 " << std::endl;
		else if (BossHP == 0)
			printf("어 사망이야 \n");
		else
			std::cout << "어 거짓이야 " << std::endl;
	}
#pragma endregion

#pragma region 랜덤
	{
		// 최소 : 200 | 최대 : 300
		// rand() % (최대 - 최소 + 1) + 최소
		srand(time(0));
		std::cout << "랜덤 : " << rand() << std::endl;
		std::cout << "특정 범위 랜덤 100 ~ 200 : " << rand() % 101 + 100 << std::endl;
		std::cout << "소수점 랜덤 2자릿수 : " << rand() % 10001 * 0.01f << std::endl;
	}
#pragma endregion

#pragma region if문 도전과제
	/*
		1. 강화수치를 저장하는 int 변수가 하나 존재
		2. 강화 수치가 0 ~ 3 사이면 100% 확률로 성공
		3. 4 ~ 6 일경우 50% 확률로 성공
		4. 7 ~ 9 일경우 20% 확률로 성공
		5. 10 ~ 12 일경우 2% 확률로 성공
		6. 13 이상일 경우 0.7% 확률로 성공
	*/
	{
		int level = 13;

		std::cout << "현재 강화 수치 : " << level << std::endl;
		if (level <= 3)
		{
			level++;
		}
		else if (level <= 6)
		{
			if (rand() % 101 >= 50)
			{
				level++;
			}
			else
				std::cout << "강화 실패" << std::endl;
		}
		else if (level <= 9)
		{
			if (rand() % 101 >= 80)
				level++;
			else
				std::cout << "강화 실패" << std::endl;
		}
		else if (level <= 12)
		{
			if (rand() % 101 >= 98)
				level++;
			else
				std::cout << "강화 실패" << std::endl;
		}
		else
		{
			int a = 0;
			while (true)
			{
				float b = rand() % 10001 * 0.0 1f;

				if (b >= 99.3f)
				{
					std::cout << "성공했을 때 확률 : " << "\t 확률 : " << b << std::endl;
					level++;
					break;
				}
				else
					std::cout << "강화 실패 도전 횟수 : " << a++ << "\t 확률 : " << b << std::endl;
			}

		}
		std::cout << "레벨 : " << level << std::endl;
	}
#pragma endregion
	return 0;
}