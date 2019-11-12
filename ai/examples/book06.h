#pragma once
#include "MJCards.h"
#include "Player.h"
#include "DataPack.h"
#include <utility>
#include <functional>
#include<vector>
#include <fstream>				
#include <ctime>

class book06 : public Player {
private:
	/*struct Tiles_
	{
		int tiles[4];
		Tiles_ operator-=(const Tiles_ & t);
		Tiles_ operator-=(const MJCard & t);
		Tiles_ operator+=(const MJCard & t);
	};*/

	typedef struct
	{
		vector<int> code;
		vector<int> Hu_Tiles;
		int steps;
	}Groups;

	int pickToEat; //存Pick2Eat的回傳值

	MJCard TileToCard(int color, int value);

	long long mask[40] = {
	3, 24, 192, 1536, 12288, 98304, 786432, 6291456, 50331648,  //刻子 <9
	73, 584, 4672, 37376, 299008, 2392064, 19136512, //順子 <16
	2, 16, 128, 1024, 8192, 65536, 524288, 4194304, 33554432, //對子 <25
	65, 520, 4160, 33280, 266240, 2129920, 17039360, //中洞 <32
	9, 72, 576, 4608, 36864, 294912, 2359296, 18874368//小順 
	};

	int need[40] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1,   //刻子 <9
	-1, -1, -1, -1, -1, -1, -1,  //順子 <16
	0, 1, 2, 3, 4, 5, 6, 7, 8,  //對子 <25
	1, 2, 3, 4, 5, 6, 7, //中洞 <32
	2, 3, 4, 5, 6, 7, 8, 7//小順  -- 中間的-3也是要的
	};

	//權重調整
	int tingFirst[4] = { 1, 1, 1, 1 };
	double T1Weight[4] = { 1, 1, 1, 1 };
	double bigWeight[4] = {0, 0, 0, 0};
	int defence[4] = { 0, 0, 0, 1 };
	int style = 2;
	//style0: 打最右邊的
	//style1: 遇到分數一樣的隨機選一個
	//style2: 打guess最高的

	//聽 -> [0] == 1
	vector<double> countTing(const DataPack & situation, vector<int> & hand, const int & phase);
	void combine(vector<int> & group, vector<long long> & handBit, int start, vector<long long> bitTemp, vector<int> selectGroup, vector< vector<int> > & resultGroup, int & handTotal, int & minTing);
	MJCard returnMJCard(int value);
	vector< vector<double> > guessNotNeed(const DataPack & situation);
	vector<int> changeTo4int(const MJCard & card);
	int checkPhase(const DataPack & situation);

	//被打出的機會
	vector< vector<double> > guess;

public:
	book06();
	~book06();
	MJCard Throw(const DataPack & situation, const MJCard & card = MJCard(-100, -100));
	std::pair<CommandType, MJCard> WannaHuGon(DataPack & situation, bool canHu, bool canGon, const MJCard & card, const MJCard & gonCard);
	CommandType WannaHGPE(DataPack & situation, bool canHu, bool canGon, bool canPon, bool canEat, const MJCard & card, int idx);
	int Pick2Eat(const MJCard & card);
	bool OnTing(const bool canMiji);
	bool WannaHu(const MJCard& card);


};