/*
	String 클래스 제작 operator
	+, = , +=, ==, !=, *(역참조) 문자열 반환

	제작 함수
	Length() : 문자열 수 반환
	Split() : 문자열 분리 함수. 인자로 분리할 문자열을
			넣어주면 분리시켜준다. 왼쪽 문자열을 반환한다.

	이동생성자
	문자열 이동
*/

#include <iostream>

class CString
{
public:
	CString()
	{
		this->Text = nullptr;
		this->Count = 0;
	}

public:
	char* Text = nullptr;
	int Count = 0;
	
	// = 연산자
	void operator = (const char* str)
	{
		if (Text)
		{
			delete[] Text;	// 기존 메모리 해제
		}

		Count = strlen(str);		// 받은 문자의 갯수로 형변환
		Text = new char[Count + 1];
		strcpy_s(Text, Count + 1, str);
	}

	// + 연산자 
	CString& operator + (const CString& str)
	{
		CString result;

		if (!Text)
		{
			result = str;
		}
	
		result.Count = Count + str.Count + 1;
		result.Text = new char[result.Count + 1];
		memset(result.Text, 0, result.Count + 1);
		strcpy_s(result.Text, Count + 1, Text);
		strcat_s(result.Text, result.Count + 1, str.Text);

		return result;
	}

	// += 연산자
	CString& operator += (const CString& str)
	{
		CString result;

		if (!Text)
		{
			result = str;
		}

		result.Count += str.Count + 1;
		result.Text = new char[result.Count + 1];
		memset(result.Text, 0, result.Count + 1);
		strcpy_s(result.Text, Count + 1, Text);
		strcat_s(result.Text, result.Count + 1, str.Text);

		return result;
	}
};

int main()
{
	CString A;
	CString B;
	A = "어 형이야";
	B = "어 혼자왔니?";

	CString AB;
	AB = A + B;

	CString C;
	C = "응애";
	C += AB;


	std::cout << AB.Text << " | " << AB.Count << std::endl;
	std::cout << C.Text << std::endl;
	return 0;
}