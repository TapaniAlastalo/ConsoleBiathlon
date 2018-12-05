#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "header.h"
#include "TestHeader.h"

using namespace std;

void populateScreen(levelEntity*);
void populateSky(levelEntity*);
void populateTrack(levelEntity*);
void populateGround(levelEntity*);
void populateForeground(levelEntity*);
void populateBackground(levelEntity*);
void populateAds(levelEntity*);
void populateShootingPositions(levelEntity*);
void populatePlayer(levelEntity*);
void printScreen(levelEntity*);

char getSpectator(levelEntity*);
char getFlag(levelEntity*);

char gameScreen[MAX_SIZE_X][MAX_SIZE_Y];

void updateScreen(levelEntity *game) {
	populateScreen(game);
	printScreen(game);
}

void populateScreen(levelEntity *game) {
	populateSky(game);
	populateTrack(game);
	populateGround(game);
	populateShootingPositions(game);
	populatePlayer(game);
}

void populateSky(levelEntity *level) {
	levelEntity game = *level;
	for (int i = 0; i < game.trackX - 1; i++)			// Käydään pelikenttä läpi ja lisätään "." jokaiseen 'peliruutuun'
	{
		for (int j = 0; j < game.sizeY; j++)
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
	populateBackground(level);
}

void populateBackground(levelEntity *level) {
	levelEntity game = *level;
	// populate poles and roofs
	for (int i = 0; i < game.sizeY; i++) {
		if (i == 1) {
			gameScreen[game.trackX - 1][i] = cPole;
		}
		else if (i == 3 || i == 6) {
			gameScreen[game.trackX - 1][i] = cPole;
			gameScreen[game.trackX - 2][i] = cPole;
		}
		else if (i == 2) {
			gameScreen[game.trackX - 3][i] = cTop;
		}
		else if (i == 4) {
			gameScreen[game.trackX - 4][i] = cTop;
		}
		else if (i == 5) {
			gameScreen[game.trackX - 4][i] = cTop;
		}
	}
	// populate slashes
	for (int i = 0; i < game.sizeY; i++) {
		if (i == 1) { // buildings
			gameScreen[game.trackX - 2][i] = cSlash;
		}
		else if (i == 3) {
			gameScreen[game.trackX - 2][i] = cBackSlash;
			gameScreen[game.trackX - 3][i] = cSlash;
		}
		else if (i == 6) {
			gameScreen[game.trackX - 3][i] = cBackSlash;
		}
		else if (i == 12) { // forest
			gameScreen[game.trackX - 1][i] = cSlash;
			gameScreen[game.trackX - 2][i] = cSlash;
		}
		else if (i == 13) {
			gameScreen[game.trackX - 1][i] = cBackSlash;
			gameScreen[game.trackX - 2][i] = cBackSlash;
		}
		else if (i == 25) { // forest
			gameScreen[game.trackX - 1][i] = cSlash;
			gameScreen[game.trackX - 2][i] = cSlash;
		}
		else if (i == 26) {
			gameScreen[game.trackX - 1][i] = cBackSlash;
			gameScreen[game.trackX - 2][i] = cBackSlash;
		}
		else if (i == 27) {
			gameScreen[game.trackX - 2][i] = cSlash;
			gameScreen[game.trackX - 3][i] = cSlash;
		}
		else if (i == 28) {
			gameScreen[game.trackX - 2][i] = cBackSlash;
			gameScreen[game.trackX - 3][i] = cBackSlash;
		}
		else if (i == 29) {
			gameScreen[game.trackX - 1][i] = cSlash;
			gameScreen[game.trackX - 2][i] = cSlash;
		}
		else if (i == 30) {
			gameScreen[game.trackX - 1][i] = cBackSlash;
			gameScreen[game.trackX - 2][i] = cBackSlash;
		}
		else if (i == 31) {
			gameScreen[game.trackX - 2][i] = cSlash;
			gameScreen[game.trackX - 3][i] = cSlash;
		}
		else if (i == 32) {
			gameScreen[game.trackX - 2][i] = cBackSlash;
			gameScreen[game.trackX - 3][i] = cBackSlash;
		}
		else if (i == 33) {
			gameScreen[game.trackX - 1][i] = cSlash;
			gameScreen[game.trackX - 2][i] = cSlash;
		}
		else if (i == 34) {
			gameScreen[game.trackX - 1][i] = cBackSlash;
			gameScreen[game.trackX - 2][i] = cBackSlash;
		}
		else if (i == 35) {
			gameScreen[game.trackX - 2][i] = cSlash;
			gameScreen[game.trackX - 3][i] = cSlash;
		}
		else if (i == 36) {
			gameScreen[game.trackX - 2][i] = cBackSlash;
			gameScreen[game.trackX - 3][i] = cBackSlash;
		} // spectator areas
		else if (i == 67 || i == 75) {
			gameScreen[game.trackX - 1][i] = cSlash;
			gameScreen[game.trackX - 2][i + 1] = cSlash;
		}
		else if (i == 74 || i == 82) {
			gameScreen[game.trackX - 1][i] = cSlash;
			gameScreen[game.trackX - 2][i + 1] = cSlash;
			gameScreen[game.trackX - 3][i - 1] = cTop;
			gameScreen[game.trackX - 3][i] = cTop;
			gameScreen[game.trackX - 3][i + 1] = cTop;
		}
		else if ((i > 68 && i < 74) || (i > 76 && i < 82)) {
			gameScreen[game.trackX - 3][i] = cTop;
		}
		else if (i == 91) {
			gameScreen[game.trackX - 1][i] = cSlash;
			gameScreen[game.trackX - 2][i + 1] = cSlash;
		}
		else if (i == 98) {
			gameScreen[game.trackX - 1][i] = cSlash;
			gameScreen[game.trackX - 2][i + 1] = cSlash;
			gameScreen[game.trackX - 3][i - 1] = cTop;
			gameScreen[game.trackX - 3][i] = cTop;
			gameScreen[game.trackX - 3][i + 1] = cTop;
		}
		else if (i > 92 && i < 98) {
			gameScreen[game.trackX - 3][i] = cTop;
		}
	}

	// prepare spectators and flags
	for (int i = 0; i < game.sizeY; i++) {
		if (i == 74 || i == 82) {
			gameScreen[game.trackX - 3][i] = getFlag(&game);
			gameScreen[game.trackX - 2][i] = getSpectator(&game);
			gameScreen[game.trackX - 1][i - 1] = getSpectator(&game);
		}
		else if ((i > 68 && i < 74) || (i > 76 && i < 82)) {
			if (i % 2 == 0) {
				gameScreen[game.trackX - 3][i] = getFlag(&game);
			}
			gameScreen[game.trackX - 2][i] = getSpectator(&game);
			gameScreen[game.trackX - 1][i - 1] = getSpectator(&game);
		}
		else if (i == 98) {
			gameScreen[game.trackX - 3][i] = getFlag(&game);
			gameScreen[game.trackX - 2][i] = getSpectator(&game);
			gameScreen[game.trackX - 1][i - 1] = getSpectator(&game);
		}
		else if (i > 92 && i < 98) {
			if (i % 2 == 0) {
				gameScreen[game.trackX - 3][i] = getFlag(&game);
			}
			gameScreen[game.trackX - 2][i] = getSpectator(&game);
			gameScreen[game.trackX - 1][i - 1] = getSpectator(&game);
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

void populateGround(levelEntity *level) {
	levelEntity game = *level;
	char cGround = '.';
	for (int i = game.trackX + 1; i < game.sizeX; i++) {
		for (int j = 0; j < game.sizeY; j++)
		{
			if ((i + j) % 3 == 0) {
				gameScreen[i][j] = cGround;
			}
			//else { gameScreen[i][j] = cEmpty;	}
		}
	}
	populateForeground(level);
}

void populateForeground(levelEntity *level) {
	levelEntity game = *level;
	// moose + tracks
	int iRand = rand() % 13;
	if (iRand == 0) {
		gameScreen[game.trackX - 3][29] = cMoose;
	}
	else {
		gameScreen[game.trackX - 3][29] = cEmpty;
	}
	int oddEven = (game.trackX - 1) % 2;
	gameScreen[game.trackX - 1][26 + oddEven] = cTrace;
	for (int i = game.trackX + 1; i < game.sizeX; i++) {
		oddEven = i % 2;
		gameScreen[i][26 + oddEven] = cTrace;
	}
	// ADS
	populateAds(level);
}

void populateAds(levelEntity *level) {
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
		/*else if (shooting.char1 == cHit || shooting.char1 == cMiss || shooting.char1 == cHipHit) {
			gameScreen[shooting.shootingTableY][shooting.shootingTableX + 1] = shooting.char1;
		} else if (shooting.char2 == cHit || shooting.char2 == cMiss || shooting.char2 == cHipHit) {
			gameScreen[shooting.shootingTableY][shooting.shootingTableX + 2] = shooting.char2;
		} else if (shooting.char3 == cHit || shooting.char3 == cMiss || shooting.char3 == cHipHit) {
			gameScreen[shooting.shootingTableY][shooting.shootingTableX + 3] = shooting.char3;
		}*/
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

/*
void catchScreen() {					// Keräämisruutu
	system("CLS");						// Tyhjennetään ruutu
	for (int i = 0; i < sizeY; ++i)
	{
		for (int j = 0; j < sizeX; ++j)
		{
			gameScreen[i][j] = '*';		// Väläytetään näyttöä, jossa koko pelikenttä täynnä "*" -merkkiä
		}
	}
	printScreen();
}

void gameOver()							// Jos pelaaja menettää kaikki elämäpisteet, printataan seuraavat asiat
{
	system("CLS");						// Tyhjennetään ruutu
	string offset = " ";
	while (!_kbhit()) { // Odotetaan käyttäjän inputtia
		Sleep(20);
		printSlow("GAME OVER   ---press any key---   ");
		offset += " ";
	}
	//newFloor();							// Uusi kenttä
}

void printSlow(string stringtoprint) { // Printtaa stringin kirjain kerrallaan
	for (int i = 0; i < stringtoprint.size(); i++) {
		cout << stringtoprint[i];
		Sleep(10);
	}
}*/