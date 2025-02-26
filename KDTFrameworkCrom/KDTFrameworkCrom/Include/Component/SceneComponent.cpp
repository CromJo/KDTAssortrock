#include "SceneComponent.h"

CSceneComponent::CSceneComponent()
{
}

CSceneComponent::CSceneComponent(const CSceneComponent& Com) :
	CComponent(Com)
{
}

CSceneComponent::CSceneComponent(CSceneComponent&& Com) :
	CComponent(Com)
{
}

CSceneComponent::~CSceneComponent()
{
	size_t Size = mChildList.size();

	// Active False면 지우기
	for (size_t i = 0; i < Size; ++i)
	{
		mChildList[i]->Destroy();
	}
}

void CSceneComponent::AddChild(CSceneComponent* Child)
{
	Child->mParent = this;

	// 씬컴포넌트의 새로운 물체(자식) 추가
	mChildList.emplace_back(Child);
}

bool CSceneComponent::Init()
{
	return true;
}

bool CSceneComponent::Init(const char* FileName)
{
	return true;
}

void CSceneComponent::PreUpdate(float DeltaTime)
{
	// 부모함수 선호출
	CComponent::PreUpdate(DeltaTime);

	std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
	std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		// 
		if (!(*iter)->IsActive())
		{
			// 지워야 할 값과 마지막 값 바꾸기
			std::swap(*iter, mChildList.back());

			// SharedPointer 이므로 pop_back하면 제거됨.
			mChildList.pop_back();
			iterEnd = mChildList.end();

			continue;
		}
		// 비활성화 상태면 다음 오브젝트 검사
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}
		
		(*iter)->PreUpdate(DeltaTime);
		++iter;
	}
}

void CSceneComponent::Update(float DeltaTime)
{
	CComponent::Update(DeltaTime);

	std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
	std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		// 
		if (!(*iter)->IsActive())
		{
			// 지워야 할 값과 마지막 값 바꾸기
			std::swap(*iter, mChildList.back());

			// SharedPointer 이므로 pop_back하면 제거됨.
			mChildList.pop_back();
			iterEnd = mChildList.end();

			continue;
		}
		// 비활성화 상태면 다음 오브젝트 검사
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}
}

void CSceneComponent::PostUpdate(float DeltaTime)
{
	CComponent::PostUpdate(DeltaTime);

	std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
	std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		// 
		if (!(*iter)->IsActive())
		{
			// 지워야 할 값과 마지막 값 바꾸기
			std::swap(*iter, mChildList.back());

			// SharedPointer 이므로 pop_back하면 제거됨.
			mChildList.pop_back();
			iterEnd = mChildList.end();

			continue;
		}
		// 비활성화 상태면 다음 오브젝트 검사
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		++iter;
	}
}

void CSceneComponent::PreRender()
{
	CComponent::PreRender();

	std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
	std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		// 
		if (!(*iter)->IsActive())
		{
			// 지워야 할 값과 마지막 값 바꾸기
			std::swap(*iter, mChildList.back());

			// SharedPointer 이므로 pop_back하면 제거됨.
			mChildList.pop_back();
			iterEnd = mChildList.end();

			continue;
		}
		// 비활성화 상태면 다음 오브젝트 검사
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PreRender();
		++iter;
	}
}

void CSceneComponent::Render()
{
	CComponent::Render();

	std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
	std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		// 
		if (!(*iter)->IsActive())
		{
			// 지워야 할 값과 마지막 값 바꾸기
			std::swap(*iter, mChildList.back());

			// SharedPointer 이므로 pop_back하면 제거됨.
			mChildList.pop_back();
			iterEnd = mChildList.end();

			continue;
		}
		// 비활성화 상태면 다음 오브젝트 검사
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render();
		++iter;
	}
}

void CSceneComponent::PostRender()
{
	CComponent::PostRender();


	std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
	std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		// 
		if (!(*iter)->IsActive())
		{
			// 지워야 할 값과 마지막 값 바꾸기
			std::swap(*iter, mChildList.back());

			// SharedPointer 이므로 pop_back하면 제거됨.
			mChildList.pop_back();
			iterEnd = mChildList.end();

			continue;
		}
		// 비활성화 상태면 다음 오브젝트 검사
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostRender();
		++iter;
	}
}

