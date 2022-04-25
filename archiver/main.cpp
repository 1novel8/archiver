#define _CRT_SECURE_NO_WARNINGS
#include"Zipper.h"
#include"Unzipper.h"

using namespace std;

int main() {

	Zipper zipper("D:\\Study\\test");
	zipper.compress("D:\\Study\\sem4");

	Unzipper unzipper("D:\\Study\\sem4\\test.hff");
	unzipper.decompress("D:\\Study\\sem4\\");
}