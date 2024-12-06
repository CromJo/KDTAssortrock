#include <iostream>

void CreateCardBoard(int size,int Number[])
{
	// 숫자판 생성
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Number[i * size + j] = i * size + j + 1;
		}
	}
}

// 섞기
void Shuffle(int size, int Number[])
{
	for (int i = 0; i < size * size; i++)
	{
		int randomShuffle = rand() % (size * size);
		int temp = Number[i];
		Number[i] = Number[randomShuffle];
		Number[randomShuffle] = temp;
	}
}

void PrintCardBoard(int size, int Number[])
{
	// 카드판 출력
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (Number[i * size + j] == INT_MAX)
			{
				std::cout << "*\t";
			}
			else
			{
				std::cout << Number[i * size + j] << "\t";
			}
		}

		std::cout << std::endl;
	}
}

int InputCardNumber(unsigned int selectNumber)
{
	std::cout << "번호를 선택해주세요 (0 : 종료) : ";
	std::cin >> selectNumber;			// 숫자 선택

	return selectNumber;
}

void NumberChecking(int size, int Number[], int selectNumber)
{
	// 카드판에서 숫자가 있는지 체크하는 기능
	for (int i = 0; i < size * size; i++)
	{
		// 숫자가 동일 하다면 실행
		if (selectNumber == Number[i])
		{
			Number[i] = INT_MAX;
		}
	}
}

int BingoChecking(int lineCount)
{
	std::cout << lineCount << "빙고" << std::endl;

	return lineCount;
}

void GamePlay(int size, int Number[], int ComNumber[])
{
	unsigned int lineCount = 0;										// 빙고 갯수
	unsigned int selectNumber = 0;									// 선택용 변수
	unsigned int horizontalCheckCount = 0;							// 가로 체크 
	unsigned int verticalCheckCount = 0;							// 세로 체크 

	// 게임 시작
	while (true)
	{
		system("cls");

		PrintCardBoard(size, Number);							// 게임판 출력
		
		if (BingoChecking(lineCount) >= 5)
			break;

		PrintCardBoard(size, ComNumber);						// 컴퓨터용 게임판 출력

		selectNumber = InputCardNumber(selectNumber);			// 입력번호 출력 및 저장

		// 0번을 입력했거나, 5칸이상 빙고가 되었다면 종료
		if (selectNumber <= 0)
			break;

		NumberChecking(size, Number, selectNumber);				// 입력 받은 번호가 존재하는지 체크

		lineCount = 0;

		// 가로 세로 체크기능
		for (int i = 0; i < size; i++)
		{
			horizontalCheckCount = 0;
			verticalCheckCount = 0;

			// 가로 세로 카운트
			for (int j = 0; j < size; j++)
			{
				if (Number[i * size + j] == INT_MAX)
				{
					horizontalCheckCount++;
				}
				if (Number[j * size + i] == INT_MAX)
				{
					verticalCheckCount++;
				}
			}

			if (horizontalCheckCount == size)
			{
				lineCount++;
			}
			if (verticalCheckCount == size)
			{
				lineCount++;
			}
		}

		horizontalCheckCount = 0;

		// 대각선 체크 기능 (왼)
		for (int i = 0; i < size * size; i += 6)
		{
			if (Number[i] == INT_MAX)
			{
				horizontalCheckCount++;
			}

			if (horizontalCheckCount == size)
			{
				lineCount++;
			}
		}

		horizontalCheckCount = 0;

		// 대각선 체크 기능 (오)
		for (int i = 4; i < 21; i += 4)
		{
			if (Number[i] == INT_MAX)
			{
				horizontalCheckCount++;
			}

			if (horizontalCheckCount == size)
			{
				lineCount++;
			}
		}

	}
}

int main()
{
	/*
		1. 5 x 5 배열의 카드판 생성	(완)
		2. 숫자는 1 ~ 25로 지정		(완)
		3. 섞기 기능 추가				(완)
		4. 숫자 입력 기능추가			(완)
		5. 0을 입력 받으면 게임 종료	(완)
		6. 선택한 숫자는 *로 출력		(완)
		7. 만약 이미 *로 바뀐 숫자를 선택한다면 while 시작점으로 이동	(자동으로 완)
		8. 가로 5줄 세로 5줄 대각선 2줄을 만들 수 있다.				(완)
		9. 빙고 점수 추가.										(완)
		10. 빙고가 5개 이상이면 게임 종료							(완)
	*/
	const int CARDBOARD_SIZE = 5;									// 카드 보드 크기
	int Number[CARDBOARD_SIZE * CARDBOARD_SIZE] = {};				// 숫자판 생성
	int ComNumber[CARDBOARD_SIZE * CARDBOARD_SIZE] = {};				// 컴퓨터용 숫자판 생성

	system("cls");

	CreateCardBoard(CARDBOARD_SIZE, Number);					// 사이즈에 맞는 카드보드 생성
	CreateCardBoard(CARDBOARD_SIZE, ComNumber);					// ↑ 컴퓨터용으로 생성
	srand(time(0));												// 랜덤기능

	Shuffle(CARDBOARD_SIZE, Number);							// 카드셔플
	Shuffle(CARDBOARD_SIZE, ComNumber);							// ↑ 컴퓨터용으로 카드셔플

	GamePlay(CARDBOARD_SIZE, Number, ComNumber);							// 플레이어 게임시작

	std::cout << "게임 종료" << std::endl;
	return 0;
}
