#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "header.h"
#include "TimeHandler.h"
#include "TestHeader.h"

using namespace std;

const int defaultMaxShootings = MAX_SHOOTINGS;	// 4
const int defaultSizeX = MAX_SIZE_X;	// 10
const int defaultSizeY = MAX_SIZE_Y;	// 100
const int defaultTrackX = 6;			// Track level on screen

const int PENALTY_S = 10; // 10 seconds per miss;
const int BONUS_S = 3; // 3 seconds per bonus hit
const int MAX_POINTS = 100000; // ALMOST MAX POINTS..
const int BASE_POINTS = 20000;

bool shootFromHipAllowed = true;

TimeHandler time;

void readySetGo(void);
int play(levelEntity*);
levelEntity prepare(void);
levelEntity createLevel(void);
playerEntity createPlayer(int);
void createShootings(levelEntity*);
void checkPassedShootingTables(levelEntity*);
bool tryToShoot(levelEntity*, char);
void playerMove(levelEntity*, int, int);
void raise(playerEntity*);
void lower(playerEntity*);
// check score
scoreEntity checkResults(levelEntity*);
// for printing
void updateScreen(levelEntity*);
void clearGameScreen(levelEntity*);

scoreEntity newGame() {
	levelEntity game = prepare();
	play(&game);
	scoreEntity score = checkResults(&game);
	pause();
	return score;
}

scoreEntity checkResults(levelEntity *game){
	const int scoreDelay = 100;
	Sleep(scoreDelay);
	if (game->finished) {
		const __int64 delta = time.getDifferenceInMillis();
		game->score.time = delta;
		cout << endl << "TIME: " << time.getHumanReadableTime(delta) << endl;

		Sleep(scoreDelay);

		float shootingPercentage = float(game->score.hits) / float(game->score.hits + game->score.misses) * 100;
		cout << "HITS: " << game->score.hits;
		Sleep(scoreDelay);
		cout << ", Shooting Accuracy " << shootingPercentage << "%" << endl;

		const int minuses = (game->score.misses * PENALTY_S) * 1000;
		Sleep(scoreDelay);
		cout << "MISSES: " << PENALTY_S << " seconds * ";
		Sleep(2 * scoreDelay);
		cout << game->score.misses;
		Sleep(scoreDelay);
		cout << " = " << minuses / 1000 << " seconds" << endl;

		const int bonuses = (game->score.bonuses * BONUS_S) * 1000;
		if (bonuses > 0) {
			Sleep(scoreDelay);
			cout << "BONUS: " << BONUS_S << " seconds * ";
			Sleep(2 * scoreDelay);
			cout << game->score.bonuses;
			Sleep(scoreDelay);
			cout << " = " << (bonuses / 1000) << " seconds" << endl;
		}
		const int score = MAX_POINTS - (game->score.time) - minuses + bonuses + BASE_POINTS;
		Sleep(2 * scoreDelay);
		cout << "SCORE: " << score << endl;
		game->score.points = score;
		return game->score;
	}
	else {
		game->score.time = -1;
		cout << endl << "DNS" << endl;
		return NULL;
	}
}

levelEntity prepare() {
	levelEntity newGame = createLevel();
	clearGameScreen(&newGame);
	return newGame;
}

void readySetGo() {
	int sleepDuration = 20;
	int input = 0;
	cout << endl << "READY. ( Press any key )" << endl;
	while (input == 0 || input == 224) {
		input = _getch();
	}
	input = 0;
	cout << endl << "SET.. ( Press any key )" << endl;
	while (input == 0 || input == 224) {
		input = _getch();
	}
	cout << endl << "GO..." << endl;
	Sleep(sleepDuration);
}

int play(levelEntity *game)
{
	updateScreen(game);
	cout << endl << "Move using the arrow keys (>>, up-up, down-down) and shoot by letters shown on tables. ( Quit ESC )" << endl;
	bool bUpdateScreen;
	int input = 0;
	readySetGo();
	time.start();		// START TAKING TIME
	while (input != 27 && !game->finished) {
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
			cout << endl << "TIME: " << time.getHumanReadableTime(time.getIntervalInMillis()) << endl;
			cout << endl << "Move using the arrow keys (>>, up-up, down-down) and shoot by letters shown on tables. ( Quit ESC )" << endl;
		}
	}
	checkPassedShootingTables(game);
	if (game->finished) {
		if (game->score.misses > 2) {
			game->player.character = cLay;
		}
		else {
			game->player.character = cWinner;
		}
	}
	updateScreen(game);
	return 0;
}

levelEntity createLevel() {
	levelEntity game = { '0' };
	game.sizeX = defaultSizeX;
	game.sizeY = defaultSizeY;
	game.trackX = defaultTrackX;
	game.player = createPlayer(game.trackX);
	createShootings(&game);
	return game;
}

playerEntity createPlayer(int trackX) {
	playerEntity player = { '0' };
	player.character = cReady;
	player.posX = trackX;
	player.posY = 1;	// starting position
	return player;
}

