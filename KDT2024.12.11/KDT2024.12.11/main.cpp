#include <iostream>
#include <functional>

/*
	��ü���� ���α׷���(OOP) : ���� ��ü�� �����ؼ� �ϳ��� 
							�ϼ��� ���α׷��� �������� ���.
	Ŭ���� : ��ü�� ����� ���� ����.
	Ŭ������ �̿��ؼ� ������� ����(�ν��Ͻ�)�� ��ü��� �Ѵ�.
	Ŭ������ ��������� �����Լ��̴�.

	����ü�� Ŭ������ ���� : Ŭ������ �Լ��� ���� �� �ִ�.

	����������
	Ŭ���� ���� : Ŭ������ ������ �Լ� ���� �ǹ��Ѵ�.
	Ŭ���� �ܺ� : Ŭ���� ����Լ� ���� �ٸ� �Լ� ���� �ǹ��Ѵ�.

	public : Ŭ������ ����ü ���� Ȥ�� �ܺο��� ��� ������ ����.
			�� ����ü�� ��𼭵� �ҷ��� �� �����Ƿ� public�� �ǹ�.
	private : Ŭ������ ����ü ���ο����� ������ �����ϰ�, �ܺο����� ������ �Ұ���. 
			�� Ŭ������ �⺻ �����������̴�.
	protected : ����� ���� �Լ��ȿ����� ������ ����.

	�޸� ����ȭ �޸� Ǯ�� ã�ƺ���.	
*/

class CPlayer
{
	/*
		�����ڿ� �Ҹ���
		������ : �� Ŭ������ �̿��Ͽ� ��ü�� ������ �� 
				�ڵ����� ȣ��Ǵ� �Լ��̴�.
		�Ҹ��� : �� Ŭ������ �̿��Ͽ� ������ ��ü�� �޸𸮿��� ���ŵ� �� �ڵ����� ȣ��Ǵ� �Լ��̴�.
				�� �Ҹ��ڴ� �����ε��� ���� �ʴ´�.
	*/
public:
	// ������ : �ַ� �ʱ�ȭ �� �� ���� ����Ѵ�.
	// ������ �ڿ� : �������(�ʱⰪ)�� �̴ϼȶ�������� �Ѵ�.
	CPlayer() :
		mAttack(3),
		mDefense(20),
		mName{}
	{
		std::cout << "CPlayer ������" << std::endl;

	}
	/*
		���� ������ : ��ü�� �����ؼ� ���ο� ��ü�� ���� �� ����Ѵ�.
					Ŭ������ ���� ��� �����Ϸ��� �ڵ����� ��������ڵ� �ϳ� ������ش�.
		�������� : �����͸� �ִ� �״�� �����Ѵ�.
					�����ͺ������� �ּҰ� ������ �� �ֱ� ����.
		�������� : �����Ҵ�� �����Ͱ� ���� ���
					���� �����ڿ��� ������ ���� �����ϰ� ����
					�����ϴ� �����̴�.
		
	*/ 
	CPlayer(const CPlayer& ref)
	{

		//*this = ref;
		//mArray = ref.mArray;
		
		memcpy(mArray, ref.mArray, sizeof(int) * 10);
		std::cout << ref.mArray << std::endl;
	}

	// �Ҹ��� : ��ü�� ������ �۾��� �� �� ���� ����Ѵ�.
	~CPlayer()
	{
		std::cout << "CPlayer �Ҹ���" << std::endl;
	}

	CPlayer(const char* Name)
	{
		strcpy_s(mName, Name);
		std::cout << "CPlayer ���� ������" << std::endl;
	}

public:
	char mName[32];
	int mAttack;
	int mDefense;
	// static ��� ������ �� Ŭ���� �ܺο� 
	// ���� ����κ��� �־�� �Ѵ�.
	// static ��� ������ �� Ŭ������ �̿��Ͽ�
	// ��ü�� ������ �� ������ �޸� ũ�⿡ ������ ����.
	// ��, ��ü�� �޸� ũ�⿡ �������Ѵ�.
	// ������ �޸� ������ 1�� ��������� ���
	// ��ü�� �����ϴ� �޸𸮰� �ȴ�.
	static int mMP;
	// ����� ���ÿ� �ʱ�ȭ
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
		����Լ� �ڿ� const�� ������ �� �Լ������� 
		Ŭ������ ������� ���� ������ �� ����.
		const ��ü�� ȣ���� �� �ִ� �Լ��� �ȴ�.
	*/
	int GetHP()	const
	{
		return HP;
	}

	void Output()
	{
		// ��������� ����ϸ� �տ� this->�� ������ ���̴�.
		// this : �ڱ� �ڽ��� �޸� �ּҸ� �ǹ�.
		//			this�� ��ü ����Լ�()�� ȣ���� ��
		//			��ü�� �޸� �ּҰ� this�� ���� �ȴ�.
		//			�Ź� ȣ�� �� ������ this�� ȣ���ϴ� ��ü�� ������ ���̴�.
		std::cout << this->mAttack << std::endl;
	}

