#pragma once
#include"Entity.h"
#include"Funcs.h"


using namespace std;


class Zipper :protected Entity{

public:
	friend class Funcs;
	Zipper(string pathIn) :Entity(pathIn) {};
	void compress( string pathOut);
};

