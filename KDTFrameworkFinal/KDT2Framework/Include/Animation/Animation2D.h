#pragma once

#include "../GameInfo.h"
#include "Animation2DSequence.h"
#include "../Shader/Animation2DCBuffer.h"

class CAnimation2D
{
	friend class CSpriteComponent;

private:
	static CAnimation2DCBuffer* mAnimCBuffer;
	CAnimation2DCBuffer* mAnimCBufferMember;

public:
	static void CreateCBuffer();
	static void DestroyCBuffer();
	static void DisableAnimation();

private:
	CAnimation2D();
	CAnimation2D(const CAnimation2D& Anim);
	virtual ~CAnimation2D();

private:
	class CScene* mScene = nullptr;
	class CSpriteComponent* mOwner = nullptr;
	std::unordered_map<std::string, CAnimation2DSequence*>	mSequenceMap;
	CAnimation2DSequence* mCurrentSequence = nullptr;

public:
	bool Init();
	void Update(float DeltaTime);
	bool AddSequence(const std::string& Name,
		float PlayTime = 1.f, float PlayRate = 1.f,
		bool Loop = false, bool Reverse = false);
	bool AddSequence(class CAnimation2DData* Asset,
		float PlayTime = 1.f, float PlayRate = 1.f,
		bool Loop = false, bool Reverse = false);
	void SetPlayTime(const std::string& Name,
		float PlayTime);
	void SetPlayRate(const std::string& Name,
		float PlayRate);
	void SetLoop(const std::string& Name,
		bool Loop);
	void SetReverse(const std::string& Name,
		bool Reverse);
	void ChangeAnimation(const std::string& Name);
	CAnimation2D* Clone();
	void SetShader();
	void SetAnimationReverseX(bool left);


private:
	CAnimation2DSequence* FindSequence(
		const std::string& Name);

public:
	/// <summary>
	/// 애니메이션 마지막 프레임의 추가 이벤트 추가.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="Name"></param>
	/// <param name="Obj"></param>
	/// <param name="Func"></param>
	template <typename T>
	void SetEndFunction(const std::string& Name, T* Obj, void(T::* Func)())
	{
		// 시퀀스 찾고
		CAnimation2DSequence* Sequence = FindSequence(Name);

		// 없으면 종료
		if (!Sequence)
			return;

		// 있으면 추가적인 이벤트를 추가.
		Sequence->SetEndFunction<T>(Obj, Func);
	}

	/// <summary>
	/// 애니메이션 추가 알림
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="Name"></param>
	/// <param name="Frame"></param>
	/// <param name="Obj"></param>
	/// <param name="Func"></param>
	template <typename T>
	void AddNotify(const std::string& Name,
		int Frame, T* Obj, void(T::* Func)())
	{
		// 시퀀스를 찾아서 대입
		CAnimation2DSequence* Sequence = FindSequence(Name);

		// 시퀀스 없으면 종료
		if (!Sequence)
			return;

		// 시퀀스의 추가 동작할 기능을 추가. 
		Sequence->AddNotify<T>(Name, Frame, Obj, Func);
	}

	template <typename T>
	void AddNotifyUpdate(const std::string& Name,
		int Frame, T* Obj, void(T::* Func)())
	{
		// 시퀀스를 찾아서 대입
		CAnimation2DSequence* Sequence = FindSequence(Name);

		// 시퀀스 없으면 종료
		if (!Sequence)
			return;

		// 시퀀스의 추가 동작할 기능을 추가. 
		Sequence->AddNotify<T>(Name, Frame, Obj, Func);
	}

	bool GetCurrentAnimation(const std::string& Name);
};

