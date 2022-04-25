#include"Unzipper.h"
#include<fstream>
void Unzipper:: decompress(string pathOut) {
	this->pathOut = pathOut;
	ifstream::pos_type pos;
	pos=getPaths(this->pathIn, this->listOfFiles, this->pathOut);
	createDir(this->listOfFiles);

	Funcs fun;
	for (int i = 0; i < this->listOfFiles.size(); i++) {
		if (isItFile(this->listOfFiles[i])) {
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


