#include "ObjectManager.h"
#include "Player.h"

DEFINITION_SINGLE(CObjectManager)

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
}

bool CObjectManager::Init()
{
	CreateObj<CPlayer>();

	return true;
}

void CObjectManager::Update(float DeltaTime)
{
	std::list<CObject*>::iterator	iter;
	std::list<CObject*>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		(*iter)->Update(DeltaTime);

		if (!(*iter)->GetActive())
		{
			SAFE_DELETE(*iter);
			iter = mObjList.erase(iter);
			continue;
		}

		++iter;
	}

	// �浹ó��
	if (mObjList.size() >= 2)
	{
		iterEnd = mObjList.end();
		--iterEnd;

		for (iter = mObjList.begin(); iter != iterEnd;)
		{
			std::list<CObject*>::iterator	iter1 = iter;
			++iter1;

			std::list<CObject*>::iterator	iter1End = mObjList.end();

			bool	IterErase = false;

			for (; iter1 != iter1End;)
			{
				if ((*iter)->GetPos().X == (*iter1)->GetPos().X &&
					(*iter)->GetPos().Y == (*iter1)->GetPos().Y)
				{
					bool	Death = false;
					bool	Death1 = false;

					// �÷��̾�� �� �Ѿ�����
					// ���� �÷��̾� �Ѿ����� �Ǵ��Ѵ�.
					switch ((*iter)->CollisionEnable(*iter1))
					{
					case ECollisionType::Damage:
						(*iter)->Damage(-1);
						break;
					case ECollisionType::Score:
						//(*iter)->Score
						break;
					}

					if (Death1)
					{
						SAFE_DELETE(*iter1);
						iter1 = mObjList.erase(iter1);
						iter1End = mObjList.end();
						iterEnd = iter1End;
						--iterEnd;
					}

					if (Death)
					{
						IterErase = true;
						SAFE_DELETE(*iter);
						iter = mObjList.erase(iter);
						iterEnd = mObjList.end();
						--iterEnd;
						break;
					}

					if (Death1)
						continue;
				}

				// �浹�� �ȵǴ� ��� ������ üũ�Ѵ�.
				++iter1;
			}

			if (!IterErase)
				++iter;
		}
	}
}

void CObjectManager::Output(char* OutputBuffer)
{
	std::list<CObject*>::iterator	iter;
	std::list<CObject*>::iterator	iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Output(OutputBuffer);
	}
}
