#include <iostream>

int main()
{
	int Array[20] = {};
 
	// 1~10까지 2장씩 정렬해서 20개의 배열안에 추가
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Array[i * 10 + j] = j + 1;
		}
	}

	// 셔플할 횟수 입력
	int input;
	std::cout << "몇번 셔플하실건가요? : ";
	std::cin >> input;

	int shuffle = 0;
	// 배열에 들어가있는 값들을 셔플 해주는 기능을 만든다.
	// 배열안에 있는 숫자들이 100으로 되면 while문 종료.

	// 셔플 해주는 기능
	// 1. 랜덤하게 선택 0배열 ~ 19배열까지
	// 2. 랜덤하게 선택된 것을 temp에 저장
	// 3. 0번부터 순서대로 
	// 4. 랜덤하게 선택한 번호를 temp에서 넣어주기
	// 5. -1이 들어가면 중단하도록 기능 추가.

	// 셔플
	while (shuffle < input)
	{
		shuffle++;
		srand(time(0));

		// ※ 안됐던 이유 셔플 다하고 출력해줬어야했는데,
		// 시부럴꺼 출력하면서 셔플해서 그랬음
		// 
 		for (int i = 0; i < 20; i++)
		{
			int shf = rand() % 20;
			int temp = Array[i];
			Array[i] = Array[shf];
			Array[shf] = temp;
		}
	}
	
	int score = 0;		// 점수 (2000점 되면 승리)
	// 본격적인 게임시작
	while (true)
	{
		system("cls");				// DOS 명령어 수행 함수 (cls : 화면 클리너)

		if (score >= 2000)
		{
			std::cout << "게임 승리!" << std::endl;
			break;
		}

		// 출력
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				std::cout << Array[i * 10 + j] << "\t";
			}
			std::cout << std::endl;
		}


		unsigned int index[2] = {};
		int size = sizeof(index) / sizeof(int);
		
		// 카드 선택란
		for (int i = 0; i < size; i++)
		{
			std::cout << i + 1 <<"번째 카드를 골라주세요 : ";
			std::cin >> index[i];

			// -1 입력받으면 게임 종료
			if (index[i] == -1)
			{
				std::cout << "게임 종료";
				return 0;
			}
		}

		if (Array[index[0]] == Array[index[1]])
		{
			if (Array[index[0]] != 100 || Array[index[1]] != 100)
			{
				Array[index[0]] = 100;
				Array[index[1]] = 100;

				score += 200;
				std::cout << "카드가 일치합니다!" << std::endl;
			}
			else
			{
				std::cout << "이미 맞췄습니다!" << std::endl;
			}
			
		}
		else
		{
			std::cout << "카드가 일치하지 않습니다." << std::endl;
		}
	}

	std::cout << "게임 끝" << std::endl;
}
