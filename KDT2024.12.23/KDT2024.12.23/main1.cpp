#include <iostream>
#include <assert.h>

/*
	operator : ������ ������.
	1. +, - ���� �⺻ �������� ����� �������Ͽ�,
		�ش� ����ü Ȥ�� Ŭ������ ������ ��������
		���鶧 ����Ѵ�.
	2. C++�� ��� �����ڵ��� �Լ��� �̷���� �ִ�.
	3. ���� :
			��ȯŸ�� operator ������ (�Ű�����...)
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
		// �׳� x�� ��� �� + �Լ��� ȣ���� ��ü�� X�����̴�.
		result.X = X + pt.X;
		result.Y = Y + pt.Y;
		
		return result;
	}
	// �Լ��� ���·� �̷���� �ֱ⿡ �����ε��� �����ϴ�.
	FPoint operator + (int Number) const
	{
		FPoint result;
		result.X = X + Number;
		result.Y = Y + Number;
		
		return result;
	}
	// �Ű������� �־��� ��� ���ϱ� ������ �ǰ�,
	// ���� ��� �������� �ȴ�.
	int operator * () const
	{
		return X;
	}
	// �����׼��� ��� 
	int& operator [] (int Index)
	{
		// assert�� bool������ ���� �� �ߴ����� true�� �ɸ��� �ܼ�â���� �α׸� �����ش�.
		assert(Index >= 0 && Index <= 1);
		/*if (Index < 0 && Index > 1)
		{
		
		}
		*/

		if (Index == 0)
			return X;
		
		return Y;
	}

	// new�� delete�� ������
	void* operator new (size_t Size)
	{
		return &Pool[0];
	}
	// ��ġ����.
	const FPoint& operator ++ ()
	{
		++X;
		++Y;
		return *this;
	}
	// ��ġ���� (�Ű������� int�� �־���� �����ϴ�)
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
		�ʱ�ȭ ����:
			���	�ʱ�ȭ ����Ʈ : ��� �������� ��ü ���� �� ��� �ʱ�ȭ�˴ϴ�.
			������ ���� �ʱ�ȭ : ��ü�� ������ �� ������ ���� ������ �ʱ�ȭ�� �̷�����ϴ�.
		����:
			��� �ʱ�ȭ ����Ʈ�� �Ϲ������� �� ȿ�����Դϴ�. 
			Ư�� ������ ��ü�� const ����� ��� ���̰� �� �ε巯���ϴ�.
	*/

	// ������ ���� �ʱ�ȭ
	/*
	FString()
	{
		Text = nullptr;
		Count = 0;
	}
	*/

	// ��� �ʱ�ȭ ����Ʈ
	FString() : 
		Text(nullptr),		// �����Ҵ��� �Ǿ����� ��� nullptr�� �ʱ�ȭ
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

	// ���� ������
	FString(const FString& str)
	{
		Count = str.Count;
		Text = new char[Count + 1];
		memset(Text, 0, Count + 1);

		strcpy_s(Text, Count + 1, str.Text);
	}

	// �̵������ڸ� �̿��� �޸� �̵�.
	FString(FString&& str)
	{
		// �̷������� �ϸ� ��������ڿ� �ٸ��ٰ� ������ �ӵ��� �� ������.
		/*{
			Count = str.Count;
			Text = new char[Count + 1];
			memset(Text, 0, Count + 1);

			strcpy_s(Text, Count + 1, str.Text);
		}*/

		// �޸� �̵�����
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
			Text = new char[Count + 1];		// ������ null���ڸ� ���� +1�� ���ش�.
			memset(Text, 0, Count + 1);		// ������ null���ڸ� ���� +1�� ���ش�.
		}
		else
		{
			// ���̰� ������� ���Ҵ��� ����� ������ ���⿡ ������.
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
			Text = new char[Count + 1];		// ������ null���ڸ� ���� +1�� ���ش�.
			memset(Text, 0, Count + 1);		// ������ null���ڸ� ���� +1�� ���ش�.
		}
		else
		{
			// ���̰� ������� ���Ҵ��� ����� ������ ���⿡ ������.
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
			Text = new char[Count + 1];		// ������ null���ڸ� ���� +1�� ���ش�.
			memset(Text, 0, Count + 1);		// ������ null���ڸ� ���� +1�� ���ش�.
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
			Text = new char[Count + 1];		// ������ null���ڸ� ���� +1�� ���ش�.
			memset(Text, 0, Count + 1);		// ������ null���ڸ� ���� +1�� ���ش�.
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
		// �� ���ڿ� ���� ������ true Ʋ���� false ��ȯ
		return strcmp(Text, str.Text) == 0;	
	}

	bool operator == (const char* str) const
	{
		// �� ���ڿ� ���� ������ true Ʋ���� false ��ȯ
		return strcmp(Text, str) == 0;
	}

	bool operator != (const FString& str) const
	{
		// �� ���ڿ� ���� Ʋ���� true ������ false ��ȯ
		return strcmp(Text, str.Text) != 0;
	}

	bool operator != (const char* str) const
	{
		// �� ���ڿ� ���� Ʋ���� true ������ false ��ȯ
		return strcmp(Text, str) != 0;
	}

	// ������
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

