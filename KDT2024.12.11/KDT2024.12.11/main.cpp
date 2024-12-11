#include <iostream>
#include <functional>

/*
	객체지향 프로그래밍(OOP) : 여러 객체를 조립해서 하나의 
							완성된 프로그램을 만들어나가는 방법.
	클래스 : 객체를 만들기 위한 수단.
	클래스를 이용해서 만들어준 변수(인스턴스)를 개체라고 한다.
	클래스도 사용자정의 지정함수이다.

	구조체와 클래스의 차이 : 클래스는 함수도 만들 수 있다.

	접근지정자
	클래스 내부 : 클래스에 만들어둔 함수 안을 의미한다.
	클래스 외부 : 클래스 멤버함수 외의 다른 함수 안을 의미한다.

	public : 클래스나 구조체 내부 혹은 외부에서 모두 접근이 가능.
			※ 구조체는 어디서든 불러올 수 있으므로 public을 의미.
	private : 클래스나 구조체 내부에서는 접근이 가능하고, 외부에서는 접근이 불가능. 
			※ 클래스의 기본 접근지정자이다.
	protected : 상속을 받은 함수안에서만 접근이 가능.

	메모리 단편화 메모리 풀링 찾아보기.	
*/

class CPlayer
{
	/*
		생성자와 소멸자
		생성자 : 이 클래스를 이용하여 객체를 생성할 때 
				자동으로 호출되는 함수이다.
		소멸자 : 이 클래스를 이용하여 생성된 객체가 메모리에서 제거될 때 자동으로 호출되는 함수이다.
				※ 소멸자는 오버로딩이 되지 않는다.
	*/
public:
	// 생성자 : 주로 초기화 할 때 많이 사용한다.
	// 생성자 뒤에 : 멤버변수(초기값)을 이니셜라이저라고 한다.
	CPlayer() :
		mAttack(3),
		mDefense(20),
		mName{}
	{
		std::cout << "CPlayer 생성자" << std::endl;

	}
	/*
		복사 생성자 : 객체를 복사해서 새로운 객체를 만들어낼 때 사용한다.
					클래스에 없을 경우 컴파일러는 자동으로 복사생성자도 하나 만들어준다.
		얕은복사 : 데이터를 있는 그대로 복사한다.
					포인터변수들의 주소가 공유될 수 있기 때문.
		깊은복사 : 동적할당된 데이터가 있을 경우
					복사 생성자에서 공간도 새로 생성하고 값만
					복사하는 형태이다.
		
	*/ 
	CPlayer(const CPlayer& ref)
	{

		//*this = ref;
		//mArray = ref.mArray;
		
		memcpy(mArray, ref.mArray, sizeof(int) * 10);
		std::cout << ref.mArray << std::endl;
	}

	// 소멸자 : 객체의 마무리 작업을 할 때 많이 사용한다.
	~CPlayer()
	{
		std::cout << "CPlayer 소멸자" << std::endl;
	}

	CPlayer(const char* Name)
	{
		strcpy_s(mName, Name);
		std::cout << "CPlayer 인자 생성자" << std::endl;
	}

public:
	char mName[32];
	int mAttack;
	int mDefense;
	// static 멤버 변수는 이 클래스 외부에 
	// 변수 선언부분이 있어야 한다.
	// static 멤버 변수는 이 클래스를 이용하여
	// 객체를 생성할 때 생성할 메모리 크기에 영향이 없다.
	// 즉, 객체의 메모리 크기에 미포함한다.
	// 별도의 메모리 공간이 1개 만들어지며 모든
	// 객체가 공유하는 메모리가 된다.
	static int mMP;
	// 선언과 동시에 초기화
private:
	int HPMax = 100;
	const int& HP = HPMax;
	int* mArray[10];
public:
	void SetDefense(int Defense)
	{
		mDefense = Defense;
	}

	int GetDefense()
	{
		return mDefense;
	}

	/*
		멤버함수 뒤에 const가 붙으면 이 함수에서는 
		클래스의 멤버변수 값을 변경할 수 없다.
		const 객체가 호출할 수 있는 함수가 된다.
	*/
	int GetHP()	const
	{
		return HP;
	}

	void Output()
	{
		// 멤버변수를 사용하면 앞에 this->가 생략된 것이다.
		// this : 자기 자신의 메모리 주소를 의미.
		//			this는 객체 멤버함수()를 호출할 때
		//			객체의 메모리 주소가 this에 들어가게 된다.
		//			매번 호출 할 때마다 this가 호출하는 객체가 지정될 것이다.
		std::cout << this->mAttack << std::endl;
	}

	void SetTest(int Num1, int Num2)
	{
		
	}

