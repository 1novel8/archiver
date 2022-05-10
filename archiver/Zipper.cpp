#include"Zipper.h"

using namespace std;

void Zipper::compress(string pathOut) {
	if (isItFile(this->pathIn)) {
		this->listOfFiles.push_back(this->pathIn);
	}
	else {
		boost::filesystem::directory_iterator begin(this->pathIn);
		this->listOfFiles.push_back(this->pathIn);
		dirwalk(begin, this->listOfFiles);
	}
	this->pathOut=pathOut+getName(this->pathIn);

	writePaths(this->pathIn, this->pathOut, listOfFiles);
	cout << endl << "Wait, it may take some time:"<<endl;
	for (int i = 0; i < listOfFiles.size(); i++) {
		int value = i * 100 / (listOfFiles.size()-1);
		cout<<"\r" << value << "%";
		if (isItFile(listOfFiles[i])) {
			Funcs fun;
			this->weight = vector<int>(0x100, 0);

			fun.readFile(this->listOfFiles[i], this->weight);

			fun.fillQueue(this->weight, this->queue);
			fun.buildTree(queue);

			vector<string>codes(0x100, "");

			this->root = queue.top();
			fun.make_code(this->root, "", codes);

			this->message = fun.message2code(this->listOfFiles[i], codes);
			//cout << message << endl;
			fun.writeFile(this->pathOut, this->weight, this->queue, message);
		}
	}
	cout << endl << "GOOD JOB!!!" << endl
		<< "Your " << getName(this->pathIn)
		<< " is here: " << this->pathOut << endl;
	system("pause");
}
//
//Funcs fun;
//fun.readFile(this->pathIn, this->weight);
//
//fun.fillQueue(this->weight, this->queue);
//fun.buildTree(queue);
//
//vector<string>codes(0x100, "");
//
//this->root = queue.top();
//fun.make_code(this->root, "", codes);
//
//this->message = fun.message2code(this->pathIn, codes);
////cout << message << endl;
//fun.writeFile(this->pathOut, this->weight, this->queue, message);