// Array Ŭ������ ������.
class CArray
{
private:
	int* mArr;
	int mArrLength;

public:
	// �����ڷ� ���ϴ� ���� �迭 ����
	CArray(int length) : mArrLength(length)
	{
		mArr = new int[length];
	}

	int& operator[] (int index)
	{
		if (index < 0 || index >= mArrLength)
		{
			std::cout << "������ �̻��ϼ���." << std::endl;
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
	// Ŀ���� �ڷ����� ��� �⺻ �����ڵ��� �����ε��� �ȵǾ��־� ������ ���.
	// p1�� + �Լ�ȣ���Ѵٴ� ���̴�.
	p3 = p1 + p2;			// FPoint operator + �Լ��� ���� ����� �����ϴ�. (������ fail) 
	// �������� ���ϴ� ���� + ������ �Լ� ȣ��
	int Number = 10 + 20;

	p3 = p1 + 50;
	std::cout << p3.X << " | " << p3.Y << std::endl;
	std::cout << *p1 << " | " << *p2 << std::endl;
	std::cout << p1[1] << std::endl;
	//std::cout << p1[2] << std::endl;			// assert ���� Ȯ�ο�
	
	FPoint* pt1 = new FPoint;
	++p1;			// ��ġ������ ����Ͽ� ������ ����.
	p1++;			// ��ġ������ ����Ͽ� ������ ����.

	FString str;	
	str = "���ڿ�";

	FString str1;
	str1 = "�׽�Ʈ";

	FString strResult;
	strResult = str + str1;

	std::cout << *strResult << std::endl;		// ������
	
	FString strPE = str;
	strPE = " ���� ���� ������";
	// �ӽð�ü�� ������.
	// 1. �����Ϸ� ����ȭ�� ���� �̵������ڵ� ���� �ʴ´�.
	// 2. ũ������ ���� �ʴ´�. (�ӽø޸� ������ ������ �ִ�.)
	FString("�ӽð�ü");							// ����� �ٷ� �Ҹ��ڰ� ����ȴ�.
	// �ӽð�ü�� ������ ��� �ӽð�ü�� ���Ű� �ȵȴ�.
	// �ӽð�ü�� ���Թ��� strTemp�� ���ŵǸ�,
	// �ӽð�ü�� ���ŵ� �Ͱ� ����.
	FString strTemp = FString("�ӽð�ü ����");	// ����� �Ҹ��� ������ �ȵȴ�. (������ �νĵǱ� ����)
	std::cout << "str���� �ּҰ� : " << &strTemp << std::endl;

	strResult += " : �ٿ�������";
	strResult += str1;

	std::cout << "str����Ʈ �ּҰ� : " << *strResult << std::endl;
	std::cout << "str����Ʈ ���� : " << strResult.Length() << std::endl;

	FString SplitLeft = strResult.Split(":");
	//std::cout << strResult.Text << std::endl;
	
	// �����׼��� ������ �Լ��� ���۷����� ������ ������ ����.
	//p1 = 100;		// �����׼��� ����� ����.

	return 0;
}