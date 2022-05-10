#pragma once
#include<string>
#include<Windows.h>
#include<iostream>
#include<vector>
#include"Filesys.h"

enum ConsoleColor { //����������� ���� ������
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};


using namespace std;
class ChooseFile
{
private:
	int pointer_ = 0;
	int depth;
	vector<string> listOfFiles;
	string curDirectory;
	string pathIn;
	string pathOut;
	ConsoleColor headColor_ = White;//���� ���� �������
	bool typeOfWork;//1-������������ 0-�����������
	bool choosePathIn;
public:
	ChooseFile(); // ������ �����������
	ChooseFile(string CurDirectory, ConsoleColor headColor);   //�����������

	int getPointer() const { return pointer_; } //��������� ���������
	bool setDir();
	void increasePointer(); //���������� ���������
	void decreasePointer();//���������� ���������
	void decreaseDepth();//��������� �������
	void increaseDepth();//����������� �������
	std::string getDirectory();
	void print(); //����� ���� � �������
	void changeInput();
	bool getTypeOfWork();
	string getPathIn();
	string getPathOut();
};
