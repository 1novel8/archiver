#pragma once
#include<string>
#include<Windows.h>
#include<iostream>
#include<vector>
#include"Filesys.h"

enum ConsoleColor { //перечиление всех цветов
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
	ConsoleColor headColor_ = White;//цвет фона консоли
	bool typeOfWork;//1-архивировать 0-распаковать
	bool choosePathIn;
public:
	ChooseFile(); // пустой конструктор
	ChooseFile(string CurDirectory, ConsoleColor headColor);   //конструктор

	int getPointer() const { return pointer_; } //получение указателя
	bool setDir();
	void increasePointer(); //увеличение указателя
	void decreasePointer();//уменьшение указателя
	void decreaseDepth();//уменьшаем глубину
	void increaseDepth();//увеличиваем глубину
	std::string getDirectory();
	void print(); //вывод меню в консоль
	void changeInput();
	bool getTypeOfWork();
	string getPathIn();
	string getPathOut();
};
