#include <iostream>
#include <assert.h>

/*
	operator : 연산자 재정의.
	1. +, - 같은 기본 연산자의 기능을 재정의하여,
		해당 구조체 혹은 클래스의 고유한 연산기능을
		만들때 사용한다.
	2. C++의 모든 연산자들은 함수로 이루어져 있다.
	3. 형태 :
			반환타입 operator 연산자 (매개변수...)
			{
			}
*/
struct FPoint
{
	static FPoint Pool[20];

	int X;
	int Y;

	FPoint operator + (const FPoint& pt) const
	{
		FPoint result;
		// 그냥 x의 경우 이 + 함수를 호출한 객체의 X변수이다.
		result.X = X + pt.X;
		result.Y = Y + pt.Y;
		
		return result;
	}
	// 함수의 형태로 이루어져 있기에 오버로딩이 가능하다.
	FPoint operator + (int Number) const
	{
		FPoint result;
		result.X = X + Number;
		result.Y = Y + Number;
		
		return result;
	}
	// 매개변수를 넣어줄 경우 곱하기 연산이 되고,
	// 없을 경우 역참조가 된다.
	int operator * () const
	{
		return X;
	}
	// 랜덤액세스 기능 
	int& operator [] (int Index)
	{
		// assert를 bool값으로 설정 후 중단점이 true로 걸리면 콘솔창에서 로그를 보여준다.
		assert(Index >= 0 && Index <= 1);
		/*if (Index < 0 && Index > 1)
		{
		
		}
		*/

		if (Index == 0)
			return X;
		
		return Y;
	}

	// new와 delete도 연산자
	void* operator new (size_t Size)
	{
		return &Pool[0];
	}
	// 전치연산.
	const FPoint& operator ++ ()
	{
		++X;
		++Y;
		return *this;
	}
	// 후치연산 (매개변수에 int를 넣어줘야 가능하다)
	const FPoint& operator ++ (int)
	{
		++X;
		++Y;
		return *this;
	}

	void operator += (const FPoint& pt)
	{
		X += pt.X;
		Y += pt.Y;
	}
};

FPoint FPoint::Pool[20];

struct FString
{
public:
	/*
		초기화 시점:
			멤버	초기화 리스트 : 멤버 변수들이 객체 생성 시 즉시 초기화됩니다.
			생성자 본문 초기화 : 객체가 생성된 후 생성자 본문 내에서 초기화가 이루어집니다.
		성능:
			멤버 초기화 리스트가 일반적으로 더 효율적입니다. 
			특히 복잡한 객체나 const 멤버의 경우 차이가 더 두드러집니다.
	*/

	// 생성자 본문 초기화
	/*
	FString()
	{
		Text = nullptr;
		Count = 0;
	}
	*/

	// 멤버 초기화 리스트
	FString() : 
		Text(nullptr),		// 동적할당이 되어있을 경우 nullptr로 초기화
		Count(0)
	{
	}
	FString(const char* _Text)
	{
		Count = (int)strlen(_Text);
		Text = new char[Count + 1];
		memset(Text, 0, Count + 1);

		strcpy_s(Text, Count + 1, _Text);
	}

	// 복사 생성자
	FString(const FString& str)
	{
		Count = str.Count;
		Text = new char[Count + 1];
		memset(Text, 0, Count + 1);

		strcpy_s(Text, Count + 1, str.Text);
	}

	// 이동생성자를 이용한 메모리 이동.
	FString(FString&& str)
	{
		// 이런식으로 하면 복사생성자와 다를바가 없지만 속도는 더 느리다.
		/*{
			Count = str.Count;
			Text = new char[Count + 1];
			memset(Text, 0, Count + 1);

			strcpy_s(Text, Count + 1, str.Text);
		}*/

		// 메모리 이동개념
		Count = str.Count;
		Text = str.Text;
		str.Text = nullptr;
	}

