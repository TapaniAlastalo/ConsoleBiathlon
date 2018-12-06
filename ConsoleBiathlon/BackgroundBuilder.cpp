#include "pch.h"
#include <iostream>
#include "header.h"
#include "TestHeader.h"

int bigForrestPosY;

char getSpectator(levelEntity*);
char getFlag(levelEntity*);

void addTree(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);
void addHouses(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);
void addWarehouse(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);
void addForrest(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);
void addBigForrest(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);
void addSpectatorArea(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);
void addBigSpectatorArea(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);

void generateSky(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y]);
void generateGround(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y]);
void populateForeground(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y]);
void populateAds(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y]);

void populateBackground(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y]) {
	generateSky(level, gameScreen); 
	generateGround(level, gameScreen);
	// populate background with this and that	
	for (int i = 0; i < level->sizeY; i++) {
		if (i == 1) { // populate buildings
			addHouses(level, gameScreen, i);
		}
		else if (i == 6) {
			addWarehouse(level, gameScreen, i);
		}
		else if (i == 13) { // tree
			addTree(level, gameScreen, i);
		}
		else if (i == 25) { // big forest
			addBigForrest(level, gameScreen, i);
		} // spectator areas
		else if (i == 67) { // long specator area
			addBigSpectatorArea(level, gameScreen, i);
		}
		else if (i == 91) {// short specator area
			addSpectatorArea(level, gameScreen, i);
		}
	}
	populateForeground(level, gameScreen);
}

void generateSky(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y]) {
	for (int i = 0; i < level->trackX - 1; i++)		// Add stars and moon
	{
		for (int j = 0; j < level->sizeY; j++)
		{
			if (j != 0) {
				if (i == 0 && j % 29 == 0) {		// rand() % 7
					gameScreen[i][j] = cStar;
				}
				else	if (i == 1 && j % 7 == 0) {		// rand() % 7
					gameScreen[i][j] = cStar;
				}
				else if (i == 2 && j % 13 == 0) {		// rand() % 7
					gameScreen[i][j] = cStar;
				}
				else if (i == 3 && j % 37 == 0) {		// rand() % 7
					gameScreen[i][j] = cStar;
				}
				else {
					//gameScreen[i][j] = cEmpty;
				}
			}
		}
	}
	gameScreen[1][2] = cMoonDark;
	gameScreen[1][3] = cMoonHalf;
}

void generateGround(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y]) {
	char cGround = '.';
	for (int i = level->trackX + 1; i < level->sizeX; i++) {
		for (int j = 0; j < level->sizeY; j++)
		{
			if ((i + j) % 3 == 0) {
				gameScreen[i][j] = cGround;
			}
			//else { gameScreen[i][j] = cEmpty;	}
		}
	}
	bigForrestPosY = -1;	// default not populated
}

void addTree(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
	gameScreen[level->trackX - 1][posY] = cSlash;
	gameScreen[level->trackX - 2][posY] = cSlash;
	gameScreen[level->trackX - 1][posY+1] = cBackSlash;
	gameScreen[level->trackX - 2][posY+1] = cBackSlash;
}

void addHouses(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
	gameScreen[level->trackX - 2][posY] = cSlash;
	gameScreen[level->trackX - 1][posY] = cPole;
	gameScreen[level->trackX - 3][posY+1] = cTop;
	gameScreen[level->trackX - 2][posY+2] = cBackSlash;
	gameScreen[level->trackX - 3][posY+2] = cSlash;
	gameScreen[level->trackX - 1][posY+2] = cPole;
	gameScreen[level->trackX - 4][posY+3] = cTop;
	gameScreen[level->trackX - 4][posY+4] = cTop;
	gameScreen[level->trackX - 3][posY+5] = cBackSlash;
	gameScreen[level->trackX - 2][posY+5] = cPole;
}

void addWarehouse(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
	gameScreen[level->trackX - 1][posY] = cPole;
	gameScreen[level->trackX - 2][posY] = cPole;
	gameScreen[level->trackX - 3][posY + 1] = cTop;
	gameScreen[level->trackX - 1][posY + 1] = cPole;
	gameScreen[level->trackX - 2][posY + 2] = cTop;
	gameScreen[level->trackX - 3][posY + 2] = cTop;
	gameScreen[level->trackX - 2][posY + 3] = cTop;
	gameScreen[level->trackX - 3][posY + 3] = cTop;
	gameScreen[level->trackX - 1][posY + 4] = cPole;
	gameScreen[level->trackX - 3][posY + 4] = cTop;
	gameScreen[level->trackX - 1][posY + 5] = cPole;
	gameScreen[level->trackX - 2][posY + 5] = cPole;
}

