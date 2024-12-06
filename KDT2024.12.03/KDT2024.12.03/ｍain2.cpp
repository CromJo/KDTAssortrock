#include <iostream>

int main()
{
	/*
		반복문 : 동일한 작업을 여러번 반복해서 동작시킬 때 사용한다.
		for, while, do while 3가지의 반복문 명칭

		for(초기값; 조건식; 증감값)
		{
			반복할 코드
		}
			※ 초기값과 증감값은 없어도 오류가 없다.

		- 동작 순서
			초기값 -> 조건식 체크 true -> 코드 동작 -> 증감값, 조건식 true,
			-> 코드 동작 -> 증감값 -> 조건식 false 시 종료.
			※ 초기값은 처음 for문 진입할때 1번만 동작한다.

		조건식이 false가 될 수 없는 조건이라면 무한루프를 돈다.
		이 경우 break를 이용해 for문을 사용해 나와야 한다.
	*/

	//int input = 0;
	//std::cout << "몇번 반복 돌릴예정? : ";
	//std::cin >> input;
	//
	//for (int i = 0; i < input; i++)
	//{
	//	if (i % 3 == 0)
	//		continue;
	//
	//	std::cout << i << "번째 예요." << std::endl;
	//}

	/*
		while(조건식)
		{
			동작할 코드
		}

		조건식이 true면 반복한다.
	*/

	/*
		do
		{
			동작할 코드
		}
		while(조건식)
		{
		}

		do while문은 처음 한번은 무조건 동작시킨다.
	*/

	int count = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//std::cout << "카운트 : " << count << std::endl;
			//count++;
			std::cout << "카운트 : " << i * 10 + j << std::endl;
		}
	}

	return 0;
}