#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "header.h"

using namespace std;

const int defaultMaxShootings = MAX_SHOOTINGS;	// 4
const int defaultSizeX = MAX_SIZE_X;	// 10
const int defaultSizeY = MAX_SIZE_Y;	// 100
const int defaultTrackX = 6;			// Track level on screen
//const char defaultGameScreen[defaultSizeX][defaultSizeY];
//const char gameScreen[sizeX][sizeY];

bool shootFromHipAllowed = true;

//shootingEntity shootingList[defaultMaxShootings];
levelEntity createLevel();
playerEntity createPlayer(int);
void createShootings(levelEntity);
bool tryToShoot(levelEntity, char);
void playerMove(levelEntity, int, int);
void raise(levelEntity);
void lower(levelEntity);

void updateScreen(levelEntity);

int play()
{
	levelEntity game = createLevel();
	updateScreen(game);

	bool bUpdateScreen;
	int input = 0;
	while (input != 27 && !game.finished) {
		cout << endl;
		cout << "Move using the arrow keys (>>, up-up, down-down), Quit ESC " << endl;
		input = _getch();
		bUpdateScreen = true;
		switch (input) {
		case 72:						// Up Arrow - H
			playerMove(game, 1, 0);
			break;
		case 80:						// Down Arrow - P
			playerMove(game, -1, 0);
			break;
		case 75:						// Left Arrow - K
			playerMove(game, 0, -1);
			break;
		case 77:						// Right Arrow - M
			playerMove(game, 0, 1);
			break;
		case 0:
		case 224:		// do nothing
			bUpdateScreen = false;
			break;
		default:
			bUpdateScreen = tryToShoot(game, input);
			break;
		}
		if (bUpdateScreen) {
			updateScreen(game);
		}
	}
	if (game.finished) {
		game.player.character = cWinner;
	}
	updateScreen(game);
	return 0;
}

levelEntity createLevel() {
	levelEntity game = {};
	game.sizeX = defaultSizeX;
	game.sizeY = defaultSizeY;
	game.trackX = defaultTrackX;
	game.shootings = defaultMaxShootings;
	game.player = createPlayer(game.trackX);
	createShootings(game);
	return game;
}

playerEntity createPlayer(int trackX) {
	playerEntity player = {};
	player.character = cReady;
	player.posX = trackX;
	player.posY = 1;	// starting position
	return player;
}

void createShootings(levelEntity game) {
	const int shootingsDefaultInterval = 20;
	game.shootings = (game.sizeY - shootingsDefaultInterval) / shootingsDefaultInterval;
	int iRand;
	int shootingPosition;
	for (int i = 0; i < game.shootings; i++) {
		shootingPosition = ((i * shootingsDefaultInterval) + ((shootingsDefaultInterval / 2) + 4)) + (rand() % 13);
		game.shootingList[i].posY = shootingPosition;
		game.shootingList[i].posX = game.trackX;
		// Shooting tables
		game.shootingList[i].char1 = 97 + rand() % 26;
		game.shootingList[i].char2 = 97 + rand() % 26;
		game.shootingList[i].char3 = 97 + rand() % 26;
		// Shooting character and table locations
		if (i % 2 == 0) {
			game.shootingList[i].character = cShootDown;
			game.shootingList[i].shootingTableX = game.shootingList[i].posX - 1;
		}
		else {
			game.shootingList[i].character = cShootUp;
			game.shootingList[i].shootingTableX = game.shootingList[i].posX - 2;
		}
		game.shootingList[i].shootingTableY = game.shootingList[i].posY;
	}
}

bool tryToShoot(levelEntity game, char cShot) {
	if (cShot < 200 && cShot != 72 && cShot != 75 && cShot != 77 && cShot != 80) { // Ignore empty inputs etc and moving
		if (cShot != cHit && cShot != cMiss && cShot != cHipHit) {
			bool fromHip = shootFromHipAllowed && game.player.character == cStand;
			for (int i = 0; i < game.shootings; i++) {
				if (game.player.posY == game.shootingList[i].posY && (game.player.character == game.shootingList[i].character || fromHip)) {
					if (cShot == game.shootingList[i].char1) {
						if (fromHip) {
							game.shootingList[i].char1 = cHipHit;
						}
						else {
							game.shootingList[i].char1 = cHit;
						}
					}
					else if (cShot == game.shootingList[i].char2) {
						if (fromHip) {
							game.shootingList[i].char2 = cHipHit;
						}
						else {
							game.shootingList[i].char2 = cHit;
						}
					}
					else if (cShot == game.shootingList[i].char3) {
						if (fromHip) {
							game.shootingList[i].char3 = cHipHit;
						}
						else {
							game.shootingList[i].char3 = cHit;
						}
					}
					else {
						if (game.shootingList[i].char1 != cHit && game.shootingList[i].char1 != cMiss && game.shootingList[i].char1 != cHipHit) {
							game.shootingList[i].char1 = cMiss;
						}
						else if (game.shootingList[i].char2 != cHit && game.shootingList[i].char2 != cMiss && game.shootingList[i].char2 != cHipHit) {
							game.shootingList[i].char2 = cMiss;
						}
						else if (game.shootingList[i].char3 != cHit && game.shootingList[i].char3 != cMiss && game.shootingList[i].char3 != cHipHit) {
							game.shootingList[i].char3 = cMiss;
						}
					}
				}
			}
		}
		return true;
	}
	return false;
}

void playerMove(levelEntity game, int deltaX, int deltaY) {
	if (deltaY != 0) {
		switch (game.player.character) {
		case cAim:
		case cStand:
			lower(game);
			break;
		case cLay:
			raise(game);
			break;
		case cReady:
			game.player.character = cSki;
			break;
		case cDown:		// Traditional style allowed
		default:
			game.player.character = cReady;
			if (deltaY < 0 && game.player.posY < 2) { // No backing too much..
			}
			else {
				game.player.posY += deltaY;
			}
			if (game.player.posY == game.sizeY - 1) {
				game.finished = true;
			}
		}
	}
	else if (deltaX != 0) {
		if (deltaX > 0) {
			raise(game);
		}
		else {
			lower(game);
		}
	}
}

void raise(levelEntity game) {
	switch (game.player.character) {
	case cAim:
		break;
	case cStand:
		game.player.character = cAim;
		break;
	case cDown:
		game.player.character = cReady;
		break;
	case cLay:
		game.player.character = cDown;
		break;
	default:
		game.player.character = cStand;
	}
}

void lower(levelEntity game) {
	switch (game.player.character) {
	case cAim:
		game.player.character = cStand;
		break;
	case cStand:
		game.player.character = cReady;
		break;
	case cDown:
		game.player.character = cLay;
		break;
	case cLay:
		break;
	default:
		game.player.character = cDown;
	}
}