#include "ChooseFile.h"
ChooseFile::ChooseFile(){
	this->listOfFiles.push_back("Zip");
	this->listOfFiles.push_back("Unzip");
	this->depth = -1;
	this->choosePathIn = true;
	this->curDirectory = "";
	this->pathIn = "";
	this->pathOut = "";
}
void ChooseFile::changeInput() {
	this->choosePathIn = !this->choosePathIn;
}

bool ChooseFile::getTypeOfWork(){
	return this->typeOfWork;
}

string ChooseFile::getPathIn()
{
	return this->pathIn;
}

string ChooseFile::getPathOut()
{
	return this->pathOut;
}

bool ChooseFile::setDir(){
	if (this->depth < 1 &&this->choosePathIn)
		return false;
	if (this->choosePathIn) {
		if (!this->typeOfWork)
			if (rightHFF(this->listOfFiles[pointer_])) {
				this->pathIn = this->listOfFiles[pointer_];
				this->choosePathIn = false;
				return true;
			}
			else
				return false;
		else {
			this->choosePathIn = false;
			this->pathIn = this->listOfFiles[pointer_];
			return true;
		}
	}
	else {
		if(!isItFile(this->listOfFiles[pointer_]))
		this->pathOut= this->listOfFiles[pointer_];
		return true;
	}
}

void ChooseFile::increasePointer(){
	this->pointer_++;
	if (this->pointer_ == listOfFiles.size())
		this->pointer_ = 0;
}

void ChooseFile::decreasePointer(){
	pointer_--;
	if (pointer_ < 0) pointer_ = listOfFiles.size()-1;
}

void ChooseFile::decreaseDepth() {
	if (this->depth == -1) {
		return;
	}
	if (this->depth == 0) {
		this->listOfFiles.clear();
		this->curDirectory = "";
		this->pathIn = "";
		this->pathOut = "";
		this->choosePathIn = true;
		this->pointer_ = 0;
		this->listOfFiles.push_back("Zip");
		this->listOfFiles.push_back("Unzip");
		this->depth--;
		return;
	}
	if (!isItFile(this->curDirectory)) {
		if (this->depth == 1) {
			this->listOfFiles.clear();
			this->curDirectory = "";
			this->pointer_ = 0;
			this->listOfFiles.push_back("C:\\");
			this->listOfFiles.push_back("D:\\");
			this->depth--;
		}
		else {
			prevDir(this->curDirectory);
			this->listOfFiles.clear();
			this->pointer_ = 0;
			boost::filesystem::directory_iterator begin(this->curDirectory);
			if (!this->typeOfWork && this->choosePathIn)
				dirwalkLite(begin, this->listOfFiles, false);
			else
				dirwalkLite(begin, this->listOfFiles, true);
			this->depth--;
		}
	}
	else {
		prevDir(this->curDirectory);
	}
}

void ChooseFile::increaseDepth() {
	if (this->depth == -1) {
		this->listOfFiles.clear();
		this->curDirectory = "";
		this->listOfFiles.push_back("C:\\");
		this->listOfFiles.push_back("D:\\");
		this->depth++;
		if (this->pointer_ == 0) {
			this->typeOfWork = true;
		}
		else {
			this->typeOfWork = false;
		}
		this->pointer_ == 0;
		return;
	}
	if (listOfFiles.size() > 0) {
		this->curDirectory = this->listOfFiles[pointer_];
		if (!isItFile(this->curDirectory)) {
			this->depth++;
			this->listOfFiles.clear();
			this->pointer_ = 0;
			boost::filesystem::directory_iterator begin(this->curDirectory);
			if (!this->typeOfWork && this->choosePathIn)
				dirwalkLite(begin, this->listOfFiles, false);
			else
				dirwalkLite(begin, this->listOfFiles, true);
		}
		else {
			this->curDirectory = this->listOfFiles[pointer_];
		}
	}
}

std::string ChooseFile::getDirectory(){
	return this->curDirectory;
}

void ChooseFile::print(){
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // получаем адресс консоли 
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Magenta));
	if (this->depth > -1) {
		if (this->typeOfWork)
			cout << "COMPRESSING... ";
		else
			cout << "DECOMPRESSING... ";
	}
	cout << "CHOOSE FILE" << endl <<"press <- back || press -> into || press \\/ down || press /\\ up || press ENTER - choose || press S - START || press Q - QUIT" << endl;
	if (this->choosePathIn) {
		SetConsoleTextAttribute(hConsole, (WORD)((Green << 4) | White));
		cout << "CHOOSE Path In: "<<this->pathIn << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Magenta));
	}
	else
		cout << "Path In: " << this->pathIn << endl;
	if(!this->choosePathIn){
		SetConsoleTextAttribute(hConsole, (WORD)((Green << 4) | White));
		cout << "CHOOSE Path Out: " << this->pathOut << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Magenta));
	}
	else
		cout << "Path Out: " << this->pathOut << endl;
	SetConsoleTextAttribute(hConsole, (WORD)((Green << 4) | White));
	cout<<"Current directory:" << this->curDirectory << endl;
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
	for (int i = 0; i < listOfFiles.size(); i++)
	{//изменение цвета в консолои
		if (i == pointer_) SetConsoleTextAttribute(hConsole, (WORD)((White << 4) | LightBlue));
		cout << listOfFiles[i];
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
		cout << endl;
	}
}