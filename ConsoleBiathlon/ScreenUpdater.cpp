#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "header.h"
#include "TestHeader.h"

using namespace std;

void populateScreen(levelEntity*);
void populateBackground(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y]);
void populateTrack(levelEntity*);
void populateShootingPositions(levelEntity*);
void populatePlayer(levelEntity*);
void printScreen(levelEntity*);

char gameScreen[MAX_SIZE_X][MAX_SIZE_Y];

void updateScreen(levelEntity *game) {
	populateScreen(game);
	printScreen(game);
}

void populateScreen(levelEntity *game) {
	populateBackground(game, gameScreen);
	populateTrack(game);
	populateShootingPositions(game);
	populatePlayer(game);
}

void populateShootingPositions(levelEntity *level) {
	levelEntity game = *level;
	const char cTableStart = '[';
	const char cTableEnd = ']';
	const char cTablePillar = '|';
	// populate shooting positions
	for (int i = 0; i < game.shootings; i++) {
		shootingEntity shooting = game.shootingList[i];
		gameScreen[shooting.posX][shooting.posY] = shooting.character;
		// populate shooting table
		gameScreen[shooting.shootingTableX][shooting.shootingTableY] = cTableStart;
		gameScreen[shooting.shootingTableX][shooting.shootingTableY + 4] = cTableEnd;
		// if shooting standing add table pillars
		if (shooting.character == cAim) {
			gameScreen[shooting.shootingTableX + 1][shooting.shootingTableY + 1] = cTablePillar;
			gameScreen[shooting.shootingTableX + 1][shooting.shootingTableY + 3] = cTablePillar;
		}
		// if at shooting position show tables
		if (game.player.posY == shooting.posY && game.player.character == shooting.character) {
			gameScreen[shooting.shootingTableX][shooting.shootingTableY + 1] = shooting.char1;
			gameScreen[shooting.shootingTableX][shooting.shootingTableY + 2] = shooting.char2;
			gameScreen[shooting.shootingTableX][shooting.shootingTableY + 3] = shooting.char3;
		}
		if (game.finished) {
			if (shooting.char1 == cHit || shooting.char1 == cMiss || shooting.char1 == cHipHit) {
				gameScreen[shooting.shootingTableX][shooting.shootingTableY + 1] = shooting.char1;
			}
			if (shooting.char2 == cHit || shooting.char2 == cMiss || shooting.char2 == cHipHit) {
				gameScreen[shooting.shootingTableX][shooting.shootingTableY + 2] = shooting.char2;
			}
			if (shooting.char3 == cHit || shooting.char3 == cMiss || shooting.char3 == cHipHit) {
				gameScreen[shooting.shootingTableX][shooting.shootingTableY + 3] = shooting.char3;
			}
		}
	}
}

void populateTrack(levelEntity *level) {
	levelEntity game = *level;
	for (int i = 0; i < game.sizeY; i++) {
		switch (i) {
		case 0:
			gameScreen[game.trackX][i] = cEmpty;
			break;
		case 1:
			gameScreen[game.trackX][i] = cFinished;
			break;
		default:
			if (i == game.sizeY - 2) {
				if (game.finished) {
					gameScreen[game.trackX][i] = cFinished;
				}
				else {
					gameScreen[game.trackX][i] = cGoal;
				}
			}
			else if (i == game.sizeY - 1) {
				gameScreen[game.trackX][i] = cEmpty;
			}
			else {
				gameScreen[game.trackX][i] = cTrack;
			}
		}
	}
}

void populatePlayer(levelEntity *level) {
	levelEntity game = *level;
	gameScreen[game.player.posX][game.player.posY] = game.player.character; // Add player icon
}

void printScreen(levelEntity *level) {
	levelEntity game = *level;
	system("CLS");
	cout << "_______________________________ CONSOLE BIATHLON SIMULATOR ________________________________" << endl;
	for (int i = 0; i < game.sizeX; ++i)
	{
		for (int j = 0; j < game.sizeY; ++j)
		{
			cout << gameScreen[i][j];
		}
		cout << endl;
	}
}

void clearGameScreen(levelEntity *level) {
	levelEntity game = *level;
	for (int i = 0; i < game.sizeX; ++i)
	{
		for (int j = 0; j < game.sizeY; ++j)
		{
			gameScreen[i][j] = cEmpty;
		}
	}
}