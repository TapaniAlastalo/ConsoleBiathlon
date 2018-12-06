#include "pch.h"
#include <iostream>
#include "header.h"
#include "TestHeader.h"

using namespace std;

int bigForrestPosY;
spaceForBackgroundItem spaceList[MAX_SHOOTINGS+1];

char getSpectator(levelEntity*);
char getFlag(levelEntity*);

int addTree(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);
int addHouses(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);
int addWarehouse(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);
int addForrest(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);
int addBigForrest(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);
int addSpectatorArea(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);
int addBigSpectatorArea(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y], int);

void generateSky(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y]);
void generateGround(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y]);
void populateForeground(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y]);
void populateAds(levelEntity*, char(&)[MAX_SIZE_X][MAX_SIZE_Y]);

void findSpaceForBackroundItems(levelEntity*);

/**
Locate the spaces between shooting points.
*/
void findSpaceForBackroundItems(levelEntity *level) {
	const int spaces = level->shootings + 1;
	spaceList[spaces] = {'\0'};
	int nextSpaceStart = 0;
	const int startX = 1;
	const int endX = level->trackX - 1;
	for (int i = 0; i < level->shootings; i++) {
		spaceForBackgroundItem space = { startX, 0, endX, 0};
		space.startY = nextSpaceStart;
		space.endY = level->shootingList[i].posY - 1;	// GIVE SPACE FOR TABLES
		space.sizeY = space.endY - space.startY;
		spaceList[i] = space;
		nextSpaceStart = level->shootingList[i].posY + 6;	// GIVE SPACE FOR TABLES
	}
	if (nextSpaceStart < level->sizeY - 1) {
		spaceForBackgroundItem space = { startX, nextSpaceStart, endX, level->sizeY - 1};
		spaceList[spaces -1] = space;
	}
}

void populateBackground(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y]) {
	generateSky(level, gameScreen); 
	generateGround(level, gameScreen);
	// check where is the space
	findSpaceForBackroundItems(level);
	const int noOfSpaces = level->shootings +1;
	// Populate buildings etc to empty spaces. 
	for (int i = 0; i < noOfSpaces; i++) { 
		if (i == 0) { // start area
			int posNext = spaceList[i].startY;
			int spaceLeft = spaceList[i].sizeY;
			if (spaceLeft > 20) {
				const int posThis = posNext;
				posNext = addSpectatorArea(level, gameScreen, posThis);
				spaceLeft -= (posNext - posThis);
			}
			if (spaceLeft > 6) {
				const int posThis = posNext;
				posNext = addHouses(level, gameScreen, posThis);
				spaceLeft -= (posNext - posThis);
			}
			if (spaceLeft > 6) {
				const int posThis = posNext;
				posNext = addWarehouse(level, gameScreen, posThis);
				spaceLeft -= (posNext - posThis);
			}
			if (spaceLeft > 7) {
				const int posThis = posNext;
				posNext = addForrest(level, gameScreen, posThis +1);
				spaceLeft -= (posNext - posThis);
			}
			if (spaceLeft > 2) {
				const int posThis = posNext;
				posNext = addTree(level, gameScreen, posThis + 1);
				spaceLeft -= (posNext - posThis);
			}
			if (spaceLeft > 2) {
				const int posThis = posNext;
				posNext = addTree(level, gameScreen, posThis + 1);
				spaceLeft -= (posNext - posThis);
			}
		} else if (i == noOfSpaces - 1) { // goal area
			int posPrev = spaceList[i].endY;
			int spaceLeft = spaceList[i].sizeY;
			bool first = true;
			if (spaceLeft > 16) {
				const int posThis = posPrev - 17;
				posPrev -= addBigSpectatorArea(level, gameScreen, posThis);
				spaceLeft -= (posThis - posPrev);
			}
			if (spaceLeft > 7) {
				const int posThis = posPrev - 8;
				posPrev -= addSpectatorArea(level, gameScreen, posThis);
				spaceLeft -= (posThis - posPrev);
			}
			if (spaceLeft > 4) {
				const int posThis = posPrev - 5;
				posPrev -= addTree(level, gameScreen, posThis);
				spaceLeft -= (posThis - posPrev);
			}
		}
		else if (i == noOfSpaces - 2) { // next to goal area
			int posPrev = spaceList[i].endY;
			int spaceLeft = spaceList[i].sizeY;
			bool first = true;
			if (spaceLeft > 17) {
				const int posThis = posPrev - 17;
				posPrev -= addBigSpectatorArea(level, gameScreen, posThis);
				spaceLeft -= (posThis - posPrev);
			}
			if (spaceLeft > 7) {
				const int posThis = posPrev - 8;
				posPrev -= addSpectatorArea(level, gameScreen, posThis);
				spaceLeft -= (posThis - posPrev);
			}
			if (spaceLeft > 4) {
				const int posThis = posPrev - 4;
				posPrev -= addTree(level, gameScreen, posThis);
				spaceLeft -= (posThis - posPrev);
			}
			if (spaceLeft > 4) {
				const int posThis = posPrev - 4;
				posPrev -= addTree(level, gameScreen, posThis);
				spaceLeft -= (posThis - posPrev);
			}
		}
		else { // Here and there
			int posNext = spaceList[i].startY +1;
			int spaceLeft = spaceList[i].sizeY -1;
			if (spaceLeft > 12) {
				const int posThis = posNext;
				if (bigForrestPosY == -1) {	// if big forrest is not set yet..
					posNext = addBigForrest(level, gameScreen, posThis);
				}
				else {
					posNext = addSpectatorArea(level, gameScreen, posThis);
				}
				spaceLeft -= (posNext - i);
			}
			if (spaceLeft > 7) {
				const int posThis = posNext;
				posNext = addForrest(level, gameScreen, posThis + 1);
				spaceLeft -= (posNext - i);
			}
			if (spaceLeft > 2) {
				const int posThis = posNext;
				posNext = addTree(level, gameScreen, posThis + 1);
				spaceLeft -= (posNext - posThis);
			}
			if (spaceLeft > 2) {
				const int posThis = posNext;
				posNext = addTree(level, gameScreen, posThis + 1);
				spaceLeft -= (posNext - posThis);
			}
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

// return where is next free slot
int addTree(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
	gameScreen[level->trackX - 1][posY] = cSlash;
	gameScreen[level->trackX - 2][posY] = cSlash;
	gameScreen[level->trackX - 1][posY+1] = cBackSlash;
	gameScreen[level->trackX - 2][posY+1] = cBackSlash;
	return posY + 2;		
}
// return where is next free slot
int addHouses(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
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
	return posY + 6;
}
// return where is next free slot
int addWarehouse(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
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
	return posY + 6;
}
// return where is next free slot
int addForrest(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
	int iRand = 0; // NOT NECESSARY AT THE MOMENT 2 * (rand() % 2);		// randomise wich way the forrest will be planted
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
	return posY + 6;
}
// return where is next free slot
int addBigForrest(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
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
	return posY + 12;
}
// return where is next free slot
int addSpectatorArea(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
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
	return posY + 9;
}
// return where is next free slot
int addBigSpectatorArea(levelEntity *level, char(&gameScreen)[MAX_SIZE_X][MAX_SIZE_Y], int posY) {
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
	return posY + 18;
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
	if (bigForrestPosY > 0) { 	// If big forrest added add moose + tracks	
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

