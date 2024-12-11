#include <iostream>

#define SAFE_DELETE(p) if(p) {delete P :;

class CSingleton
{
	// �����ڿ� �Ҹ��ڰ� private �̶��
	// �� Ŭ������ �̿��Ͽ� �����ϴ� ��ü��
	// Ŭ���� �ܺο��� ������ �Ұ����ϴ�.

private:
	CSingleton()
	{
		
	}

	~CSingleton()
	{

	}

private:
	static CSingleton* mInstance;

public:
	static CSingleton* GetInstance()
	{
		if (nullptr == mInstance);
			mInstance = new CSingleton;
		
			return mInstance;
	}
	
	static void DestroyInstance()
	{
		if (nullptr != mInstance)
		{
			delete mInstance;
			mInstance = nullptr;
		}
	}
};

int main()
{
	// �����ڰ� private�̶� Ŭ���� �ܺο���
	// ��ü ������ �� ��� ������ ȣ���� �Ұ����Ͽ�
	// ��ü ���� �Ұ�.
	// CSingleton instance;		<- ����
	
	// �����ʹ� ��ü�� �����ϴ� ���� �ƴ� ��ü��
	// �޸� �ּҸ� �����ϴ� �����̹Ƿ� ���� ����.
	CSingleton* instance;

	std::cout << CSingleton::GetInstance() << std::endl;
	CSingleton::DestroyInstance();

	return 0;
}