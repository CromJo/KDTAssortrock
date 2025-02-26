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

	// Active False�� �����
	for (size_t i = 0; i < Size; ++i)
	{
		mChildList[i]->Destroy();
	}
}

void CSceneComponent::AddChild(CSceneComponent* Child)
{
	Child->mParent = this;

	// ��������Ʈ�� ���ο� ��ü(�ڽ�) �߰�
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
	// �θ��Լ� ��ȣ��
	CComponent::PreUpdate(DeltaTime);

	std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
	std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		// 
		if (!(*iter)->IsActive())
		{
			// ������ �� ���� ������ �� �ٲٱ�
			std::swap(*iter, mChildList.back());

			// SharedPointer �̹Ƿ� pop_back�ϸ� ���ŵ�.
			mChildList.pop_back();
			iterEnd = mChildList.end();

			continue;
		}
		// ��Ȱ��ȭ ���¸� ���� ������Ʈ �˻�
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
			// ������ �� ���� ������ �� �ٲٱ�
			std::swap(*iter, mChildList.back());

			// SharedPointer �̹Ƿ� pop_back�ϸ� ���ŵ�.
			mChildList.pop_back();
			iterEnd = mChildList.end();

			continue;
		}
		// ��Ȱ��ȭ ���¸� ���� ������Ʈ �˻�
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
			// ������ �� ���� ������ �� �ٲٱ�
			std::swap(*iter, mChildList.back());

			// SharedPointer �̹Ƿ� pop_back�ϸ� ���ŵ�.
			mChildList.pop_back();
			iterEnd = mChildList.end();

			continue;
		}
		// ��Ȱ��ȭ ���¸� ���� ������Ʈ �˻�
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
			// ������ �� ���� ������ �� �ٲٱ�
			std::swap(*iter, mChildList.back());

			// SharedPointer �̹Ƿ� pop_back�ϸ� ���ŵ�.
			mChildList.pop_back();
			iterEnd = mChildList.end();

			continue;
		}
		// ��Ȱ��ȭ ���¸� ���� ������Ʈ �˻�
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
			// ������ �� ���� ������ �� �ٲٱ�
			std::swap(*iter, mChildList.back());

			// SharedPointer �̹Ƿ� pop_back�ϸ� ���ŵ�.
			mChildList.pop_back();
			iterEnd = mChildList.end();

			continue;
		}
		// ��Ȱ��ȭ ���¸� ���� ������Ʈ �˻�
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
			// ������ �� ���� ������ �� �ٲٱ�
			std::swap(*iter, mChildList.back());

			// SharedPointer �̹Ƿ� pop_back�ϸ� ���ŵ�.
			mChildList.pop_back();
			iterEnd = mChildList.end();

			continue;
		}
		// ��Ȱ��ȭ ���¸� ���� ������Ʈ �˻�
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

	// �θ� ������ ���� ����ó���� �ٸ��� ó���Ǿ���Ѵ�.
	// �θ� ������ �θ��� ����
	if (mParent)
	{
		mWorldScale = mRelativeScale * mParent->mWorldScale;
	}
	// �θ� ������ �ڽ��� �θ�
	else
	{
		mWorldScale = mRelativeScale;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// �ڽ� ������ǥ = 
		// - �ڽ� ������ġ * �θ� ����ũ�� + �θ� ���� ��ġ
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
	// ��� ������ �ְ�
	mRelativeRotation = Rotation;

	// �θ��ΰ� �ƴѰ��� �Ǵ�
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
		// ȸ�� ���� ���� �ٴѴٸ�
		// �ڽ��� ������ġ �� =
		//	�ڽ��� ������ġ�� ȸ���� + �θ������ġ
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
	// ����ķ� ����ϱ⿣ �����ϴ�.
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
		// �ڽĻ��ũ�� :
		// - �ڽĿ���ũ�� / �θ����ũ��
		mRelativeScale = mWorldScale / mParent->mWorldScale;
	}
	else
	{
		mRelativeScale = mWorldScale;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// �ڽ� ������ǥ = 
		// - �ڽ� ������ġ * �θ� ����ũ�� + �θ� ���� ��ġ
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
		// �ڽ� ���� ȸ�� =
		// �ڽ� ����ȸ���� - �θ��� ����ȸ����
		mRelativeRotation = mWorldRotation - mParent->mWorldRotation;
	}
	// �θ� ���ٸ�
	else
	{
		// �ڱ� �ڽ��� �θ�ȸ����
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
		// ���� �����̼Ǹ�ŭ ȸ�� �� ȸ�� Ⱦ�ķ� ��ġ�� �������Ƿ�,
		// �� ���� �ݴ���Ⱚ���� �����ش�.
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
