/*
	String Ŭ���� ���� operator
	+, = , +=, ==, !=, *(������) ���ڿ� ��ȯ

	���� �Լ�
	Length() : ���ڿ� �� ��ȯ
	Split() : ���ڿ� �и� �Լ�. ���ڷ� �и��� ���ڿ���
			�־��ָ� �и������ش�. ���� ���ڿ��� ��ȯ�Ѵ�.

	�̵�������
	���ڿ� �̵�
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
	
	// = ������
	void operator = (const char* str)
	{
		if (Text)
		{
			delete[] Text;	// ���� �޸� ����
		}

		Count = strlen(str);		// ���� ������ ������ ����ȯ
		Text = new char[Count + 1];
		strcpy_s(Text, Count + 1, str);
	}

	// + ������ 
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

	// += ������
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
	A = "�� ���̾�";
	B = "�� ȥ�ڿԴ�?";

	CString AB;
	AB = A + B;

	CString C;
	C = "����";
	C += AB;


	std::cout << AB.Text << " | " << AB.Count << std::endl;
	std::cout << C.Text << std::endl;
	return 0;
}