#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Header.h"
#include "TimeHandler.h"
#include "TestHeader.h"
#include <ctime>

using namespace std;

void initialize(void);
void startScreen(void);
void selection(void);
void selectionTexts(void);

scoreEntity newGame(void);

void loadScores(void);
void showHighScores(void);
void showHighScoresSnap(void);
void tryToSaveScores(scoreEntity);

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
	loadScores();
	srand(time(NULL));		// set random seed for random function
}

void selection() {
	bool exit = false;
	int input = 0;
	selectionTexts();
	while (input != 27 && !exit) {	// ESC
		input = _getch();
		switch (input) {
		case 49:	// 1
		case 83:	// s
		case 115:	// S
			scoreEntity score = newGame();	// Start new game
			tryToSaveScores(score);
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
	cout << "_________________CONSOLE BIATHLON________________" << endl;
	Sleep(startDelayMS);
	cout << endl << "Press (s) key to start new game (ESC to Quit)" << endl;
	Sleep(startDelayMS);
	showHighScoresSnap();
}