	void SetTest(int Num1, int Num2)
	{
		
	}

	/*
		static ����Լ������� this�� ����� �� ����.
		�׷��� �Ϲ� ����������� ������ �Ұ����ϰ�
		static ����������� ������ �����ϴ�.
		�ֳ��ϸ� �Ϲ� ��������� ����ϸ� �տ� ��� ��ü��
		������������� �����ϱ� ����
		this->�� �����Ǵµ� static ����Լ������� this��
		����� �� �����Ƿ� �Ϲ� ��������� ����� �� ���� ���̴�.
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
	// new�� ���� �Ұ�� �޸� ����ȭ�� �Ͼ �� �ִ�.
	// �޸� ����ȭ�� �޸𸮸� �Ҵ��Ҷ� ���������� �Ҵ�ȴٴ�
	// ������ ��� �߰��߰��� ���� �޸𸮵��� ���ԵǴ� �����̴�.
	// ���δ���ȭ : ���μ����� �ʿ��� �纸�� �� ū �޸𸮰� �Ҵ�� ��.
	//		���� �Ҵ���� : 500byte
	//		���� ������ : 300byte
	//		200byte��ŭ�� ���δ���ȭ�� �߻�.
	// �ܺ� ����ȭ : �޸� �Ҵ� ������ �ݺ��� �� �޸� �߰��߰���
	//				���� �޸𸮰� ���ԵǴ� �����̴�.
	//				���� �޸𸮸� ���ϸ� �޸𸮴� ���� ������,
	//				���� �Ҵ��� ������ �����Ͽ� ����� �����̴�.
	// ����¡ : �ܺ� �ذ�, ���� ����
	// ���׸����̼� : ���� �ذ�, �ܺ� ����
	// �޸�Ǯ : �̸� ū �޸� ������ �������� �ű⼭ �޸𸮸� ������ ����ϴ� ���.
	//			�� ����/�ܺ� ����ȭ �ذ���.
	std::cout << player.mAttack << std::endl;
	std::cout << OutputGlobal << std::endl;
	
	CPlayer* kkk = new CPlayer;
	//delete kkk;				// delete�� ���ҽ� �Ҹ��ڰ� ������� ����.

	CPlayer* jjj = new CPlayer();
	delete jjj;
	jjj = new CPlayer("aaa");

	// jjj��ü�� ���ڷ� �־ ���� ������ִ� 
	// ��ü�� �����͸� jjj��ü�� �����ͷ�
	// �����Ͽ� ������ش�.
	CPlayer* lll = new CPlayer(*jjj);		// jjj�� ������ lll�� ����.
	delete lll;

	// const ��ü�� ���� ��� ��������� ���� ������ �� ����.
	// const�� const�� ���� ������ �Լ��� �ҷ��� �� �ִ�.
	const CPlayer ppp;
	ppp.GetHP();
	
	// const_cast : const�� �����ش�.
	CPlayer* qqq = const_cast<CPlayer*>(&ppp);
	qqq->GetHP();
	// ��ü.Output()
	player.Output();		// �Ϲ� Ŭ������ ������� ��ü�� ����.
	
	// ��ü�ּ�->Output();
	// �Ʒ� ȣ���� �� this�� jjj ��ü�� �޸� �ּҰ� �ȴ�.
	jjj->Output();			// �����ͷ� ������� ��ü�� ����.
	// �Ʒ� ȣ���� �� this�� kkk ��ü�� �޸� �ּҰ� �ȴ�.
	kkk->Output();
	std::cout << "jjj : " << jjj << std::endl;
	std::cout << "kkk : " << kkk << std::endl;
	//std::cout << "jjj Output Func : " << jjj->Output() 

	ppp.mMP = 1234;
	jjj->mMP = 5678;
	kkk->mMP = 9101;
	std::cout << "MP�� 1234 : " << ppp.mMP << std::endl;
	std::cout << "MP�� 1234 : " << jjj->mMP << std::endl;
	std::cout << "MP�� 1234 : " << kkk->mMP << std::endl;

	kkk->OutputStatic();
	jjj->OutputStatic();

	void(*Func)() = CPlayer::OutputStatic;

	std::cout << CPlayer::OutputStatic << std::endl;
	std::cout << &CPlayer::SetDefense << std::endl;

	void(CPlayer:: * Func1)() = &CPlayer::Output;

	std::cout << "��� �Լ������� : " << Func1 << std::endl;

	// ����Լ� �����ʹ� ȣ�� �� this�� ���ε� �� ��ü�� �����ؾ��Ѵ�.
	// (��ü.*����Լ�������)();
	// (��ü�ּ�->*����Լ�������)();
	(kkk->*Func1)();
	
	// ����1
	std::function<void()> func;
	func = std::bind(&CPlayer::Output, kkk);
	func();

	// ����2
	// include <functional> ���� �� 
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