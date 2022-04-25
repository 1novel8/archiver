#pragma once
#include<iostream>

using uchar = unsigned char;
using namespace std;

class Node {
public:
	using pointer = shared_ptr<Node>;
	pointer left{ nullptr };
	pointer right{ nullptr };
	pointer parent{ nullptr };
	Node() = default;
	Node(uchar uch, int w) : ch(uch), weight(w) {};
	//friend ostream& operator<<(ostream& os, const Node& node);
	bool operator<(const Node& oth) const {	return weight < oth.weight;}
	int getWeight() const { return weight; }
	string code() const {
		return code_string;
	}
	void code(const string& c) {
		code_string = c;
	}
	uchar getByte() const {
		return ch;
	}
	bool isLeaf() const {
		return (left == nullptr&&right==nullptr);
	}
private: 
	string code_string{""};
	uchar ch{ 0 };
	int weight{ 0 };

};
//ostream& operator<<(ostream& os, const Node& node) {
//	return os << "[" << (int)node.ch << "]=" << node.weight;
//}

class LowestPriority {
public:
	bool operator()(const Node::pointer& left, const Node::pointer& right) const { return left->getWeight() > right->getWeight(); }
};