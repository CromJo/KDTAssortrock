#pragma once

#include <iostream>

/// <summary>
/// ���� ���� ������
/// </summary>
enum class EClass : unsigned char
{
	None = 0,
	Knight,
	Archer,
	Magician,
	Thief,
	Back,
	MAX
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