	/*
		static 멤버함수에서는 this를 사용할 수 없다.
		그래서 일반 멤버변수에는 접근이 불가능하고
		static 멤버변수에만 접근이 가능하다.
		왜냐하면 일반 멤버변수를 사용하면 앞에 어느 객체의
		멤버변수인지를 구분하기 위한
		this->가 생략되는데 static 멤버함수에서는 this를
		사용할 수 없으므로 일반 멤버변수를 사용할 수 없는 것이다.
	*/
	static void OutputStatic()
	{
		//std::cout << this->mAttack << std::endl;
		//std::cout << this
	}
};

int CPlayer::mMP = 500;

void OutputGlobal()
{
	std::cout << "OutputGlobal" << std::endl;
}

int main()
{
	//CPlayer* player = (CPlayer*)malloc(sizeof(CPlayer));
	
	CPlayer player;
	// new를 많이 할경우 메모리 단편화가 일어날 수 있다.
	// 메모리 단편화는 메모리를 할당할때 연속적으로 할당된다는
	// 보장이 없어서 중간중간의 작은 메모리들이 남게되는 현상이다.
	// 내부단편화 : 프로세스가 필요한 양보다 더 큰 메모리가 할당될 때.
	//		실제 할당공간 : 500byte
	//		실제 사용공간 : 300byte
	//		200byte만큼의 내부단편화가 발생.
	// 외부 단편화 : 메모리 할당 해제가 반복될 때 메모리 중간중간의
	//				작은 메모리가 남게되는 현상이다.
	//				남는 메모리를 합하면 메모리는 많이 있지만,
	//				실제 할당할 공간이 부족하여 생기는 현상이다.
	// 페이징 : 외부 해결, 내부 존재
	// 세그멘테이션 : 내부 해결, 외부 존재
	// 메모리풀 : 미리 큰 메모리 공간을 만들어놓고 거기서 메모리를 가져다 사용하는 기법.
	//			※ 내부/외부 단편화 해결방법.
	std::cout << player.mAttack << std::endl;
	std::cout << OutputGlobal << std::endl;
	
	CPlayer* kkk = new CPlayer;
	//delete kkk;				// delete를 안할시 소멸자가 실행되지 않음.

	CPlayer* jjj = new CPlayer();
	delete jjj;
	jjj = new CPlayer("aaa");

	// jjj객체를 인자로 넣어서 새로 만들어주는 
	// 객체의 데이터를 jjj객체의 데이터로
	// 복사하여 만들어준다.
	CPlayer* lll = new CPlayer(*jjj);		// jjj를 복제한 lll을 만듦.
	delete lll;

	// const 객체를 만들 경우 멤버변수의 값을 변경할 수 없다.
	// const는 const가 붙은 변수나 함수만 불러올 수 있다.
	const CPlayer ppp;
	ppp.GetHP();
	
	// const_cast : const를 없애준다.
	CPlayer* qqq = const_cast<CPlayer*>(&ppp);
	qqq->GetHP();
	// 객체.Output()
	player.Output();		// 일반 클래스로 만들어진 객체만 가능.
	
	// 객체주소->Output();
	// 아래 호출할 시 this는 jjj 객체의 메모리 주소가 된다.
	jjj->Output();			// 포인터로 만들어진 객체만 가능.
	// 아래 호출할 시 this는 kkk 객체의 메모리 주소가 된다.
	kkk->Output();
	std::cout << "jjj : " << jjj << std::endl;
	std::cout << "kkk : " << kkk << std::endl;
	//std::cout << "jjj Output Func : " << jjj->Output() 

	ppp.mMP = 1234;
	jjj->mMP = 5678;
	kkk->mMP = 9101;
	std::cout << "MP값 1234 : " << ppp.mMP << std::endl;
	std::cout << "MP값 1234 : " << jjj->mMP << std::endl;
	std::cout << "MP값 1234 : " << kkk->mMP << std::endl;

	kkk->OutputStatic();
	jjj->OutputStatic();

	void(*Func)() = CPlayer::OutputStatic;

	std::cout << CPlayer::OutputStatic << std::endl;
	std::cout << &CPlayer::SetDefense << std::endl;

	void(CPlayer:: * Func1)() = &CPlayer::Output;

	std::cout << "멤버 함수포인터 : " << Func1 << std::endl;

	// 멤버함수 포인터는 호출 시 this에 바인딩 될 객체를 지정해야한다.
	// (객체.*멤버함수포인터)();
	// (객체주소->*멤버함수포인터)();
	(kkk->*Func1)();
	
	// 사용법1
	std::function<void()> func;
	func = std::bind(&CPlayer::Output, kkk);
	func();

	// 사용법2
	// include <functional> 선언 후 
	func = OutputGlobal;
	func();

	std::function<void(int, int)> func2;
	func2 = std::bind(CPlayer::SetDefense, player, std::placeholders::_1,
		std::placeholders::_2);

	func2(10, 20);

	player.mAttack = 100;
	player.mDefense = 200;

	player.SetDefense(50);
	return 0;
}