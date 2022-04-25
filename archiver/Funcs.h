#pragma once
//#define _CRT_SECURE_NO_WARNINGS


#include<fstream>
#include<map>
#include<vector>
#include<queue>
#include<memory>
#include<bitset>
#include"Node.h"

using queue_t = priority_queue<Node::pointer, vector<Node::pointer>, LowestPriority>;

class Funcs {
public:
	ifstream::pos_type get_size(const string& fn);
	void make_code(Node::pointer& node, string str, vector<string>& codes);
	void fillQueue(vector<int>& weight, queue_t& queue);
	void buildTree(queue_t& queue);
	void readFile(const string& filename, vector<int>& weight);//for zipper
	string message2code(string& filename, const vector<string>& codes);
	void writeFile(const string& filename, vector<int>& weight, const queue_t queue, const string& message);
	ifstream::pos_type readFile(string& filename,ifstream::pos_type pos,  vector<int>& weight2, string& message2);// for unzipper
	void decode(const Node::pointer& root, const string& message, string& text);
};
