#include "pch.h"
#include <iostream>
#include <conio.h>
#include "Header.h"
#include "TestHeader.h"

using namespace std;

void printTAG(string);

void printTAG(string TAG) {
	cout << endl << "_________ "<< TAG << " _________"<< endl;
}

void testInput(string TAG) {
	printTAG(TAG);
	testInput();
}

void testInput() {
	int input = 0;
	cout << endl << "Press ESC to go forward";
	while (input != 27) {
		input = _getch();
		char c = input;
		cout << input << "-" << c << "; ";
	}
}

void testOutput(string output, string TAG) {
	printTAG(TAG);
	testOutput(output);
}

void testOutput(char output, string TAG) {
	printTAG(TAG);
	testOutput(output);
}

void testOutput(int output, string TAG) {
	printTAG(TAG);
	testOutput(output);
}

void testOutput(string output) {
	cout << "Output:" << output << endl;
}

void testOutput(char output) {
	cout << "Output:" << output << endl;
}

void testOutput(int output) {
	cout << "Output:" << output << endl;
}

void testLevel(levelEntity game, string TAG) {
	printTAG(TAG);
	testLevel(game);
}

void testLevel(levelEntity game) {
	// Level
	cout << "Size " << game.sizeX << "*" << game.sizeY << ", TrackX=" << game.trackX << endl;
	// player
	playerEntity player = game.player;
	cout << "Player: " << player.character << ", " << player.posX << ", " << player.posY << endl;
	// shooting
	cout << "Shootings: " << game.shootings << ", finished? " << game.finished << endl;
	for (int i = 0; i < game.shootings; i++) {
		shootingEntity shooting = game.shootingList[i];
		cout << "Shooting-" << i << endl;
		cout << shooting.character << ", [" << shooting.char1 << ", " << shooting.char2 << ", " << shooting.char3 << "]" << endl;
		cout <<shooting.posX << ", " << shooting.posY << ", " << shooting.shootingTableX << ", " << shooting.shootingTableY << endl;
	}
	pause();
}

void pause() {
	cout << endl << "Press ESC to go forward" << endl;
	while (_getch() != 27);	// stop
}

void pause(string output) {
	cout << endl << output << endl;
	while (_getch() != 27);	// stop
}

void pause(string output, string TAG) {
	cout << endl << TAG << endl;
	cout << endl << output << endl;
	while (_getch() != 27);	// stop
}