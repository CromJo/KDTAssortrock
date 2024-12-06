#include <iostream>
#include <Windows.h>

// testInt를 이용하여 int 타입 변수를 선언할 수 있게 해준다.
typedef int kim;

int main()
{
	char Text[32] = {};		// 0으로 초기화 및 선언
	
	strcpy_s(Text, "응 형이야");

	std::cout << Text << std::endl;

	// typedef : 타입을 다른 이름으로 사용할 수 있도록 타입의 이름을 추가해준다.
	// 타입의 이름을 추가해준다.
	size_t Count = strlen(Text);
	//strlen(Text);	// 문자열의 길이를 확인하는 함수

	std::cout << "문자열 길이 : " << Count << std::endl;

	// strcmp : 왼쪽과 오른쪽에 들어가는 문자열이 서로 같은지 비교.
	//			같으면 0을 반환, 다를 경우 0이 아닌 값으로 반환.
	if (strcmp("aa", "aa") == 0)
	{
		std::cout << "같다." << std::endl;
	}
	else
	{
		std::cout << "다르다." << std::endl;
	}

	// strcat_s :  오른쪽의 문자열을 왼쪽의 문자열의 뒤에 붙여준다.
	strcat_s(Text, "aabb cc");
	std::cout << "붙이기 결과 : " << Text << strcat_s(Text, "Yoshi ") << std::endl;

	wchar_t Text111 = '엉';		// 2byte로 되어있는 char
	char Text222 = 'ㄴ';

	std::wcout.imbue(std::locale("kor"));
	std::wcout << L"항굴" << std::endl;

	std::wstring

	return 0;
}