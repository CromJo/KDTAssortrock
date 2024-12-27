#include "ObjectManager.h"
#include "Player.h"
#include "Stage.h"
#include "StageManager.h"

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
	std::list<CObject*>::iterator iter;
	std::list<CObject*>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd;)
	{
		(*iter)->Update(DeltaTime);

		if (!(*iter)->GetActive())
		{
			SAFE_DELETE(*iter);
			mObjectList.erase(iter);

			continue;
		}

		iter++;
	}

	// 충돌처리
	if (mObjectList.size() >= 2)
	{
		iterEnd = mObjectList.end();
		iterEnd--;

		for (iter = mObjectList.begin(); iter != iterEnd;)
		{
			std::list<CObject*>::iterator iter1 = iter;
			iter1++;

			std::list<CObject*>::iterator iter1End = mObjectList.end();

			bool IterErase = false;

			for (; iter1 != iter1End;)
			{
				if ((*iter)->GetPos().X == (*iter1)->GetPos().X &&
					(*iter)->GetPos().Y == (*iter1)->GetPos().Y)
				{
					bool Death1 = false;
					bool Death2 = false;

					// 플레이어 및 적 총알인지 체크
					// 적과 플레이어 총알인지 체크
					switch ((*iter)->CollisionEnable(*iter1))
					{
					case ECollisionType::Damage:
						Death1 = (*iter)->Damage((*iter1)->GetDamage());
						Death2 = (*iter1)->Damage((*iter)->GetDamage());
						break;
					case ECollisionType::Heal:
						break;
					case ECollisionType::Power:
						break;
					case ECollisionType::Score:
						CStageManager::GetInst()->GetStage()->AddScore(10);

						// iter가 Player일시
						if (dynamic_cast<CPlayer*>(*iter))
						{
							Death1 = true;
						}
						else
						{
							Death2 = true;
						}

						Death1 = (*iter)->Damage((*iter1)->GetDamage());
						Death2 = (*iter1)->Damage((*iter)->GetDamage());
						break;
					}

					if (Death1)
					{
						SAFE_DELETE(*iter1);
						iter1 = mObjectList.erase(iter1);
						iter1End = mObjectList.end();
						iterEnd = iter1End;
						iterEnd--;

						if (mObjectList.size() == 1)
						{
							IterErase = true;
						}
					}
					if (Death2)
					{
						IterErase = true;
						SAFE_DELETE(*iter);
						iter = mObjectList.erase(iter);
						iterEnd = mObjectList.end();
						iterEnd--;

						break;
					}

					if (Death1)
						continue;

					(*iter)->CollisionEnable(*iter1);

				}

				// 충돌 안되는 경우 다음을 체크
				iter1++;
			}

			if (!IterErase)
			{
				iter++;
			}
		}
	}
}

void CObjectManager::Output(char* OutputBuffer)
{
	std::list<CObject*>::iterator iter;
	std::list<CObject*>::iterator iterEnd = mObjectList.end();

	for (iter = mObjectList.begin(); iter != iterEnd; iter++)
	{
		(*iter)->Output(OutputBuffer);
	}
}

