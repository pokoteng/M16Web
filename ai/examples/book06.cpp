#include"book06.h"

//-------------------------------------------------------------------------

MJCard book06::returnMJCard(int value)
{
	if (value < 30)
	{
		return MJCard(value / 9, value % 9);
	}
	else
	{
		return MJCard(4, (value % 9) - 3);
	}
}

bool book06::OnTing(const bool canMiji)
{
	return false;
}

bool book06::WannaHu(const MJCard& card)
{
	return true;
}

book06::book06() {
	srand(time(NULL));
}

book06::~book06() {

}

vector< vector<double> > book06::guessNotNeed(const DataPack & situation)
{
	int phase = checkPhase(situation);

	guess.clear();
	for (int i = 0; i < 4; i = i + 1)
	{
		guess.push_back(vector<double>());
		for (int j = 0; j < 34; j = j + 1)
		{
			guess[i].push_back(1);
		}
	}

	for (int i = 0; i < 4; i = i + 1)
	{
		int size = situation.throwSeq[i].size();
		for (int j = 0; j < size; j = j + 1)
		{
			int tile = situation.throwSeq[i][j];
			int before1 = (j - 1 < 0 ? -1 : situation.throwSeq[i][j-1]);
			int before2 = (j - 2 < 0 ? -1 : situation.throwSeq[i][j-2]);

			if (tile < 27 && tile % 9 == 1) //��2���n21
			{
				guess[i][tile] = guess[i][tile] * 0.25;
				guess[i][tile - 1] = guess[i][tile - 1] * 0.25;
			}
			else if (tile < 27 && tile % 9 == 2) //��3���n321
			{
				guess[i][tile] = guess[i][tile] * 0.25;
				guess[i][tile - 1] = guess[i][tile - 1] * 0.25;
				guess[i][tile - 2] = guess[i][tile - 2] * 0.25;
			}
			else if (tile < 27 && tile % 9 == 3) //��4���n432
			{
				guess[i][tile] = guess[i][tile] * 0.25;
				guess[i][tile - 1] = guess[i][tile - 1] * 0.25;
				guess[i][tile - 2] = guess[i][tile - 2] * 0.25;
			}
			else if (tile < 27 && tile % 9 == 5) //��6���n678
			{
				guess[i][tile] = guess[i][tile] * 0.25;
				guess[i][tile + 1] = guess[i][tile + 1] * 0.25;
				guess[i][tile + 2] = guess[i][tile + 2] * 0.25;
			}
			else if (tile < 27 && tile % 9 == 6) //��7���n789
			{
				guess[i][tile] = guess[i][tile] * 0.25;
				guess[i][tile + 1] = guess[i][tile + 1] * 0.25;
				guess[i][tile + 2] = guess[i][tile + 2] * 0.25;
			}
			else if (tile < 27 && tile % 9 == 7) //��8���n89
			{
				guess[i][tile] = guess[i][tile] * 0.25;
				guess[i][tile + 1] = guess[i][tile + 1] * 0.25;
			}
			//----------------------------------
			
			if (phase > 0) //���߲�
			{
				/*if (tile < 27 && tile % 9 == 4) //��35���n47
				{
					if (before1 != -1 && before2 != -1 && ((before1 < 27 && before1 / 9 == tile / 9 && before1 % 9 == 2) || (before2 < 27 && before2 / 9 == tile / 9 && before2 % 9 == 2)))
					{
						guess[i][tile - 1] = guess[i][tile - 1] * 0.4;
						guess[i][tile + 2] = guess[i][tile + 2] * 0.4;
					}
				}
				else if (tile < 27 && tile % 9 == 2) //��53���n41
				{
					if (before1 != -1 && before2 != -1 && ((before1 < 27 && before1 / 9 == tile / 9 && before1 % 9 == 4) || (before2 < 27 && before2 / 9 == tile / 9 && before2 % 9 == 4)))
					{
						guess[i][tile + 1] = guess[i][tile + 1] * 0.4;
						guess[i][tile - 2] = guess[i][tile - 2] * 0.4;
					}
				}
				else if (tile < 27 && tile % 9 == 6) //��57���n69
				{
					if (before1 != -1 && before2 != -1 && ((before1 < 27 && before1 / 9 == tile / 9 && before1 % 9 == 4) || (before2 < 27 && before2 / 9 == tile / 9 && before2 % 9 == 4)))
					{
						guess[i][tile - 1] = guess[i][tile - 1] * 0.4;
						guess[i][tile + 2] = guess[i][tile + 2] * 0.4;
					}
				}
				else if (tile < 27 && tile % 9 == 4) //��75���n63
				{
					if (before1 != -1 && before2 != -1 && ((before1 < 27 && before1 / 9 == tile / 9 && before1 % 9 == 6) || (before2 < 27 && before2 / 9 == tile / 9 && before2 % 9 == 6)))
					{
						guess[i][tile + 1] = guess[i][tile + 1] * 0.4;
						guess[i][tile - 2] = guess[i][tile - 2] * 0.4;
					}
				}*/
				//----------------------------------
				/*if (tile < 27 && tile % 9 == 8) //��69���n6789
				{
					if (before1 != -1 && before2 != -1 && ((before1 < 27 && before1 / 9 == tile / 9 && before1 % 9 == 5) || (before2 < 27 && before2 / 9 == tile / 9 && before2 % 9 == 5)))
					{
						guess[i][tile] = guess[i][tile] * 0.6;
						guess[i][tile - 1] = guess[i][tile - 1] * 0.6;
						guess[i][tile - 2] = guess[i][tile - 2] * 0.6;
						guess[i][tile - 3] = guess[i][tile - 3] * 0.6;
					}
				}
				else if (tile < 27 && tile % 9 == 0) //��41���n4321
				{
					if (before1 != -1 && before2 != -1 && ((before1 < 27 && before1 / 9 == tile / 9 && before1 % 9 == 3) || (before2 < 27 && before2 / 9 == tile / 9 && before2 % 9 == 3)))
					{
						guess[i][tile] = guess[i][tile] * 0.6;
						guess[i][tile + 1] = guess[i][tile + 1] * 0.6;
						guess[i][tile + 2] = guess[i][tile + 2] * 0.6;
						guess[i][tile + 3] = guess[i][tile + 3] * 0.6;
					}
				}*/
				//----------------------------------
				/*
				if (phase < 2) //����
				{
					if (tile < 27 && tile % 9 == 0) //��61�n25
					{
						if (before1 != -1 && before2 != -1 && ((before1 < 27 && before1 / 9 == tile / 9 && before1 % 9 == 5) || (before2 < 27 && before2 / 9 == tile / 9 && before2 % 9 == 5)))
						{
							guess[i][tile + 1] = guess[i][tile + 1] * 1.25;
							guess[i][tile + 4] = guess[i][tile + 4] * 1.25;
						}
					}
					else if (tile < 27 && tile % 9 == 1) //��72�n36
					{
						if (before1 != -1 && before2 != -1 && ((before1 < 27 && before1 / 9 == tile / 9 && before1 % 9 == 6) || (before2 < 27 && before2 / 9 == tile / 9 && before2 % 9 == 6)))
						{
							guess[i][tile + 1] = guess[i][tile + 1] * 1.25;
							guess[i][tile + 4] = guess[i][tile + 4] * 1.25;
						}
					}
					else if (tile < 27 && tile % 9 == 7) //��38�n47
					{
						if (before1 != -1 && before2 != -1 && ((before1 < 27 && before1 / 9 == tile / 9 && before1 % 9 == 2) || (before2 < 27 && before2 / 9 == tile / 9 && before2 % 9 == 2)))
						{
							guess[i][tile - 1] = guess[i][tile - 1] * 1.25;
							guess[i][tile - 4] = guess[i][tile - 4] * 1.25;
						}
					}
					else if (tile < 27 && tile % 9 == 8) //��49�n58
					{
						if (before1 != -1 && before2 != -1 && ((before1 < 27 && before1 / 9 == tile / 9 && before1 % 9 == 3) || (before2 < 27 && before2 / 9 == tile / 9 && before2 % 9 == 3)))
						{
							guess[i][tile - 1] = guess[i][tile - 1] * 1.25;
							guess[i][tile - 4] = guess[i][tile - 4] * 1.25;
						}
					}
				}
				*/
			}
			
		}
	}

	for (int i = 0; i < 4; i = i + 1)
	{
		for (int j = 0; j < 34; j = j + 1)
		{
			if (guess[i][j] > 1) guess[i][j] = 1;

			guess[i][j] = 1 - guess[i][j];
		}
	}

	return guess;
}

