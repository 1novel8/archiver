#pragma once

#include<iostream>
#include<fstream>
#include<map>
#include<vector>


void decompress() {
	struct Node
	{
		char ch;
		int parent;
		int sero;
		int one;
		bool branch;
	};
	vector<Node> tree;
	vector<bool> data;

	ifstream in("D:\\Study\\sem4\\archiver\\archiver\\infile.txt");
	int treeSize;
	in.read((char*)&treeSize, sizeof(treeSize));

	for (int i = 0; i < treeSize; i++) {
		Node n;
		in.read((char*)&n, sizeof(n));
		tree.push_back(n);
	}

	while (!in.eof()) {
		unsigned char ch;
		in.read((char*)&ch, sizeof(ch));
		for (int i = 0; i < 8; i++) {
			data.push_back((ch& (1 << i) )!= 0);
		}
	}
	auto n = tree.size() - 1;
	for (auto i : data) {
		if (i)
			n = tree[n].one;
		else
			n = tree[n].sero;
		if (tree[n].one == -1) {
			cout << tree[n].ch;
			n = tree.size() - 1;
		}

	}
	return;
}