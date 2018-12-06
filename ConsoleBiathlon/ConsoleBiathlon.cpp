#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Header.h"

using namespace std;

void initialize(void);
void startScreen(void);
void selection(void);
void selectionTexts(void);
scoreEntity newGame(void);

const int startDelayMS = 600;

int main()
{
	initialize();
	startScreen();
	selection();
	return 0;
}

void initialize() {
	//setlocale(LC_ALL, "finnish");
}

void selection() {
	bool exit = false;
	int input = 0;
	scoreEntity score;
	selectionTexts();
	while (input != 27 && !exit) {	// ESC
		input = _getch();
		switch (input) {
		case 49:	// 1
		case 83:	// s
		case 115:	// S
			score = newGame();	// Start new game
			selectionTexts();
			break;
		case 27:	// ESC
		default:
			break;
		}
	}
}

void selectionTexts() {
	system("CLS");
	cout << "CONSOLE BIATHLON" << endl;
	Sleep(startDelayMS);
	cout << endl << "Press (s) key to start new game (ESC to Quit)" << endl;
}

void showHighScores() {

}