	~FString() 
	{
		if (nullptr != Text)
			delete[] Text;
	}

private:
	char* Text;
	int Count = 0;

public:
	void operator = (const FString& str)
	{
		if (!Text)
		{
			Count = str.Count;
			Text = new char[Count + 1];		// 마지막 null문자를 위한 +1을 해준다.
			memset(Text, 0, Count + 1);		// 마지막 null문자를 위한 +1을 해준다.
		}
		else
		{
			// 길이가 작을경우 재할당을 해줘야 문제가 없기에 선언함.
			if (Count < str.Count)
			{
				delete[] Text;
				Count = str.Count;
				Text = new char[Count + 1];
				memset(Text, 0, Count + 1);
			}
		}

		strcpy_s(Text, str.Count + 1, str.Text);
	}

	void operator = (const char* str)
	{
		int Length = (int)strlen(str);

		if (!Text)
		{
			Count = Length;
			Text = new char[Count + 1];		// 마지막 null문자를 위한 +1을 해준다.
			memset(Text, 0, Count + 1);		// 마지막 null문자를 위한 +1을 해준다.
		}
		else
		{
			// 길이가 작을경우 재할당을 해줘야 문제가 없기에 선언함.
			if (Count < Length)
			{
				delete[] Text;
				Count = Length;
				Text = new char[Count + 1];
				memset(Text, 0, Count + 1);
			}
		}

		strcpy_s(Text, Length + 1, str);
	}

	FString operator + (const FString& str)
	{
		FString	result;

		if (!Text)
		{
			result = str;
		}

		else
		{
			result.Count = Count + str.Count + 1;
			result.Text = new char[result.Count + 1];
			memset(result.Text, 0, result.Count + 1);
			strcpy_s(result.Text, Count + 1, Text);
			strcat_s(result.Text, result.Count + 1, str.Text);
		}

		return result;
	}

	FString operator + (const char* str)
	{
		FString	result;

		if (!Text)
		{
			result = str;
		}

		else
		{
			int	Length = (int)strlen(str);
			result.Count = Count + Length + 1;
			result.Text = new char[result.Count + 1];
			memset(result.Text, 0, result.Count + 1);
			strcpy_s(result.Text, Count + 1, Text);
			strcat_s(result.Text, result.Count + 1, str);
		}

		return result;
	}

	void operator += (const FString& str)
	{
		if (!Text)
		{
			Count = str.Count;
			Text = new char[Count + 1];		// 마지막 null문자를 위한 +1을 해준다.
			memset(Text, 0, Count + 1);		// 마지막 null문자를 위한 +1을 해준다.
			strcpy_s(Text, Count + 1, str.Text);
		}
		else
		{
			//int Length = Count + str.Count + 1;
			int Length = Count + str.Count + 1;
			char* _Text = new char[Length];
			memset(_Text, 0, Length);
			strcpy_s(_Text, Length, Text);
			strcat_s(_Text, Length, str.Text);
			//strcat_s(_Text, str.Count + 1, str.Text);

			delete[] Text;

			Count = Length - 1;

			Text = _Text;
		}
	}

	void operator += (const char* str)
	{
		if (!Text)
		{
			Count = (int)strlen(str);
			Text = new char[Count + 1];		// 마지막 null문자를 위한 +1을 해준다.
			memset(Text, 0, Count + 1);		// 마지막 null문자를 위한 +1을 해준다.
			strcpy_s(Text, Count + 1, str);
		}
		else
		{
			int Length = Count + (int)strlen(str) + 1;
			char* _Text = new char[Length];
			memset(_Text, 0, Length);
			strcpy_s(_Text, Length, Text);
			strcat_s(_Text, Length, str);

			delete[] Text;

			Count = Length - 1;

			Text = _Text;
		}
	}

	bool operator == (const FString& str) const
	{
		// 두 문자열 비교후 같으면 true 틀리면 false 반환
		return strcmp(Text, str.Text) == 0;	
	}

	bool operator == (const char* str) const
	{
		// 두 문자열 비교후 같으면 true 틀리면 false 반환
		return strcmp(Text, str) == 0;
	}