void book06::combine(vector<int> & group, vector<long long> & handBit, int start, vector<long long> bitTemp, vector<int> selectGroup, vector< vector<int> > & resultGroup, int & handTotal, int & minTing)
{
	for (int i = start; i < group.size(); i = i + 1)
	{
		for (int j = 0; j < 4; j = j + 1)
		{
			if (j == 3 && !((group[i] >= 16 && group[i] < 25) || group[i] < 9))
			{
				break;
			}

			bitTemp[j] = bitTemp[j] + mask[group[i]];

			//if (selectGroup.size() > 17)
			//{
			//	cout << selectGroup.size() << endl;
			//	cout << "handBit: ";
			//	for (int m = 0; m < 4; m = m + 1)
			//	{
			//		for (int n = 0; n < 9; n = n + 1)
			//		{
			//			cout << ((handBit[j] >> (n * 3)) & 7) << " ";
			//		}
			//		cout << endl;
			//	}
			//	cout << "bitTemp: ";
			//	for (int m = 0; m < 4; m = m + 1)
			//	{
			//		for (int n = 0; n < 9; n = n + 1)
			//		{
			//			cout << ((bitTemp[j] >> (n * 3)) & 7) << " ";
			//		}
			//		cout << endl;
			//	}
			//}

			int flag = 0;
			for (int k = 0; k < 9; k = k + 1)
			{
				if (j == 3 && (bitTemp[j] >> 21) > 0)
				{
					flag = 1;
					break;
				}
				if (((handBit[j] >> (k * 3)) & 7) < ((bitTemp[j] >> (k * 3)) & 7)) //����
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				selectGroup.push_back(j * 40 + group[i]);

				combine(group, handBit, i, bitTemp, selectGroup, resultGroup, handTotal, minTing);

				selectGroup.pop_back();

			}

			bitTemp[j] = bitTemp[j] - mask[group[i]];
		}
	}

	//cout << bitTemp[0] << "  " << bitTemp[1] << "  " << bitTemp[2] << "  " << bitTemp[3] << endl;
	//for (int i = 0; i < selectGroup.size(); i = i + 1)
	//{
	//
	//	cout << selectGroup[i] << "  ";
	//}
	//cout << endl;

	int temp = handTotal / 3 * 2 + 1;

	int pair = 0;
	int preGroup = 0;
	int completeGroup = 0;

	//�D��i��
	for (int i = 0; i < selectGroup.size(); i = i + 1)
	{
		if (selectGroup[i] % 40 < 9)
		{
			temp = temp - 2;
			completeGroup = completeGroup + 1;
		}
		else if (selectGroup[i] % 40 < 16)
		{
			temp = temp - 2;
			completeGroup = completeGroup + 1;
		}
		else if (selectGroup[i] % 40 < 25)
		{
			temp = temp - 1;
			pair = 1;
			preGroup = preGroup + 1;
		}
		else if (selectGroup[i] % 40 < 32)
		{
			temp = temp - 1;
			preGroup = preGroup + 1;
		}
		else
		{
			temp = temp - 1;
			preGroup = preGroup + 1;
		}
	}

	//�f�L�h
	if (selectGroup.size() > handTotal / 3 + 1) temp = temp + selectGroup.size() - (handTotal / 3 + 1);

	//�ʲ�
	if (pair == 0 && preGroup >= ((handTotal / 3 + 1) - completeGroup))
	{
		temp = temp + 1;
	}

	if (temp <= minTing)
	{
		minTing = temp;
		selectGroup.push_back(temp);
		resultGroup.push_back(selectGroup);
	}

}

