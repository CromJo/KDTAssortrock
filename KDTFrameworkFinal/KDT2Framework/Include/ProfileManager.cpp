#include "ProfileManager.h"

DEFINITION_SINGLE(CProfileManager)

CProfileManager::CProfileManager()
{
}

CProfileManager::~CProfileManager()
{
	auto	iter = mProfileMap.begin();
	auto	iterEnd = mProfileMap.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CProfileManager::Init()
{
	CreateProfile("Default", ECollisionChannel::Default, true,
		ECollisionInteraction::Collision);

	CreateProfile("Player", ECollisionChannel::Player, true,
		ECollisionInteraction::Collision);

	CreateProfile("Enemy", ECollisionChannel::Enemy, true,
		ECollisionInteraction::Collision);

	CreateProfile("PlayerAttack", ECollisionChannel::PlayerAttack, true,
		ECollisionInteraction::Ignore);

	CreateProfile("EnemyAttack", ECollisionChannel::EnemyAttack, true,
		ECollisionInteraction::Ignore);

	CreateProfile("EnemyDetect", ECollisionChannel::EnemyDetect, true,
		ECollisionInteraction::Ignore);

	SetInteraction("Player", ECollisionChannel::Player,
		ECollisionInteraction::Ignore);
	SetInteraction("Player", ECollisionChannel::PlayerAttack,
		ECollisionInteraction::Ignore);
	/*SetInteraction("Player", ECollisionChannel::Default,
		ECollisionInteraction::Ignore);*/

	SetInteraction("Enemy", ECollisionChannel::Enemy,
		ECollisionInteraction::Ignore);
	SetInteraction("Enemy", ECollisionChannel::EnemyAttack,
		ECollisionInteraction::Ignore);

	SetInteraction("PlayerAttack", ECollisionChannel::Default,
		ECollisionInteraction::Collision);
	SetInteraction("PlayerAttack", ECollisionChannel::Enemy,
		ECollisionInteraction::Collision);

	SetInteraction("EnemyAttack", ECollisionChannel::Default,
		ECollisionInteraction::Collision);
	SetInteraction("EnemyAttack", ECollisionChannel::Player,
		ECollisionInteraction::Collision);

	SetInteraction("EnemyDetect", ECollisionChannel::Player,
		ECollisionInteraction::Collision);

	return true;
}

bool CProfileManager::CreateProfile(const std::string& Name,
	ECollisionChannel::Type Channel,
	bool Enable, ECollisionInteraction::Type Interaction)
{
	FCollisionProfile* Profile = FindProfile(Name);

	if (Profile)
		return false;

	Profile = new FCollisionProfile;

	Profile->Name = Name;
	Profile->Channel = Channel;
	Profile->Enable = Enable;

	for (int i = 0; i < ECollisionChannel::End; ++i)
	{
		Profile->Interaction[i] = Interaction;
	}

	mProfileMap.insert(std::make_pair(Name, Profile));

	return true;
}

bool CProfileManager::SetInteraction(const std::string& Name,
	ECollisionChannel::Type Channel,
	ECollisionInteraction::Type Interaction)
{
	FCollisionProfile* Profile = FindProfile(Name);

	if (!Profile)
		return false;

	Profile->Interaction[Channel] = Interaction;

	return true;
}

bool CProfileManager::SetEnable(const std::string& Name,
	bool Enable)
{
	FCollisionProfile* Profile = FindProfile(Name);

	if (!Profile)
		return false;

	Profile->Enable = Enable;

	return true;
}

FCollisionProfile* CProfileManager::FindProfile(
	const std::string& Name)
{
	auto	iter = mProfileMap.find(Name);

	if (iter == mProfileMap.end())
		return nullptr;

	return iter->second;
}
