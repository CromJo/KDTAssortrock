#include <iostream>

#define SAFE_DELETE(p) if(p) {delete P :;

class CSingleton
{
	// 생성자와 소멸자가 private 이라면
	// 이 클래스를 이용하여 생성하는 객체는
	// 클래스 외부에서 생성이 불가능하다.

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
	// 생성자가 private이라서 클래스 외부에서
	// 객체 생성을 할 경우 생성자 호출이 불가능하여
	// 객체 생성 불가.
	// CSingleton instance;		<- 에러
	
	// 포인터는 객체를 생성하는 것이 아닌 객체의
	// 메모리 주소를 저장하는 변수이므로 선언 가능.
	CSingleton* instance;

	std::cout << CSingleton::GetInstance() << std::endl;
	CSingleton::DestroyInstance();

	return 0;
}