vector<double> book06::countTing(const DataPack & situation, vector<int> & hand, const int & phase)
{
	int handTotal = 0;
	//987654321
	vector<long long> handBit;
	for (int i = 0; i < 3; i = i + 1)
	{
		long long temp = 0;
		for (int j = 0; j < 9; j = j + 1)
		{
			//if (hand[i * 9 + j] != 0) cout << i * 9 + j << ", ";
			temp = temp + (hand[i * 9 + j] << (j * 3));
			handTotal = handTotal + hand[i * 9 + j];
		}
		handBit.push_back(temp);
	}
	long long temp = 0;
	for (int j = 0; j < 7; j = j + 1)
	{
		//if (hand[27 + j] != 0) cout << 27 + j << ", ";
		temp = temp + (hand[27 + j] << (j * 3));
		handTotal = handTotal + hand[27 + j];
	}
	handBit.push_back(temp);
	//cout << " -- " << handTotal << endl;
	//--------------------------

	vector<int> group;
	for (int j = 0; j < 40; j = j + 1)
	{
		for (int i = 0; i < 4; i = i + 1)
		{
			if (i == 3 && !((j >= 16 && j < 25) || j < 9)) break;

			int flag = 0;
			for (int k = 0; k < 9; k = k + 1)
			{
				if (((handBit[i] >> (k * 3)) & 7) < ((mask[j] >> (k * 3)) & 7)) //����
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0)
			{
				group.push_back(j);
				break;
			}
		}
	}

	//--------------------------

	vector<long long> bitTemp;
	vector<int> selectGroup;
	vector< vector<int> > resultGroup;

	resultGroup.clear();

	bitTemp.push_back(0);
	bitTemp.push_back(0);
	bitTemp.push_back(0);
	bitTemp.push_back(0);

	//cout << handBit[0] << "  " << handBit[1] << "  " << handBit[2] << "  " << handBit[3] << endl;

	int minTing = handTotal / 3 * 2 + 1;
	combine(group, handBit, 0, bitTemp, selectGroup, resultGroup, handTotal, minTing);

	//0 -> ���n, 1 -> �n�ۤv�N�~����, 2 -> �i�H�Y, 3 -> �i�H�I
	vector<int> T1;
	vector<int> unionT1;
	vector<double> bigT1; //���i�P�i�੹�j�P�e�i�����v�`��
	for (int i = 0; i < 34; i = i + 1)
	{
		T1.push_back(0);
		unionT1.push_back(0);
		bigT1.push_back(0);
	}

	int selfpos = -1;
	for (int i = 0; i < 4; i = i + 1)
	{
		if (situation.uid[i] == uid)
		{
			selfpos = i;
			break;
		}
	}

	for (int i = 0; i < resultGroup.size(); i = i + 1)
	{
		if (resultGroup[i][resultGroup[i].size() - 1] <= minTing)
		{
			int hasPair = 0;

			vector<long long> useTemp;
			useTemp.clear();
			useTemp.push_back(0);
			useTemp.push_back(0);
			useTemp.push_back(0);
			useTemp.push_back(0);

			for (int j = 0; j < 34; j = j + 1)
			{
				T1[j] = 0;
			}

			//--�j�P�[�J--
			//�I�I�J4, ��@��4, �j�T��8, �M�@��8, �j�|��16
			int bigCount[5] = { 0, 0, 0, 0, 0 };
			int threeColor[3] = {0, 0, 0};

			for (int j = 0; j < situation.door[selfpos].size(); j = j + 1)
			{
				if (situation.door[selfpos][j][0] == situation.door[selfpos][j][1] && situation.door[selfpos][j][1] == situation.door[selfpos][j][2]) //�I�I�J
				{
					bigCount[0] = bigCount[0] + 1;
				}
				
				if (situation.door[selfpos][j][0] >= 27 && situation.door[selfpos][j][0] <= 29) //�j�T��
				{
					bigCount[1] = bigCount[1] + 1;
					bigCount[2] = bigCount[2] + 3;
				}

				if (situation.door[selfpos][j][0] > 29) //�j�|��
				{
					bigCount[1] = bigCount[1] + 1;
					bigCount[4] = bigCount[4] + 3;
				}

				if (situation.door[selfpos][j][0] < 27) //��@��+�M�@��
				{
					threeColor[situation.door[selfpos][j][0] / 9] = threeColor[situation.door[selfpos][j][0] / 9] + 1;
				}
			}

			//------------

			for (int j = 0; j < resultGroup[i].size() - 1; j = j + 1)
			{
				int tag = resultGroup[i][j] % 40;

				//--�j�P--

				if (resultGroup[i][j] / 40 == 3) //�j�r
				{
					if (tag >= 16 && tag < 25) //��l
					{
						bigCount[0] = bigCount[0] + 1;
						bigCount[1] = bigCount[1] + 1;
						if (tag <= 19) //���o��
						{
							bigCount[2] = bigCount[2] + 2;
						}
						else
						{
							bigCount[4] = bigCount[4] + 2;
						}
					}
					if (tag < 9) //��l
					{
						bigCount[0] = bigCount[0] + 1;
						bigCount[1] = bigCount[1] + 1;
						if (tag <= 19) //���o��
						{
							bigCount[2] = bigCount[2] + 3;
						}
						else
						{
							bigCount[4] = bigCount[4] + 3;
						}
					}
				}
				else
				{
					if ((tag >= 16 && tag < 25) || tag < 9) //��l�Ψ�l
					{
						bigCount[0] = bigCount[0] + 1;
					}

					threeColor[resultGroup[i][j] / 40] = threeColor[resultGroup[i][j] / 40] + 1;
				}

				//--------

				useTemp[resultGroup[i][j] / 40] = useTemp[resultGroup[i][j] / 40] + mask[tag];

				if (need[tag] == -1) continue; //��l�M���l���ݭn����P

				int pos = (resultGroup[i][j] / 40) * 9 + need[tag];
				if (tag < 25)
				{
					T1[pos] = 3;
					hasPair = 1;
				}
				else if (T1[pos] < 2) T1[pos] = 2;

				if (tag >= 33 && tag <= 38)//�������q�٦��p������
				{
					if (T1[pos - 3] < 2) T1[pos - 3] = 2;
				}

			}

			//------------------

			if (resultGroup[i].size() - 1 < handTotal / 3 + 1)
			{
				bigCount[0] = bigCount[0] + 1; //�I�I�J��Q

				for (int j = 0; j < 4; j = j + 1)
				{
					for (int k = 0; k < 9; k = k + 1)
					{
						if (j == 3 && k >= 7) break;

						if (((handBit[j] & (7 << (k * 3)))) > (useTemp[j] & (7 << (k * 3))))
						{
							if (j == 3)
							{
								if (T1[j * 9 + k] == 0) T1[j * 9 + k] = 1;

								if (k < 3) bigCount[2] = bigCount[2] + ((handBit[j] & (7 << (k * 3)))) - (useTemp[j] & (7 << (k * 3))); //�j�T��
								else bigCount[4] = bigCount[4] + ((handBit[j] & (7 << (k * 3)))) - (useTemp[j] & (7 << (k * 3))); //�j�|��
							}
							else
							{
								if ((resultGroup[i].size() - 1) < (handTotal / 3) || hasPair == 1) //�p��handTotal / 3 || �����~������񪺴�f
								{
									if (k >= 2 && T1[j * 9 + k - 2] == 0) T1[j * 9 + k - 2] = 1;
									if (k >= 1 && T1[j * 9 + k - 1] == 0) T1[j * 9 + k - 1] = 1;
									
									if (k <= 7 && T1[j * 9 + k + 1] == 0) T1[j * 9 + k + 1] = 1;
									if (k <= 6 && T1[j * 9 + k + 2] == 0) T1[j * 9 + k + 2] = 1;
								}
								
								if (T1[j * 9 + k] == 0)				  T1[j * 9 + k] = 1;
							}
						}
					}
				}
			}

			//------------------
			//�j�P����

			// 4�f=5�f=6�f, 4�f=5�f=6�f, 5�i=6�i, 4�f=5�f=6�f, 8�i=9�i
			// 0.125=0.25=0.5, 0.125=0.25=0.5, 0.5=1, 0.25=0.5=1, 1=2
			int colorMax = threeColor[0];
			if (colorMax < threeColor[1]) colorMax = threeColor[1];
			if (colorMax < threeColor[2]) colorMax = threeColor[2];

			double bigMuti = 0;

			if (bigCount[0] == 4) bigMuti = bigMuti + 0.125;
			else if (bigCount[0] == 5) bigMuti = bigMuti + 0.25;
			else if (bigCount[0] >= 6) bigMuti = bigMuti + 0.5;

			if (bigCount[1] + colorMax == 4) bigMuti = bigMuti + 0.125;
			else if (bigCount[1] + colorMax == 5) bigMuti = bigMuti + 0.25;
			else if (bigCount[1] + colorMax >= 6) bigMuti = bigMuti + 0.5;

			if (bigCount[2] == 5) bigMuti = bigMuti + 0.5;
			else if (bigCount[2] >= 6) bigMuti = bigMuti + 1;

			if (colorMax == 4) bigMuti = bigMuti + 0.25;
			else if (colorMax == 5) bigMuti = bigMuti + 0.5;
			else if (colorMax >= 6) bigMuti = bigMuti + 1;

			if (bigCount[4] == 8) bigMuti = bigMuti + 1;
			else if (bigCount[4] >= 9) bigMuti = bigMuti + 2;

			//------------------

			for (int i = 0; i < 34; i = i + 1)
			{
				if (T1[i] > unionT1[i])
				{
					unionT1[i] = T1[i];
					if (bigMuti > bigT1[i]) bigT1[i] = bigMuti;
				}
			}

		}
	}

	double totalT1 = 0;
	if (minTing == 1)
	{
		for (int i = 0; i < 34; i = i + 1)
		{
			if (unionT1[i] != 0)
			{
				totalT1 = totalT1 + (T1Weight[phase] + bigT1[i] * bigWeight[phase]) * (situation.remain[i] - hand[i]);
				totalT1 = totalT1 + (T1Weight[phase] + bigT1[i] * bigWeight[phase]) * (situation.remain[i] - hand[i]) * guess[(selfpos - 1 + 4) % 4][i];
				totalT1 = totalT1 + (T1Weight[phase] + bigT1[i] * bigWeight[phase]) * (situation.remain[i] - hand[i]) * guess[(selfpos - 2 + 4) % 4][i];
				totalT1 = totalT1 + (T1Weight[phase] + bigT1[i] * bigWeight[phase]) * (situation.remain[i] - hand[i]) * guess[(selfpos - 3 + 4) % 4][i];
			}
		}
	}
	else
	{
		for (int i = 0; i < 34; i = i + 1)
		{
			if (unionT1[i] >= 1) totalT1 = totalT1 + (T1Weight[phase] + bigT1[i] * bigWeight[phase]) * (situation.remain[i] - hand[i]);

			if (unionT1[i] >= 2) totalT1 = totalT1 + (T1Weight[phase] + bigT1[i] * bigWeight[phase]) * (situation.remain[i] - hand[i]) * guess[(selfpos - 1 + 4) % 4][i];

			if (unionT1[i] >= 3)
			{
				//�[�W�t�~��a
				totalT1 = totalT1 + (T1Weight[phase] + bigT1[i] * bigWeight[phase]) * (situation.remain[i] - hand[i]) * guess[(selfpos - 2 + 4) % 4][i];
				totalT1 = totalT1 + (T1Weight[phase] + bigT1[i] * bigWeight[phase]) * (situation.remain[i] - hand[i]) * guess[(selfpos - 3 + 4) % 4][i];
			}
		}
	}

	if (defence[phase] == 1 && minTing > 1)
	{
		totalT1 = -1;
	}

	//cout << minTing << ", " << phase << ", " << totalT1 << endl;

	vector<double> returnValue;
	returnValue.push_back(minTing);
	returnValue.push_back(totalT1);

	return returnValue;
}

