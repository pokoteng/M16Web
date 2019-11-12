#pragma once
#include <iostream>
#include <vector>

using namespace std;

class DataPack
{
public:
	//30-31-32-40-41-42-43
	vector<int> uid;
	//[id][seq]
	vector< vector<int> > throwSeq;
	vector< vector< vector<int> > > door; //id吃了幾個, 每個分別為何
	vector< int > remain;
	void init()
	{
		uid.clear();
		throwSeq.clear();
		door.clear();
		remain.clear();

		for (int i = 0; i < 4; i = i + 1)
		{
			uid.push_back(-1);
			throwSeq.push_back(vector<int>());
			door.push_back(vector< vector<int> >());
		}

		for (int i = 0; i < 34; i = i + 1)
		{
			remain.push_back(4);
		}
	}
	void show()
	{
		for (int i = 0; i < 4; i = i + 1)
		{
			cout << uid[i] << endl;
			cout << "throwSeq: ";
			for (int j = 0; j < throwSeq[i].size(); j = j + 1)
			{
				cout << throwSeq[i][j] << ", ";
			}
			cout << endl;
			cout << "door: ";
			for (int j = 0; j < door[i].size(); j = j + 1)
			{
				for (int k = 0; k < door[i][j].size(); k = k + 1)
				{
					cout << door[i][j][k] << "-";
				}
				cout << ", ";
			}
			cout << endl;
		}
		for (int i = 0; i < 4; i = i + 1)
		{
			for (int j = 0; j < 9; j = j + 1) 
			{
				if (i == 3 && j >= 7) break;
				cout << remain[i * 9 + j] << " ";
			}
			cout << endl;
		}
	}
};