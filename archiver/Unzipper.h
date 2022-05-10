#pragma once
#include"Entity.h"
#include"Funcs.h"


using namespace std;


class Unzipper :protected Entity {

public:
	friend class Funcs;
	Unzipper(string pathIn) :Entity(pathIn) {};
	void decompress(string pathOut);
};