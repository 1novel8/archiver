#include"Funcs.h"

ifstream::pos_type Funcs::get_size(const string& fn) {
	ifstream f(fn, ifstream::ate);
	return f.tellg();
}

void Funcs::readFile(const string& filename, vector<int>& weight) {

	ifstream in(filename, ifstream::binary);
	int filesize = Funcs::get_size(filename);
	if (filesize < 0) {
		cerr << "Error in [" << __func__ << "]:" /*<< strerror_s(errno)*/;
		return;
	}

	if (!in) {
		cerr << "Error in [" << __func__ << "]:" /*<< strerror_s(errno)*/;
		return;
	}

	//cout << "Reading file " << filename << ": " << endl;
	int i = 0;
	while (true) {

		char ch;
		in.read(&ch, sizeof(char));
		if (in.eof())
			break;
		weight[static_cast<unsigned char>(ch)]++;

		i++;
		int value = i * 100.0 / filesize;
		//cout << "\r" << value << "%" << flush;
	}
	//cout << endl;
	//for (int i = 0; i < weight.size(); i++) {
	//	if (weight[i] != 0)
	//		//cout << "[" << i << "] = " << weight[i] << ", \t" << " \n"[i == weight.size() - 1];
	//}
	in.close();
}

void Funcs::make_code(Node::pointer& node, string str, vector<string>& codes) {
	if (node->left != nullptr) {
		Funcs::make_code(node->left, str + "0", codes);
	}
	if (node->right) {
		Funcs::make_code(node->right, str + "1", codes);
	}
	if (node->right == nullptr && node->right == nullptr) {
		node->code(str);
		codes[node->getByte()] = str;
		//cout << "leaf:" << *node << " code:" << codes[node->getByte()] << endl;
	}
}

void Funcs::fillQueue(vector<int>& weight, queue_t& queue) {
	uchar byte = 0;
	for_each(weight.begin(), weight.end(), [&queue, &byte](const auto& value) {
		if (value != 0) {
			Node::pointer node = make_shared<Node>(byte, value);
			queue.push(node);
		}
		byte++;
	});
}

void Funcs::buildTree(queue_t& queue) {
	while (queue.size() > 1) {
		Node::pointer x = queue.top();
		queue.pop();

		Node::pointer y = queue.top();
		queue.pop();

		Node::pointer z = make_shared<Node>(0, x->getWeight() + y->getWeight());

		z->left = x;
		z->right = y;

		x->parent = z;
		y->parent = z;
		queue.push(z);
	}
}

string Funcs::message2code(string& filename, const vector<string>& codes) {
	string msg{ "" };
	ifstream in(filename, ifstream::binary);

	if (!in) {
		cerr << "Error in [" << __func__ << "]:" /*<< strerror_s(errno)*/;
		return msg;
	}
	while (true) {
		char ch;
		in.read(&ch, 1);
		if (in.eof()) {
			break;
		}
		msg += codes[static_cast<uchar>(ch)];
	}
	return msg;
}

void Funcs::writeFile(const string& fileOut, vector<int>& weight, const queue_t queue, const string& message) {
	ofstream out(fileOut, /*ofstream::binary,*/ ios_base::app|ios_base::ate|ios_base::binary);
	if (!out) {
		cerr << "Error in [" << __func__ << "]:" /*<< strerror_s(errno)*/;
		return;
	}
	
	int count = count_if(weight.begin(), weight.end(), [](const int& value) {return value != 0; });
	out.write(reinterpret_cast<char*>(&count), sizeof(count));
	for_each(weight.begin(), weight.end(), [index = uchar(0), &out](int& value) mutable{
		if (value != 0) {
			out.write(reinterpret_cast<char*>(&index), sizeof(index));
			out.write(reinterpret_cast<char*>(&value), sizeof(value));
		}
		index++;
	});
	int byteCount = message.size() / CHAR_BIT;
	uchar modulo = message.size() % CHAR_BIT;

	out.write(reinterpret_cast<char*>(&byteCount), sizeof(byteCount));
	out.write(reinterpret_cast<char*>(&modulo), sizeof(modulo));

	int i = 0;
	for (; i < byteCount; ++i) {
		bitset<CHAR_BIT> b(message.substr(i * CHAR_BIT, CHAR_BIT));
		uchar value = static_cast<uchar>(b.to_ulong());
		out.write(reinterpret_cast<char*>(&value), sizeof(value));
	}
	if (modulo > 0) {
		bitset<CHAR_BIT> b(message.substr(i * CHAR_BIT, modulo));
		uchar value = static_cast<uchar>(b.to_ulong());
		out.write(reinterpret_cast<char*>(&value), sizeof(value));
	}
}

ifstream::pos_type Funcs::readFile(string& filename, ifstream::pos_type pos, vector<int>& weight2, string& message2) {
	ifstream in(filename, ofstream::binary);
	if (!in) {
		cerr << "Error in [" << __func__ << "]:" /*<< strerror_s(errno)*/;
		return 0;
	}
	in.seekg(pos);

	int count = 0;
	in.read(reinterpret_cast<char*>(&count), sizeof count);
	//cout << "New count:" << (int)count << endl;
	int i = 0;
	while (i < count) {
		uchar ch;
		in.read(reinterpret_cast<char*>(&ch), sizeof ch);

		int w = 0;
		in.read(reinterpret_cast<char*>(&w), sizeof w);
		weight2[ch] = w;
		i++;
	}
	//for_each(weight2.begin(), weight2.end(), [index = uchar(0)](const int& value) mutable{
	//	if (value != 0) {
	//		cout << "[" << static_cast<char>(index) << "]" << value << endl;
	//	}
	//	index++;s
	//});

	int byteCount = 0;
	uchar modulo = 0;

	in.read(reinterpret_cast<char*>(&byteCount), sizeof byteCount);
	in.read(reinterpret_cast<char*>(&modulo), sizeof modulo);

	i = 0;
	for (; i < byteCount; i++) {
		uchar byte;
		in.read(reinterpret_cast<char*>(&byte), sizeof byte);

		bitset<CHAR_BIT>b(byte);
		message2 += b.to_string();
	}
	if (modulo > 0) {
		uchar byte;

		in.read(reinterpret_cast<char*>(&byte), sizeof byte);

		bitset<CHAR_BIT>b(byte);
		message2 += b.to_string().substr(CHAR_BIT - modulo, CHAR_BIT);
	}
	return in.tellg();
}

void Funcs::decode(const Node::pointer& root, const string& message, string& text) {
	Node::pointer node = root;


	for (size_t i = 0; i < message.size(); i++) {
		char ch = message[i];
		if (ch == '0') {
			if (node->left != nullptr) {
				node = node->left;
				if (node->isLeaf()) {
					if (text.size() > 0 || (text.size() ==0 && (node->getByte() != 239 && node->getByte() != 187&&node->getByte() != 191)))
						text += node->getByte();
					node = root;
				}
			}
		}
		else if (ch == '1') {
			if (node->right != nullptr) {
				node = node->right;
				if (node->isLeaf()) {
					if (text.size() >0 ||(text.size() == 0 &&( node->getByte() != 239 && node->getByte() != 187&& node->getByte() != 191)))
						text += node->getByte();
					node = root;
				}
			}
		}
	}
}