#include <iostream>

int main()
{
	FILE* File = nullptr;

	// Mode 1��
	// r : ���� �о����
	// w : ���� �����
	// a : ������ ������ ����� ������ ������,
	//		���� ���� �о �� �ں��� �߰��� ���ش�.
	// Mode 2��
	// t : �ؽ�Ʈ����
	// b : ���̳ʸ� ����
	// r+ : ������ ������ �ش� ������ �б�/���� �Ѵ� �����ϰ� ����д�. 
	//		������ ������ ����.
	// w+ : ������ ������ �ش� ������ �б�/���� �Ѵ� �����ϰ� ����д�.
	//		������ ������ �����.
	// a+ : ������ ������ �� ���������� �б�/���� �Ѵ� �����ϰ� ����д�.
	//		������ ������ �����.
	fopen_s(&File, "TestFile.txt", "wt");

	// ������ ���� ���Ͽ� �����͸� ������ �� �ִ� ���
	if (nullptr != File)
	{
		fputc('A', File);
		fputs("\nHello World", File);
		
		int Number = 100;
		fprintf(File, "Number = %d", Number);

		// ����� ���� ��Ʈ���� �ݾ��ش�.
		// �ȴ����� ������ ��� ������� �ɷ� �����ȴ�.
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