void addForrest(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
	int iRand = 2 * (rand() % 2);		// randomise wich way the forrest will be planted
	for (int i = 0; i < 6; i++) {
		if ((i + iRand) % 4 == 0) {
			gameScreen[level->trackX - 1][posY + i] = cSlash;
			gameScreen[level->trackX - 2][posY + i] = cSlash;
		}
		else if ((i + iRand) % 4 == 1) {
			gameScreen[level->trackX - 1][posY + i] = cBackSlash;
			gameScreen[level->trackX - 2][posY + i] = cBackSlash;
		}
		else if ((i + iRand) % 4 == 2) {
			gameScreen[level->trackX - 2][posY + i] = cSlash;
			gameScreen[level->trackX - 3][posY + i] = cSlash;
		}
		else {
			gameScreen[level->trackX - 2][posY + i] = cBackSlash;
			gameScreen[level->trackX - 3][posY + i] = cBackSlash;
		}
	}
}

void addBigForrest(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
	for (int i = 0; i < 12; i++) {
		if (i % 4 == 0) {
			gameScreen[level->trackX - 1][posY + i] = cSlash;
			gameScreen[level->trackX - 2][posY + i] = cSlash;
		}
		else if (i % 4 == 1) {
			gameScreen[level->trackX - 1][posY + i] = cBackSlash;
			gameScreen[level->trackX - 2][posY + i] = cBackSlash;
		}
		else if (i % 4 == 2) {
			gameScreen[level->trackX - 2][posY + i] = cSlash;
			gameScreen[level->trackX - 3][posY + i] = cSlash;
		}
		else {
			gameScreen[level->trackX - 2][posY + i] = cBackSlash;
			gameScreen[level->trackX - 3][posY + i] = cBackSlash;
		}
	}
	bigForrestPosY = posY;
}

void addSpectatorArea(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
	for (int i = 0; i < 8; i++) {
		if (i == 0) {// short specator area
			gameScreen[level->trackX - 1][posY + i] = cSlash;
			gameScreen[level->trackX - 2][posY + i + 1] = cSlash;
		}
		else if (i == 7) {
			gameScreen[level->trackX - 1][posY + i] = cSlash;
			gameScreen[level->trackX - 2][posY + i + 1] = cSlash;
			gameScreen[level->trackX - 3][posY + i - 1] = cTop;
			gameScreen[level->trackX - 3][posY + i] = cTop;
			gameScreen[level->trackX - 3][posY + i + 1] = cTop;
			gameScreen[level->trackX - 3][posY + i] = getFlag(level);
			gameScreen[level->trackX - 2][posY + i] = getSpectator(level);
			gameScreen[level->trackX - 1][posY + i - 1] = getSpectator(level);
		}
		else if (i > 1 && i < 7) {
			gameScreen[level->trackX - 3][posY + i] = cTop;
			if (i % 2 == 1) {
				gameScreen[level->trackX - 3][posY + i] = getFlag(level);
			}
			gameScreen[level->trackX - 2][posY + i] = getSpectator(level);
			gameScreen[level->trackX - 1][posY + i - 1] = getSpectator(level);
		}
	}
}

void addBigSpectatorArea(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
	for (int i = 0; i < 17; i++) {
		if (i == 0 || i == 8) {// short specator area
			gameScreen[level->trackX - 1][posY + i] = cSlash;
			gameScreen[level->trackX - 2][posY + i + 1] = cSlash;
		}
		else if (i == 7 || i == 15) {
			gameScreen[level->trackX - 1][posY + i] = cSlash;
			gameScreen[level->trackX - 2][posY + i + 1] = cSlash;
			gameScreen[level->trackX - 3][posY + i - 1] = cTop;
			gameScreen[level->trackX - 3][posY + i] = cTop;
			gameScreen[level->trackX - 3][posY + i + 1] = cTop;
			gameScreen[level->trackX - 3][posY + i] = getFlag(level);
			gameScreen[level->trackX - 2][posY + i] = getSpectator(level);
			gameScreen[level->trackX - 1][posY + i - 1] = getSpectator(level);
		}
		else if ((i > 1 && i < 7) || (i > 9 && i < 15)) {
			gameScreen[level->trackX - 3][posY + i] = cTop;
			if (i % 2 == 1) {
				gameScreen[level->trackX - 3][posY + i] = getFlag(level);
			}
			gameScreen[level->trackX - 2][posY + i] = getSpectator(level);
			gameScreen[level->trackX - 1][posY + i - 1] = getSpectator(level);
		}
	}
}

