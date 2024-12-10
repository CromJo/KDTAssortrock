#include <iostream>

int main()
{
	FILE* File = nullptr;

	// Mode 1번
	// r : 파일 읽어오기
	// w : 파일 만들기
	// a : 파일이 없으면 만들고 파일이 있으면,
	//		기존 파일 읽어서 맨 뒤부터 추가를 해준다.
	// Mode 2번
	// t : 텍스트파일
	// b : 바이너리 파일
	// r+ : 파일이 있으면 해당 파일을 읽기/쓰기 둘다 가능하게 열어둔다. 
	//		파일이 없으면 에러.
	// w+ : 파일이 있으면 해당 파일을 읽기/쓰기 둘다 가능하게 열어둔다.
	//		파일이 없으면 만든다.
	// a+ : 파일이 있으면 맨 끝에서부터 읽기/쓰기 둘다 가능하게 열어둔다.
	//		파일이 없으면 만든다.
	fopen_s(&File, "TestFile.txt", "wt");

	// 파일을 만들어서 파일에 데이터를 저장할 수 있는 경우
	if (nullptr != File)
	{
		fputc('A', File);
		fputs("\nHello World", File);
		
		int Number = 100;
		fprintf(File, "Number = %d", Number);

		// 열어둔 파일 스트림을 닫아준다.
		// 안닫으면 파일이 계속 사용중인 걸로 판정된다.
		fclose(File);
	}

	fopen_s(&File, "TestFile.txt", "rt");

	if (nullptr != File)
	{
		char Text1 = fgetc(File);

		std::cout << Text1 << std::endl;

		char Text2[128] = {};

		fgets(Text2, 128, File);

		std::cout << Text2 << std::endl;

		int Number1 = 0;
		fscanf_s(File, "Number = %d", &Number1);

		fclose(File);
	}

	return 0;
}