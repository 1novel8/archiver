#pragma once

#include<fstream>
#include<map>
#include<vector>
#include<queue>
#include<memory>
#include<bitset>
#include"Node.h"
#include"Filesys.h"

using queue_t = priority_queue<Node::pointer, vector<Node::pointer>, LowestPriority>;
using namespace std;

class Entity {
protected:
	vector<string> listOfFiles;
	string pathIn = "";
	string pathOut = "";
	vector<int> weight;
	queue_t queue;
	string message="";
	Node::pointer root;
public:
	Entity(string pathIn) {
		this->pathIn = pathIn;
		this->weight = vector<int>(0x100, 0);
	};
	void setPathIn(string pathIn) { this->pathIn = pathIn; };
	void setPathOut(string pathOut) { this->pathOut = pathOut; };
};