CSceneComponent* CSceneComponent::Clone()
{
	return new CSceneComponent(*this);
}

void CSceneComponent::SetRelativeScale(const FVector3D& Scale)
{
	mRelativeScale = Scale;

	// 부모 유무에 따라서 예외처리가 다르게 처리되어야한다.
	// 부모가 있으면 부모값을 곱함
	if (mParent)
	{
		mWorldScale = mRelativeScale * mParent->mWorldScale;
	}
	// 부모가 없으면 자신이 부모
	else
	{
		mWorldScale = mRelativeScale;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// 자식 월드좌표 = 
		// - 자식 로컬위치 * 부모 월드크기 + 부모 월드 위치
		mChildList[i]->mWorldPosition = mChildList[i]->mRelativePosition * mWorldScale
			+ mWorldPosition;

		mChildList[i]->SetWorldScale(mChildList[i]->mRelativeScale * mWorldScale);
	}
}

void CSceneComponent::SetRelativeScale(float x, float y, float z)
{
	SetRelativeScale(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativeScale(const FVector2D& Scale)
{
	SetRelativeScale(FVector3D(Scale.x, Scale.y, 1.f));
}

void CSceneComponent::SetRelativeScale(float x, float y)
{
	SetRelativeScale(FVector3D(x, y, 1.f));
}

void CSceneComponent::SetRelativeRotation(const FVector3D& Rotation)
{
	// 상대 정보를 넣고
	mRelativeRotation = Rotation;

	// 부모인가 아닌가를 판단
	if (mParent)
	{
		mWorldRotation = mRelativeRotation + mParent->mWorldRotation;
	}
	else
	{
		mWorldRotation = mRelativeRotation;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// 회전 없이 따라만 다닌다면
		// 자식의 월드위치 값 =
		//	자식의 로컬위치의 회전값 + 부모월드위치
		mChildList[i]->mWorldPosition = 
			mChildList[i]->mRelativePosition.
			GetRotation(mWorldRotation)
			+ mWorldPosition;
		
		mChildList[i]->SetWorldRotation(mChildList[i]->mWorldRotation + mWorldRotation);
	}
}

void CSceneComponent::SetRelativeRotation(float x, float y, float z)
{
	SetRelativeRotation(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativeRotation(const FVector2D& Rotation)
{
	SetRelativeRotation(FVector3D(Rotation.x, Rotation.y, mRelativeRotation.z));
}

void CSceneComponent::SetRelativeRotation(float x, float y)
{
	SetRelativeRotation(FVector3D(x, y, mRelativeRotation.z));
}

void CSceneComponent::SetRelativeRotationX(float x)
{
	SetRelativeRotation(FVector3D(x, mRelativeRotation.y, mRelativeRotation.z));

}

void CSceneComponent::SetRelativeRotationY(float y)
{
	SetRelativeRotation(FVector3D(mRelativeRotation.x, y, mRelativeRotation.z));

}

void CSceneComponent::SetRelativeRotationZ(float z)
{
	SetRelativeRotation(FVector3D(mRelativeRotation.x, mRelativeRotation.y, z));

}

void CSceneComponent::SetRelativeRotationAxis(float Angle, const FVector3D& Axis)
{
	// 축행렬로 계산하기엔 복잡하다.
}

void CSceneComponent::SetRelativePosition(const FVector3D& Position)
{
	mRelativePosition = Position;

	if (mParent)
	{
		mWorldPosition = mRelativePosition +
			mParent->mWorldPosition;
	}
	else
	{
		mWorldPosition = mRelativePosition;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		mChildList[i]->SetWorldPosition(mChildList[i]->
			mRelativePosition + mWorldPosition);
	}
}

void CSceneComponent::SetRelativePosition(float x, float y, float z)
{
	SetRelativePosition(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativePosition(const FVector2D& Position)
{
	SetRelativePosition(FVector3D(Position.x, Position.y, mRelativePosition.z));
}

void CSceneComponent::SetRelativePosition(float x, float y)
{
	SetRelativePosition(FVector3D(x, y, mRelativePosition.z));
}

void CSceneComponent::SetWorldScale(const FVector3D& Scale)
{
	mWorldScale = Scale;

	if (mParent)
	{
		// 자식상대크기 :
		// - 자식월드크기 / 부모월드크기
		mRelativeScale = mWorldScale / mParent->mWorldScale;
	}
	else
	{
		mRelativeScale = mWorldScale;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// 자식 월드좌표 = 
		// - 자식 로컬위치 * 부모 월드크기 + 부모 월드 위치
		mChildList[i]->SetWorldScale(mChildList[i]->mRelativeScale * mWorldScale);
		
		mChildList[i]->SetWorldPosition(mChildList[i]->mRelativePosition * mWorldScale * mWorldPosition);
	}
}

void CSceneComponent::SetWorldScale(float x, float y, float z)
{
	SetWorldScale(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldScale(const FVector2D& Scale)
{
	SetWorldScale(FVector3D(Scale.x, Scale.y, mWorldScale.z));
}

void CSceneComponent::SetWorldScale(float x, float y)
{
	SetWorldScale(FVector3D(x, y, mWorldScale.z));
}

void CSceneComponent::SetWorldRotation(const FVector3D& Rotation)
{
	mWorldRotation = Rotation;

	if (mParent)
	{
		// 자식 로컬 회전 =
		// 자식 월드회전값 - 부모의 월드회전값
		mRelativeRotation = mWorldRotation - mParent->mWorldRotation;
	}
	// 부모가 없다면
	else
	{
		// 자기 자신이 부모회전값
		mRelativeRotation = mWorldRotation;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{

		mChildList[i]->SetWorldRotation(mChildList[i]->mRelativeRotation * mWorldRotation);
		
		mChildList[i]->SetWorldPosition(mChildList[i]->mRelativePosition.
			GetRotation(mWorldRotation)
			+ mWorldPosition);
	}
}

void CSceneComponent::SetWorldRotation(float x, float y, float z)
{
	SetRelativeRotation(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldRotation(const FVector2D& Rotation)
{
	SetRelativeRotation(FVector3D(Rotation.x, Rotation.y, mRelativeRotation.z));
}

void CSceneComponent::SetWorldRotation(float x, float y)
{
	SetRelativeRotation(FVector3D(x, y, mRelativeRotation.z));
}

void CSceneComponent::SetWorldRotationX(float x)
{
	SetRelativeRotation(FVector3D(x, mRelativeRotation.y, mRelativeRotation.z));
}

void CSceneComponent::SetWorldRotationY(float y)
{
	SetRelativeRotation(FVector3D(mRelativeRotation.x, y, mRelativeRotation.z));
}

void CSceneComponent::SetWorldRotationZ(float z)
{
	SetRelativeRotation(FVector3D(mRelativeRotation.x, mRelativeRotation.y, z));
}

void CSceneComponent::SetWorldRotationAxis(float Angle, const FVector3D& Axis)
{
}

void CSceneComponent::SetWorldPosition(const FVector3D& Position)
{
	mWorldPosition = Position;

	if (mParent)
	{
		FVector3D relativePosition = mWorldPosition - mParent->mWorldPosition;
		// 월드 로테이션만큼 회전 대 회전 횡렬로 위치를 구했으므로,
		// 그 값의 반대방향값으로 돌려준다.
		mRelativePosition = relativePosition.GetRotation(mParent->mWorldRotation * -1.f);
	}
	else
	{
		mRelativePosition = mWorldPosition;
	}


	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		mChildList[i]->SetWorldPosition(
			mChildList[i]->mRelativePosition +
			mWorldPosition);

	}
}

void CSceneComponent::SetWorldPosition(float x, float y, float z)
{
	SetWorldPosition(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldPosition(const FVector2D& Position)
{
	SetWorldPosition(FVector3D(Position.x, Position.y, mRelativePosition.z));
}

void CSceneComponent::SetWorldPosition(float x, float y)
{
	SetWorldPosition(FVector3D(x, y, mRelativePosition.z));
}