vector<int> book06::changeTo4int(const MJCard & card)
{
	vector<int> hand_;
	hand_.clear();

	for (int i = 0; i < 3; i = i + 1)
	{
		for (int j = 0; j < 9; j = j + 1)
		{
			hand_.push_back((Hand.mjcolor[i].value >> (j * 3)) & 7);
		}
	}

	for (int i = 0; i < 3; i = i + 1)
	{
		hand_.push_back((Hand.cfbCards >> (i * 3)) & 7);
	}

	for (int i = 0; i < 4; i = i + 1)
	{
		hand_.push_back((Hand.windsCards >> (i * 3)) & 7);
	}

	if (card.color != -100)
	{
		int cardValue = card.color * 9 + card.value - (card.color == 4 ? 6 : 0);
		hand_[cardValue] = hand_[cardValue] + 1;
	}

	return hand_;
}

int book06::checkPhase(const DataPack & situation)
{
	int phase = 0;
	int daCount = 0;
	for (int i = 0; i < 4; i = i + 1)
	{
		if (situation.uid[i] == uid) continue;

		if (situation.throwSeq[i].size() <= 4) phase = (phase < 0 ? 0 : phase);
		else if (situation.throwSeq.size() <= 8) phase = (phase < 1 ? 1 : phase);
		else if (situation.throwSeq.size() <= 12) phase = (phase < 2 ? 2 : phase);
		else phase = (phase < 3 ? 3 : phase);

		if (situation.door[i].size() >= 4) phase = (phase < 3 ? 3 : phase);
		else if (situation.door[i].size() >= 3) phase = (phase < 2 ? 2 : phase);
		else if (situation.door[i].size() >= 2)
		{
			phase = (phase < 1 ? 1 : phase);
			daCount = daCount + 1;
		}
	}

	if (daCount >= 2) phase = (phase < 2 ? 2 : phase);

	return phase;
}