/*
Get Specator either sitting or cheering
*/
char getSpectator(levelEntity *level) {
	levelEntity game = *level;
	int propability;
	if (game.finished) {
		propability = 3;
	}
	else {
		propability = 13;
	}
	char cSpectator;
	int random = rand() % propability;
	if (random == 0 || random == 1) {
		cSpectator = cCheer;
	}
	else {
		cSpectator = cSpectate;
	}
	return cSpectator;
}

/*
Get flag either calm or firm
*/
char getFlag(levelEntity *level) {
	levelEntity game = *level;
	int propability = 3;
	if (game.finished) {
		propability = 3;
	}
	else {
		propability = 5;
	}
	char flag;
	int random = rand() % propability;
	if (random == 0 || random == 1) {
		flag = cFlag;
	}
	else {
		flag = cStill;
	}
	return flag;
}

void populateForeground(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y]) {
	if (bigForrestPosY > 0) { 	// add moose + tracks	
		int iRand = rand() % 13;
		if (iRand == 0) {
			gameScreen[level->trackX - 3][bigForrestPosY + 4] = cMoose;
		}
		else {
			gameScreen[level->trackX - 3][bigForrestPosY + 4] = cEmpty;
		}
		int oddEven = (level->trackX - 1) % 2;
		gameScreen[level->trackX - 1][bigForrestPosY + 1 + oddEven] = cTrace;
		for (int i = level->trackX + 1; i < level->sizeX; i++) {
			oddEven = i % 2;
			gameScreen[i][bigForrestPosY + 1 + oddEven] = cTrace;
		}
	}
	// ADS
	populateAds(level, gameScreen);
}

void populateAds(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y]) {
	levelEntity game = *level;
	char ad1[] = "_DalaiL_";
	char ad2[] = "_PRODUCTIONS_";
	char ad1b[] = "_NO_ADS_";
	char ad2b[] = "___AD_FREE___";

	int adStartPos1 = 60;
	int adLength1 = strlen(ad1);
	int adStartPos2 = adStartPos1 + adLength1 + 8;
	int adLength2 = strlen(ad2);

	for (int i = adStartPos1; i < adStartPos2 + adLength2; i++) {
		if (i == adStartPos1 || i == adStartPos2) {
			gameScreen[game.trackX + 2][i - 1] = cSlash;
			gameScreen[game.trackX + 1][i] = cTop;
			gameScreen[game.trackX + 2][i] = cBottom;
		}
		else if (i == adStartPos1 + adLength1 - 1 || i == adStartPos2 + adLength2 - 1) {
			gameScreen[game.trackX + 1][i] = cTop;
			gameScreen[game.trackX + 2][i] = cBottom;
			gameScreen[game.trackX + 1][i + 1] = cTop;
			gameScreen[game.trackX + 2][i + 1] = cSlash;
			gameScreen[game.trackX + 2][i + 2] = cBackSlash;
		}
		else if (i < adStartPos1 + adLength1 || i > adStartPos2) {
			gameScreen[game.trackX + 1][i] = cTop;
			gameScreen[game.trackX + 2][i] = cBottom;
		}
	}
	if (game.player.posY > 20) {
		if ((game.player.posY / 10) % 2 == 0) {
			for (int i = 0; i < strlen(ad1); i++) {
				gameScreen[game.trackX + 2][adStartPos1 + i] = ad1[i];
			}
			for (int i = 0; i < strlen(ad2); i++) {
				gameScreen[game.trackX + 2][adStartPos2 + i] = ad2[i];
			}
		}
		else if ((game.player.posY / 10) % 2 == 1) {
			for (int i = 0; i < strlen(ad1b); i++) {
				gameScreen[game.trackX + 2][adStartPos1 + i] = ad1b[i];
			}
			for (int i = 0; i < strlen(ad2b); i++) {
				gameScreen[game.trackX + 2][adStartPos2 + i] = ad2b[i];
			}
		}
	}
}

