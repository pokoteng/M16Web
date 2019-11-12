


#pragma once

#include"MJCards.h"
#include<iostream>
#include<string>
#include<tuple>



using namespace std;


enum CommandType
{
	NONE = 0b0000000,			//�S��
	COMMAND_PON = 0b0000001, //�I
	COMMAND_GON = 0b0000010, //���b
	COMMAND_ANGON = 0b0000100, //�t�b
	COMMAND_PONGON = 0b0001000, //���U�b
	COMMAND_HU = 0b0010000, //�J
	COMMAND_ZIMO = 0b0100000, //�ۺN
	COMMAND_EAT = 0b1000000
};

enum Actions
{
	NOTREADY = 0,
	PASS,
	THROW,
	HU,
	ZIMO,
	GON,
	ONGON,
	PONGON,
	PON,
	EAT,
	BUHUA
};

class Player {
public:

	MJCards Hand;
	//MJCards Door;

	Player();
	
	bool isDron; //�O�_����
	long long eat; //�O���Y�A�C�ӦY��3bit�x�s(�i��Y�F�|��)�A�C�@�⦳�C�ئY�k�A�@63bit 0~20 �U 21~41 �� 42~62 �� 
	long long pon; //�O���I�A0~8 �U 9~17 �� 18~26 �� 27~29 �r 30~33��
	long long gon; //�O���b(�]�A��ة��b)�A0~8 �U 9~17 �� 18~26 �� 27~29 �r 30~33��
	long long anGon; //�O���t�b�A0~8 �U 9~17 �� 18~26 �� 27~29 �r 30~33��
	int flowers;
	int winds; //�P�ձ����榡�ۦP
	MJCards discards;

	
	int id, uid;
	std::string Print();
	int Count();
	virtual bool Ready();
	virtual bool IsHu();
	virtual bool WannaHu(const MJCard & card); //�n�m�b�J��?
	virtual std::pair<CommandType, MJCard> WannaHuGon(bool canHu, bool canGon, const MJCard & card, const MJCard & gonCard);
	virtual CommandType WannaHGPE(bool canHu, bool canGon, bool canPon, bool canEat, const MJCard & card, int idx); //idx����P�̪�ID
	virtual int Pick2Eat(const MJCard & card);

	Actions Action;
	virtual MJCard Throw(const MJCard & card = MJCard(-100, -100));


};