MJCard book06::Throw(const DataPack & situation, const MJCard & card) {
	//cout << uid << " throw" << endl;
	guessNotNeed(situation);

	vector<int> hand_;

	hand_ = changeTo4int(card);

	for (int i = 0; i < 4; i = i + 1)
	{
		for (int j = 0; j < 9; j = j + 1)
		{
			if (i == 3 && j >= 7) break;
			for (int k = 0; k < hand_[i * 9 + j]; k = k + 1)
			{
				cout << i * 9 + j << ", ";
			}
		}
	}
	cout << endl;

	//-----------------------------------------------------------------------------

	int phase = checkPhase(situation);

	//-----------------------------------------------------------------------------

	int best = -1;
	int bestTing = 99;
	double bestT1 = 0;
	//vector<double> bestTing = countTing(situation, hand_, phase);

	for (int i = 0; i < 34; i = i + 1)
	{
		if (hand_[i] != 0)
		{
			hand_[i] = hand_[i] - 1;

			//cout << i << ", ";

			vector<double> after = countTing(situation, hand_, phase);

			if (best == -1)
			{
				best = i;
				bestTing = (int)after[0];
				bestT1 = after[1];
			}
			else
			{
				if (tingFirst[phase] == 1)
				{
					if (after[0] < bestTing)
					{
						best = i;
						bestTing = (int)after[0];
						bestT1 = after[1];
					}
					else if (((int)after[0]) == bestTing && after[1] > bestT1)
					{
						best = i;
						bestTing = (int)after[0];
						bestT1 = after[1];
					}
					else if (((int)after[0]) == bestTing && after[1] == bestT1) //����
					{
						if (style == 0)
						{
							//do nothing
						}
						else if (style == 1)
						{
							if (rand() % 2 == 1) //�@�b�����|���N
							{
								best = i;
								bestTing = ((int)after[0]);
								bestT1 = after[1];
							}
						}
						else if (style == 2)
						{
							double guessMin1 = 1;
							double guessMin2 = 1;
							for (int j = 0; j < 4; j = j + 1)
							{
								if (situation.uid[j] == uid) continue;
								guessMin1 = (guessMin1 < guess[j][best] ? guessMin1 : guess[j][best]);
								guessMin2 = (guessMin2 < guess[j][i] ? guessMin2 : guess[j][i]);
							}
							if (guessMin2 > guessMin1)
							{
								best = i;
								bestTing = ((int)after[0]);
								bestT1 = after[1];
							}
						}
					}
				}
				else
				{
					if (after[1] > bestT1)
					{
						best = i;
						bestTing = ((int)after[0]);
						bestT1 = after[1];
					}
					else if (after[1] == bestT1) //����
					{
						if (style == 0)
						{
							//do nothing
						}
						else if (style == 1)
						{
							if (rand() % 2 == 1) //�@�b�����|���N
							{
								best = i;
								bestTing = ((int)after[0]);
								bestT1 = after[1];
							}
						}
						else if (style == 2)
						{
							double guessMin1 = 1;
							double guessMin2 = 1;
							for (int j = 0; j < 4; j = j + 1)
							{
								if (situation.uid[j] == uid) continue;
								guessMin1 = (guessMin1 < guess[j][best] ? guessMin1 : guess[j][best]);
								guessMin2 = (guessMin2 < guess[j][i] ? guessMin2 : guess[j][i]);
							}
							if (guessMin2 > guessMin1)
							{
								best = i;
								bestTing = ((int)after[0]);
								bestT1 = after[1];
							}
						}
					}
				}
			}

			hand_[i] = hand_[i] + 1;
		}
	}
	//cout << endl;
	////���u�Ҧ�: ���X�O�H�襴�L���P
	//if (phase == 3 && bestTing > 1)
	//{
	//	for (int i = 3; i > 0; i = i - 1)
	//	{
	//		int tile = situation.throwSeq[((id + i) % 4)][situation.throwSeq[((id + i) % 4)].size() - 1];
	//		if (hand_[tile] != 0) return returnMJCard(tile);
	//	}
	//}

	if (best != -1)
	{
		if (bestT1 == -1)
		{
			int tile = -1;
			double maxSafe = 0;
			//�iť�Ƥ��ŦX�n�D(phase23 ť==1) -> ���u
			for (int i = 0; i < 34; i = i + 1)
			{
				if (hand_[i] != 0)
				{
					double guessMin = 1;
					for (int j = 0; j < 4; j = j + 1)
					{
						if (situation.uid[j] == uid) continue;
						guessMin = (guessMin < guess[j][i] ? guessMin : guess[j][i]);
					}
					if (guessMin > maxSafe)
					{
						tile = i;
						maxSafe = guessMin;
					}

				}
			}
			if (tile != -1) return returnMJCard(tile);
			else return returnMJCard(best);
		}
		else
		{
			if (phase == 3)
			{
				double guessMin = 1;
				for (int j = 0; j < 4; j = j + 1)
				{
					if (situation.uid[j] == uid) continue;
					guessMin = (guessMin < guess[j][best] ? guessMin : guess[j][best]);
				}

				if (guessMin > 0.5)
				{
					return returnMJCard(best);
				}
				else
				{
					//�����|��j
					int tile = -1;
					double maxSafe = 0;
					for (int i = 0; i < 34; i = i + 1)
					{
						if (hand_[i] != 0)
						{
							double guessMin = 1;
							for (int j = 0; j < 4; j = j + 1)
							{
								if (situation.uid[j] == uid) continue;
								guessMin = (guessMin < guess[j][i] ? guessMin : guess[j][i]);
							}
							if (guessMin > maxSafe)
							{
								tile = i;
								maxSafe = guessMin;
							}

						}
					}

					if (tile != -1) return returnMJCard(tile);
					else return returnMJCard(best);
				}
			}
			else
			{
				return returnMJCard(best);
			}
		}
	}

	//���OT1
	for (int i = 33; i >= 0; i = i - 1)
	{
		if (hand_[i] != 0)
		{
			cout << "Not Good ... " << endl;
			return returnMJCard(i);
		}
	}

	cout << "book06::throw error!!!" << endl;
	return returnMJCard(0);
}

