#pragma once
#include<iostream>
#include<fstream>
#include<map>
#include<vector>

using namespace std;

void compress() {
	int weight[0x100];
	for (auto& i : weight)
		i = 0;
	{
		ifstream in("D:\\Study\\sem4\\archiver\\archiver\\infile.txt");
		if (in.is_open()) {
			while (!in.eof()) {
				unsigned char ch;
				in.read((char*)&ch, sizeof(ch));
				weight[ch]++;
			}
			in.close();
		}
	}

	multimap<int/*вес*/, int/*индекс в tree*/> sortedWeight;

	struct Node
	{
		char ch;
		int parent;
		int sero;
		int one;
		bool branch;
	};
	map<char, int> charMap;
	vector<Node> tree;


	for (size_t i = 0; i < 0x100; i++) {
		if (weight[i] > 0) {
			tree.push_back(Node{ (char)i, -1, -1, -1, false });
			charMap[i] = tree.size() - 1;
			sortedWeight.insert(make_pair(weight[i], tree.size() - 1));
		}
	}
	while (sortedWeight.size() > 1) {
		int w0 = begin(sortedWeight)->first;//достаем из sortedWeight 
		int n0 = begin(sortedWeight)->second;
		sortedWeight.erase(begin(sortedWeight));

		int w1 = begin(sortedWeight)->first;//достаем из sortedWeight 
		int n1 = begin(sortedWeight)->second;
		sortedWeight.erase(begin(sortedWeight));

		tree.push_back(Node{ '\0',-1, n0, n1, false });//добавляем нового родителя

		tree[n0].parent = tree.size() - 1;//присваиваем детям своего родителя
		tree[n0].branch = false;

		tree[n1].parent = tree.size() - 1;//присваиваем детям своего родителя
		tree[n1].branch = true;

		sortedWeight.insert(make_pair(w0 + w1, tree.size() - 1));//добавляем родителя в sortedWeight


	}
	vector<bool> data;
	ifstream in("D:\\Study\\sem4\\archiver\\archiver\\infile.txt");
	if (in.is_open()) {
		while (!in.eof()) {
			unsigned char ch;
			in.read((char*)&ch, sizeof(ch));
			auto n = tree[charMap[ch]];
			vector<bool>compressedChar;
			while (n.parent != -1) {
				compressedChar.push_back(n.branch);
				n = tree[n.parent];
			}
			data.insert(end(data), compressedChar.rbegin(), compressedChar.rend());
		}
		cout << data.size();
		in.close();
	}
	ofstream out("D:\\Study\\sem4\\archiver\\archiver\\outfile.txt");
	int treeSize = tree.size();
	out.write((char*)&treeSize, sizeof(treeSize));
	for (const auto &i : tree)
		out.write((char*)&i, sizeof(i));

	for (size_t i = 0; i <= data.size() / 8; i++) {
		unsigned char ch = 0;
		for (int j = 0; j < 8; j++) {
			if (data.size() >= (i * 8 + j))
				ch |= (1 << j);
			else
				break;
			cout << endl << i * 8 + j;
		}
		out.write((char*)&ch, sizeof(ch));
	}
	out.close();
	return;
}