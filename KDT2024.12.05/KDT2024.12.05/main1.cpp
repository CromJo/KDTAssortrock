#include <iostream>
#include <Windows.h>

// testInt�� �̿��Ͽ� int Ÿ�� ������ ������ �� �ְ� ���ش�.
typedef int kim;

int main()
{
	char Text[32] = {};		// 0���� �ʱ�ȭ �� ����
	
	strcpy_s(Text, "�� ���̾�");

	std::cout << Text << std::endl;

	// typedef : Ÿ���� �ٸ� �̸����� ����� �� �ֵ��� Ÿ���� �̸��� �߰����ش�.
	// Ÿ���� �̸��� �߰����ش�.
	size_t Count = strlen(Text);
	//strlen(Text);	// ���ڿ��� ���̸� Ȯ���ϴ� �Լ�

	std::cout << "���ڿ� ���� : " << Count << std::endl;

	// strcmp : ���ʰ� �����ʿ� ���� ���ڿ��� ���� ������ ��.
	//			������ 0�� ��ȯ, �ٸ� ��� 0�� �ƴ� ������ ��ȯ.
	if (strcmp("aa", "aa") == 0)
	{
		std::cout << "����." << std::endl;
	}
	else
	{
		std::cout << "�ٸ���." << std::endl;
	}

	// strcat_s :  �������� ���ڿ��� ������ ���ڿ��� �ڿ� �ٿ��ش�.
	strcat_s(Text, "aabb cc");
	std::cout << "���̱� ��� : " << Text << strcat_s(Text, "Yoshi ") << std::endl;

	wchar_t Text111 = '��';		// 2byte�� �Ǿ��ִ� char
	char Text222 = '��';

	std::wcout.imbue(std::locale("kor"));
	std::wcout << L"�ױ�" << std::endl;

	std::wstring

	return 0;
}