std::pair<CommandType, MJCard> book06::WannaHuGon(DataPack & situation, bool canHu, bool canGon, const MJCard & card, const MJCard & gonCard) {
	//cout << uid << " HuGon" << endl;
	if (canHu)
		return std::make_pair(COMMAND_ZIMO, card);
	//else if (canGon) {
	//	//
	//	//std::pair<bool, MJCard> temp = GonOrNot(card, true);
	//	//
	//	////�b�|���i�U�ƼW�[
	//	//if (!temp.first) {
	//	//	return std::make_pair(NONE, Throw(situation, card));
	//	//}
	//	//else {
	//	//	return std::make_pair(COMMAND_GON, temp.second);
	//	//}
	//	return std::make_pair(NONE, Throw(situation, card));
	//}
	else
		return std::make_pair(NONE, Throw(situation, card));
}
CommandType book06::WannaHGPE(DataPack & situation, bool canHu, bool canGon, bool canPon, bool canEat, const MJCard & card, int idx) {
	//cout << uid << " HGPE" << endl;
	if (canHu) {
		return COMMAND_HU;
	}

	guessNotNeed(situation);

	vector<int> hand_;
	hand_ = changeTo4int(MJCard(-100, -100));
	int phase = checkPhase(situation);

	vector<double> before = countTing(situation, hand_, phase);

	//for (int k = 0; k < 4; k = k + 1)
	//{
	//	for (int j = 0; j < 9; j = j + 1)
	//	{
	//		if (k == 3 && j >= 7) continue;
	//		if (hand_[k * 9 + j] > 4 || hand_[k * 9 + j] < 0)
	//		{
	//			cout << k << "  -  " << j << endl;
	//			cout << "value: " << hand_[k * 9 + j] << endl;
	//		}
	//	}
	//}

	int totalHand = 0;
	for (int i = 0; i < 34; i = i + 1)
	{
		totalHand = totalHand + hand_[i];
	}

	int cardValue = card.color * 9 + card.value - (card.color == 4 ? 6 : 0);

	if (canEat) {
		if (totalHand <= 5) //��P����
		{
			return NONE;
		}

		pickToEat = -1;

		int ting = 10;
		double maxT1 = 0;

		if (card.value >= 2)
		{
			int flag = 0;
			if (hand_[cardValue - 1] <= 0) flag = 1;
			if (hand_[cardValue - 2] <= 0) flag = 1;

			if (flag == 0)
			{
				hand_[cardValue - 1] = hand_[cardValue - 1] - 1;
				hand_[cardValue - 2] = hand_[cardValue - 2] - 1;

				vector<double> temp = countTing(situation, hand_, phase);
				if (pickToEat == -1 || ting > (int)temp[0] || (ting == (int)temp[0]) && maxT1 < temp[1])
				{
					ting = (int)temp[0];
					maxT1 = temp[1];
					pickToEat = 0;
				}

				hand_[cardValue - 1] = hand_[cardValue - 1] + 1;
				hand_[cardValue - 2] = hand_[cardValue - 2] + 1;
			}
		}

		if (card.value >= 1 && card.value <= 7)
		{
			int flag = 0;
			if (hand_[cardValue - 1] <= 0) flag = 1;
			if (hand_[cardValue + 1] <= 0) flag = 1;

			if (flag == 0)
			{
				hand_[cardValue - 1] = hand_[cardValue - 1] - 1;
				hand_[cardValue + 1] = hand_[cardValue + 1] - 1;

				vector<double> temp = countTing(situation, hand_, phase);
				if (pickToEat == -1 || ting > (int)temp[0] || (ting == (int)temp[0]) && maxT1 < temp[1])
				{
					ting = (int)temp[0];
					maxT1 = temp[1];
					pickToEat = 1;
				}

				hand_[cardValue - 1] = hand_[cardValue - 1] + 1;
				hand_[cardValue + 1] = hand_[cardValue + 1] + 1;
			}

		}

		if (card.value <= 6)
		{
			int flag = 0;
			if (hand_[cardValue + 1] <= 0) flag = 1;
			if (hand_[cardValue + 2] <= 0) flag = 1;

			if (flag == 0)
			{
				hand_[cardValue + 1] = hand_[cardValue + 1] - 1;
				hand_[cardValue + 2] = hand_[cardValue + 2] - 1;

				vector<double> temp = countTing(situation, hand_, phase);
				if (pickToEat == -1 || ting > (int)temp[0] || (ting == (int)temp[0]) && maxT1 < temp[1])
				{
					ting = (int)temp[0];
					maxT1 = temp[1];
					pickToEat = 2;
				}

				hand_[cardValue + 1] = hand_[cardValue + 1] + 1;
				hand_[cardValue + 2] = hand_[cardValue + 2] + 1;
			}
		}

		if (pickToEat == 0)
		{
			hand_[cardValue - 1] = hand_[cardValue - 1] - 1;
			hand_[cardValue - 2] = hand_[cardValue - 2] - 1;
		}
		else if (pickToEat == 1)
		{
			hand_[cardValue - 1] = hand_[cardValue - 1] - 1;
			hand_[cardValue + 1] = hand_[cardValue + 1] - 1;
		}
		else if (pickToEat == 2)
		{
			hand_[cardValue + 1] = hand_[cardValue + 1] - 1;
			hand_[cardValue + 2] = hand_[cardValue + 2] - 1;
		}

		if (before[0] < ting)
		{
			return NONE;
		}
		else if ((int)before[0] == ting && before[1] >= maxT1)
		{
			return NONE;
		}
		else if (phase == 3 && ting > 1)
		{
			return NONE;
		}
		else
		{
			for (int i = 0; i < 34; i = i + 1)
			{
				if (hand_[i] != 0)
				{
					if (i == card.color * 9 + card.value - (card.color == 4 ? 6 : 0)) continue;

					if (defence[phase] == 1) //phase23
					{
						int flag = 0;
						for (int j = 0; j < 4; j = j + 1)
						{
							if (situation.uid[j] == uid) continue;
							if (guess[j][i] > 0.5)
							{
								flag = flag + 1;
								break;
							}
						}
						if (flag != 3) continue;
					}

					hand_[i] = hand_[i] - 1;

					if (pickToEat == 0)
					{
						situation.remain[cardValue - 1] = situation.remain[cardValue - 1] - 1;
						situation.remain[cardValue - 2] = situation.remain[cardValue - 2] - 1;
					}
					else if (pickToEat == 1)
					{
						situation.remain[cardValue - 1] = situation.remain[cardValue - 1] - 1;
						situation.remain[cardValue + 1] = situation.remain[cardValue + 1] - 1;
					}
					else if (pickToEat == 2)
					{
						situation.remain[cardValue + 1] = situation.remain[cardValue + 1] - 1;
						situation.remain[cardValue + 2] = situation.remain[cardValue + 2] - 1;
					}

					vector<double> temp = countTing(situation, hand_, phase);

					if (pickToEat == 0)
					{
						situation.remain[cardValue - 1] = situation.remain[cardValue - 1] + 1;
						situation.remain[cardValue - 2] = situation.remain[cardValue - 2] + 1;
					}
					else if (pickToEat == 1)
					{
						situation.remain[cardValue - 1] = situation.remain[cardValue - 1] + 1;
						situation.remain[cardValue + 1] = situation.remain[cardValue + 1] + 1;
					}
					else if (pickToEat == 2)
					{
						situation.remain[cardValue + 1] = situation.remain[cardValue + 1] + 1;
						situation.remain[cardValue + 2] = situation.remain[cardValue + 2] + 1;
					}
					if ((int)temp[0] == ting) return COMMAND_EAT;

					hand_[i] = hand_[i] + 1;
				}
			}
		}
		return NONE;
	}

	if (canPon) {
		if (totalHand <= 5) //��P����
		{
			return NONE;
		}

		hand_[cardValue] = hand_[cardValue] - 2;
		vector<double> after = countTing(situation, hand_, phase);

		if (before[0] < after[0])
		{
			return NONE;
		}
		else if ((int)before[0] == (int)after[0] && before[1] >= after[1])
		{
			return NONE;
		}
		else if (phase == 3 && after[0] > 1)
		{
			return NONE;
		}
		else if (phase <= 1 && ((idx + 1) % 4) == id && (card.color == 3 || card.color == 4) && situation.remain[card.color * 9 + card.value - (card.color == 4 ? 6 : 0)] == 4)
		{
			return NONE;
		}
		else
		{
			for (int i = 0; i < 34; i = i + 1)
			{
				if (hand_[i] != 0)
				{
					if (defence[phase] == 1) //phase23
					{
						int flag = 0;
						for (int j = 0; j < 4; j = j + 1)
						{
							if (situation.uid[j] == uid) continue;
							if (guess[j][i] > 0.5)
							{
								flag = flag + 1;
								break;
							}
						}
						if (flag != 3) continue;
					}

					hand_[i] = hand_[i] - 1;

					situation.remain[cardValue] = situation.remain[cardValue] - 2;

					vector<double> temp = countTing(situation, hand_, phase);

					situation.remain[cardValue] = situation.remain[cardValue] + 2;

					if ((int)temp[0] == (int)after[0]) return COMMAND_PON;

					hand_[i] = hand_[i] + 1;
				}
			}
		}

		return NONE;
	}


	if (!canHu && !canEat && !canPon && !canGon) {
		cout << "WannaHGPE error" << endl;
		return NONE;
	}

	return NONE;
}

int book06::Pick2Eat(const MJCard & card) {
	return pickToEat;
}

MJCard book06::TileToCard(int color, int value) {
	int rColor, rValue;
	if (color == 3) {
		if (value <= 3) {
			rColor = 4;
			rValue = value;
		}
		else {
			rColor = 3;
			rValue = value - 4;
		}
	}
	else {
		rColor = color;
		rValue = value;
	}

	return MJCard(rColor, rValue);
}
