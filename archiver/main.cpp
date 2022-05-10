#define _CRT_SECURE_NO_WARNINGS
#include"Zipper.h"
#include"Unzipper.h"
#include"ChooseFile.h"
#include"conio.h"
#include<locale.h>



int main() {
	setlocale(LC_ALL, "ru");
	ChooseFile menu; // создаётся объект класса меню
	char c;
	string path;
	while (true){
		menu.print();			//<-75 ->77
		do{
			c = _getch();
			
		} while (c!='s' && c != 'q' && c != 13 && c != 72 && c != 80 && c != 75 && c != 77 && c != 32);

		switch (c){
		case 72:
			menu.decreasePointer(); break;
		case 80:
			menu.increasePointer(); break;
		case 75:
			menu.decreaseDepth(); break;
		case 77:
			menu.increaseDepth(); break;
		case 13:
			menu.setDir();
			break;
		case 32:
			menu.changeInput();
			break;
		case 's': {
			if (menu.getTypeOfWork()) {
				Zipper zipper(menu.getPathIn());
				zipper.compress(menu.getPathOut());
			}
			else {
				Unzipper unzipper(menu.getPathIn());
				unzipper.decompress(menu.getPathOut());
			}
			break;
		}
		case'q':
			return 0;
		default:
			return 0;
		}
	}

	//Zipper zipper("D:\\Study\\test");
	//zipper.compress("D:\\Study\\sem4");

	//Unzipper unzipper("D:\\Study\\sem4\\test.hff");
	//unzipper.decompress("D:\\Study\\sem4\\");
}