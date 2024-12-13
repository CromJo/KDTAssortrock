#include <iostream>

class CHuman
{
public:
	CHuman();
	~CHuman();

private:
	char mName[32];
	int mAtk = 0;
	int mDfs = 0;
	int mCri = 0;
	int mSpeed = 0;

protected:
	char* GetName() { return mName; }
	int GetAttack() { return mAtk; }
	int GetDefense() { return mDfs; }
	int GetCritical() { return mCri; }
	int GetSpeed() { return mSpeed; }
};

class CArm : public CHuman
{
public:
	CArm();
	~CArm();

private:
	char mArmName[32];
	int mArmAtk = 0;
	int mArmDfs = 0;
	int mArmCri = 0;

protected:
	char* GetArmName() { return mArmName; }
	int GetArmAttack() { return mArmAtk; }
	int GetArmDefense() { return mArmDfs; }
	int GetCritical() { return mArmCri; }
};

CArm::CArm()
{
	std::cout << "��ģ ��ٶ� ����ĵ�. : " << std::endl;
}
CArm::~CArm()
{
	std::cout << "������ �ʴ� ����� �Ƿ� �ϳ� : " << std::endl;
}

CHuman::CHuman()
{
	std::cout << "���� ������ �ɰž� :" << std::endl;
}
CHuman::~CHuman()
{
	std::cout << "�ƹ��� ���� �������� �ʾ� :" << std::endl;
}


int main()
{
	CArm arm;
	CHuman human;

	return 0;
}
