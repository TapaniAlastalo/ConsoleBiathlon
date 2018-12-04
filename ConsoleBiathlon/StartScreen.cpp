#include "pch.h"
#include <iostream>
#include <conio.h>

using namespace std;

void start(void);
void newGame(void);
int play(void);

void test(void);

void start() {
	//setlocale(LC_ALL, "finnish");
	//test();
	newGame();
}

void test() {
	int input = 0;
	while (input != 27) {
		input = _getch();
		char c = input;
		cout << input << "-" << c << "; ";
	}
}

void newGame() {
	play();
}