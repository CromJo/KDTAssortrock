#pragma once

#include <iostream>

/// <summary>
/// ���� ���� ������
/// </summary>
enum class EClass : unsigned char
{
	None,
	Knight,
	Archer,
	Magician,
	Thief,
	Back,
	MAX
};


/// <summary>
/// ������ ���̵� State
/// </summary>
enum EMode
{
	None = 0,
	Easy,
	Normal,
	Hard,
	Back
};

struct FPlayer
{
	char Name[32];
	EClass Class;
	int Attack;
	int Defense;
	int HP;
	int HPMax;
	int MP;
	int MPMax;
	int Level;
	int Exp;
	int Gold;
};

struct FMonster
{
	char Name[32];
	int Attack;
	int Defense;
	int HP;
	int HPMax;
	int Gold;				// ������ �ִ� �ݾ�
};