	bool operator != (const FString& str) const
	{
		// 두 문자열 비교후 틀리면 true 같으면 false 반환
		return strcmp(Text, str.Text) != 0;
	}

	bool operator != (const char* str) const
	{
		// 두 문자열 비교후 틀리면 true 같으면 false 반환
		return strcmp(Text, str) != 0;
	}

	// 역참조
	const char* operator *() const
	{
		return Text;
	}

	int Length()
	{
		return Count;
	}

	FString Split(const char* str)
	{
		char* Context = nullptr;
		char* Left = strtok_s(Text, str, &Context);

		Count = (int)strlen(Context);

		char* _Text = new char[Count + 1];
		memset(_Text, 0, Count + 1);
		strcpy_s(_Text, Count + 1, Context);	

		FString result = Left;

		delete[] Text;

		Text = _Text;

		return result;
	}
};

// Array 클래스를 만들어보기.
class CArray
{
private:
	int* mArr;
	int mArrLength;

public:
	// 생산자로 원하는 양의 배열 생성
	CArray(int length) : mArrLength(length)
	{
		mArr = new int[length];
	}

	int& operator[] (int index)
	{
		if (index < 0 || index >= mArrLength)
		{
			std::cout << "범위가 이상하세요." << std::endl;
			assert(false);
		}
		
		return mArr[index];
	}

	~CArray()
	{
		delete []mArr;
	}
};

int main()
{
	FPoint p1, p2, p3;
	p1.X = 10;
	p1.Y = 20;
	p2.X = 30;
	p2.Y = 40;

	//p3 = p1;
	// 커스텀 자료형의 경우 기본 연산자들이 오버로딩이 안되어있어 오류가 뜬다.
	// p1의 + 함수호출한다는 뜻이다.
	p3 = p1 + p2;			// FPoint operator + 함수로 인해 사용이 가능하다. (없으면 fail) 
	// 정수끼리 더하는 전역 + 연산자 함수 호출
	int Number = 10 + 20;

	p3 = p1 + 50;
	std::cout << p3.X << " | " << p3.Y << std::endl;
	std::cout << *p1 << " | " << *p2 << std::endl;
	std::cout << p1[1] << std::endl;
	//std::cout << p1[2] << std::endl;			// assert 에러 확인용
	
	FPoint* pt1 = new FPoint;
	++p1;			// 전치연산을 사용하여 가능한 문법.
	p1++;			// 후치연산을 사용하여 가능한 문법.

	FString str;	
	str = "문자열";

	FString str1;
	str1 = "테스트";

	FString strResult;
	strResult = str + str1;

	std::cout << *strResult << std::endl;		// 역참조
	
	FString strPE = str;
	strPE = " 아이 위시 포레버";
	// 임시객체를 대입함.
	// 1. 컴파일러 최적화로 인해 이동생성자도 되지 않는다.
	// 2. 크래쉬는 나지 않는다. (임시메모리 해제와 관련이 있다.)
	FString("임시객체");							// 사용후 바로 소멸자가 실행된다.
	// 임시객체를 대입할 경우 임시객체는 제거가 안된다.
	// 임시객체를 대입받은 strTemp가 제거되면,
	// 임시객체가 제거된 것과 같다.
	FString strTemp = FString("임시객체 대입");	// 사용후 소멸자 실행이 안된다. (참조로 인식되기 때문)
	std::cout << "str템프 주소값 : " << &strTemp << std::endl;

	strResult += " : 붙여보리기";
	strResult += str1;

	std::cout << "str리절트 주소값 : " << *strResult << std::endl;
	std::cout << "str리절트 길이 : " << strResult.Length() << std::endl;

	FString SplitLeft = strResult.Split(":");
	//std::cout << strResult.Text << std::endl;
	
	// 랜덤액세스 연산자 함수를 레퍼런스로 받으면 가능한 문법.
	//p1 = 100;		// 랜덤액세스 기능의 실패.

	return 0;
}