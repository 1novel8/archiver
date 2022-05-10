#pragma once
#include<boost/filesystem/operations.hpp>
#include<iostream>
#include<fstream>
#include<cassert>

void dirwalk(boost::filesystem::directory_iterator path, std::vector<std::string>& paths);
void dirwalkLite(boost::filesystem::directory_iterator path, std::vector<std::string>& paths, bool show);
std::string getName(std::string path);
bool isItFile(std::string);
void writePaths(std::string pathIn, std::string pathOut, std::vector<std::string>listOfFiles);
std::ifstream::pos_type getPaths(std::string pathIn, std::vector<std::string>& listOfFiles, std::string pathOut);
void createDir(std::vector<std::string>listOfFiles);
void prevDir(std::string& dir);
bool findWord(std::string mainStr, std::string str);
bool rightHFF(std::string str);