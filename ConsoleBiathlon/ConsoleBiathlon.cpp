#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Header.h"
#include "TimeHandler.h"

using namespace std;

void initialize(void);
void startScreen(void);
void selection(void);
void selectionTexts(void);
scoreEntity newGame(void);
void showHighScores(void);

void loadScoresFromFile(scoreEntity*, int*);
void saveScoresToFile(scoreEntity*, int*);
void tryToSaveScores(scoreEntity*, scoreEntity, int*);

scoreEntity scores[50];
int noOfScores;

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
	noOfScores = 0;
	loadScoresFromFile(scores, &noOfScores);
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
			tryToSaveScores(scores, score, &noOfScores);
			selectionTexts();
			break;
		case 27:	// ESC
		default:
			break;
		}
	}
}

void tryToSaveScores(scoreEntity *scores, scoreEntity score, int *scoresSize) {
	if (score.points > 0) {
		scores[*scoresSize] = score;
		(*scoresSize)++;
		saveScoresToFile(scores, scoresSize);
	}
}

void selectionTexts() {
	system("CLS");
	cout << "_________________CONSOLE BIATHLON________________" << endl;
	Sleep(startDelayMS);
	cout << endl << "Press (s) key to start new game (ESC to Quit)" << endl;
	Sleep(startDelayMS);
	showHighScores();
}

void showHighScores() {
	cout << endl << endl << "________________HIGH SCORES________________";
	cout << endl << "## - " << "POINTS" << " : " << "TIME" << " : " << "ACCURACY" << " : " << "BONUS" << endl;
	TimeHandler time;
	if (noOfScores > 0) {		
		for (int i = 0; i < noOfScores; i++) {
			scoreEntity score = scores[i];
			float accuracy = (float(score.hits) / float(score.hits + score.misses)) * 100;
			cout << (i + 1) << " - " << score.points << " : " << time.getHumanReadableTime(score.time) << " : " << accuracy << "% : " << scores->bonuses << endl;
		}
	}
	else {
		cout << "Not any attempts yet..";
	}
}

