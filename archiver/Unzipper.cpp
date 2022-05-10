#include"Unzipper.h"
#include<fstream>
void Unzipper:: decompress(string pathOut) {
	this->pathOut = pathOut;
	ifstream::pos_type pos;
	pos=getPaths(this->pathIn, this->listOfFiles, this->pathOut);
	createDir(this->listOfFiles);

	Funcs fun;
	cout << endl << "Wait, it may take some time:" << endl;

	for (int i = 0; i < this->listOfFiles.size(); i++) {
		int value = i * 100 / (listOfFiles.size() - 1);
		cout << "\r" << value << "%";
		if (listOfFiles[i][listOfFiles[i].size() - 1] == 'd') {
			listOfFiles[i].pop_back();
		}
		else{
			listOfFiles[i].pop_back();
			this->weight = vector<int>(0x100, 0);
			this->message = "";
			pos = fun.readFile(this->pathIn, pos, this->weight, this->message);

			fun.fillQueue(this->weight, this->queue);
			fun.buildTree(this->queue);

			this->root = this->queue.top();

			string text = "";
			fun.decode(this->root, this->message, text);
			ofstream out(this->listOfFiles[i], ofstream::binary);
			if (!out) {
				cerr << "Error in [" << __func__ << "]:" /*<< strerror_s(errno)*/;
				return;
			}
			for (int i = 0; i < text.size(); i++) {
				out.write(&text[i], sizeof(char));
			}
		}
	}
	string name=getName(this->pathIn);
	name.pop_back();
	name.pop_back();
	name.pop_back();
	name.pop_back();
	cout << "GOOD JOB!!!" << endl
		<< "Your " << name
		<< " is here: " << this->pathOut <<name<< endl;
	system("pause");

	
}


	//fun.readFile(this->pathIn, this->weight, this->message);

	//fun.fillQueue(this->weight, this->queue);
	//fun.buildTree(this->queue);

	//this->root = this->queue.top();

	//string text = "";
	//fun.decode(this->root, this->message, text);
	//ofstream out(pathOut, ofstream::binary);
	//if (!out) {
	//	cerr << "Error in [" << __func__ << "]:" /*<< strerror_s(errno)*/;
	//	return;
	//}
	//for (int i = 0; i < text.size(); i++) {
	//	out.write(&text[i], sizeof(char));
	//}