void createShootings(levelEntity *game) {
	const int shootingsDefaultInterval = 20;
	game->shootings = (game->sizeY - shootingsDefaultInterval) / shootingsDefaultInterval;
	int iRand;
	int shootingPosition;
	for (int i = 0; i < game->shootings; i++) {
		shootingPosition = ((i * shootingsDefaultInterval) + ((shootingsDefaultInterval / 2) + 4)) + (rand() % 13);
		game->shootingList[i].posY = shootingPosition;
		game->shootingList[i].posX = game->trackX;
		// Shooting tables
		game->shootingList[i].char1 = 97 + rand() % 26;
		game->shootingList[i].char2 = 97 + rand() % 26;
		game->shootingList[i].char3 = 97 + rand() % 26;
		// Shooting character and table locations
		if (i % 2 == 0) {
			game->shootingList[i].character = cShootDown;
			game->shootingList[i].shootingTableX = game->shootingList[i].posX - 1;
		}
		else {
			game->shootingList[i].character = cShootUp;
			game->shootingList[i].shootingTableX = game->shootingList[i].posX - 2;
		}
		game->shootingList[i].shootingTableY = game->shootingList[i].posY;

	}
}

/*
After race check if shooting tables were passed purposely or accidentally.. penalty...
*/
void checkPassedShootingTables(levelEntity *game) {
	for (int i = 0; i < game->shootings; i++) {
		if (game->shootingList[i].char1 != cHit && game->shootingList[i].char1 != cMiss && game->shootingList[i].char1 != cHipHit) {
			game->shootingList[i].char1 = cMiss;
			game->score.misses++;
		}
		if (game->shootingList[i].char2 != cHit && game->shootingList[i].char2 != cMiss && game->shootingList[i].char2 != cHipHit) {
			game->shootingList[i].char2 = cMiss;
			game->score.misses++;
		}
		if (game->shootingList[i].char3 != cHit && game->shootingList[i].char3 != cMiss && game->shootingList[i].char3 != cHipHit) {
			game->shootingList[i].char3 = cMiss;
			game->score.misses++;
		}
	}
}

bool tryToShoot(levelEntity *game, char cShot) {
	if (cShot < 200 && cShot != 72 && cShot != 75 && cShot != 77 && cShot != 80) { // Ignore empty inputs etc and moving
		if (cShot != cHit && cShot != cMiss && cShot != cHipHit) {
			bool fromHip = shootFromHipAllowed && game->player.character == cStand;
			for (int i = 0; i < game->shootings; i++) {
				if (game->player.posY == game->shootingList[i].posY && (game->player.character == game->shootingList[i].character || fromHip)) {
					if (cShot == game->shootingList[i].char1) {
						if (fromHip) {
							game->shootingList[i].char1 = cHipHit;
							game->score.bonuses++;					// ADD BONUS HERE
						}
						else {
							game->shootingList[i].char1 = cHit;
						}
						game->score.hits++;
					}
					else if (cShot == game->shootingList[i].char2) {
						if (fromHip) {
							game->shootingList[i].char2 = cHipHit;
							game->score.bonuses++;					// ADD BONUS HERE
						}
						else {
							game->shootingList[i].char2 = cHit;
						}
						game->score.hits++;
					}
					else if (cShot == game->shootingList[i].char3) {
						if (fromHip) {
							game->shootingList[i].char3 = cHipHit;
							game->score.bonuses++;					// ADD BONUS HERE
						}
						else {
							game->shootingList[i].char3 = cHit;
						}
						game->score.hits++;
					}
					else {
						if (game->shootingList[i].char1 != cHit && game->shootingList[i].char1 != cMiss && game->shootingList[i].char1 != cHipHit) {
							game->shootingList[i].char1 = cMiss;
							game->score.misses++;
						}
						else if (game->shootingList[i].char2 != cHit && game->shootingList[i].char2 != cMiss && game->shootingList[i].char2 != cHipHit) {
							game->shootingList[i].char2 = cMiss;
							game->score.misses++;
						}
						else if (game->shootingList[i].char3 != cHit && game->shootingList[i].char3 != cMiss && game->shootingList[i].char3 != cHipHit) {
							game->shootingList[i].char3 = cMiss;
							game->score.misses++;
						}
					}
				}
			}
		}
		return true;
	}
	return false;
}

void playerMove(levelEntity *game, int deltaX, int deltaY) {
	playerEntity *player = &game->player;
	if (deltaY != 0) {
		switch (player->character) {
		case cAim:
		case cStand:
			lower(player);
			break;
		case cLay:
			raise(player);
			break;
		case cReady:
			player->character = cSki;
			break;
		case cDown:		// Traditional style allowed
		default:
			player->character = cReady;
			if (deltaY < 0 && player->posY < 2) { // No backing too much..
			}
			else {
				player->posY += deltaY;
			}
			if (player->posY == game->sizeY - 1) {
				game->finished = true;
			}
		}
	}
	else if (deltaX != 0) {
		if (deltaX > 0) {
			raise(player);
		}
		else {
			lower(player);
		}
	}
}

void raise(playerEntity *player) {
	switch (player->character) {
	case cAim:
		break;
	case cStand:
		player->character = cAim;
		break;
	case cDown:
		player->character = cReady;
		break;
	case cLay:
		player->character = cDown;
		break;
	default:
		player->character = cStand;
	}
}

void lower(playerEntity *player) {
	switch (player->character) {
	case cAim:
		player->character = cStand;
		break;
	case cStand:
		player->character = cReady;
		break;
	case cDown:
		player->character = cLay;
		break;
	case cLay:
		break;
	default:
		player->character = cDown;
	}
}