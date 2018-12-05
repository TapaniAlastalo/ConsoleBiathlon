#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "header.h"
using namespace std;

void populateScreen(levelEntity);
void populateSky(levelEntity);
void populateTrack(levelEntity);
void populateGround(levelEntity);
void populateForeground(levelEntity);
void populateBackground(levelEntity);
void populateAds(levelEntity);
void populateShootingPositions(levelEntity);
void populatePlayer(levelEntity);
void printScreen(levelEntity);

void updateScreen(levelEntity game) {
	populateScreen(game);
	printScreen(game);
}

void populateScreen(levelEntity game) {
	populateSky(game);
	populateTrack(game);
	populateGround(game);
	populateShootingPositions(game);
	populatePlayer(game);
}

void populateSky(levelEntity game) {
	for (int i = 0; i < game.trackX - 1; i++)			// Käydään pelikenttä läpi ja lisätään "." jokaiseen 'peliruutuun'
	{
		for (int j = 0; j < game.sizeY; j++)
		{
			if (j != 0) {
				if (i == 0 && j % 29 == 0) {		// rand() % 7
					game.screen[i][j] = cStar;
				}
				else	if (i == 1 && j % 7 == 0) {		// rand() % 7
					game.screen[i][j] = cStar;
				}
				else if (i == 2 && j % 13 == 0) {		// rand() % 7
					game.screen[i][j] = cStar;
				}
				else if (i == 3 && j % 37 == 0) {		// rand() % 7
					game.screen[i][j] = cStar;
				}
				else {
					//gameScreen[i][j] = cEmpty;
				}
			}
		}
	}
	game.screen[1][2] = cMoonDark;
	game.screen[1][3] = cMoonHalf;
	populateBackground(game);
}

char getSpectator(levelEntity);
char getFlag(levelEntity);

void populateBackground(levelEntity game) {
	// populate poles and roofs
	for (int i = 0; i < game.sizeY; i++) {
		if (i == 1) {
			game.screen[game.trackX - 1][i] = cPole;
		}
		else if (i == 3 || i == 6) {
			game.screen[game.trackX - 1][i] = cPole;
			game.screen[game.trackX - 2][i] = cPole;
		}
		else if (i == 2) {
			game.screen[game.trackX - 3][i] = cTop;
		}
		else if (i == 4) {
			game.screen[game.trackX - 4][i] = cTop;
		}
		else if (i == 5) {
			game.screen[game.trackX - 4][i] = cTop;
		}
	}
	// populate slashes
	for (int i = 0; i < game.sizeY; i++) {
		if (i == 1) { // buildings
			game.screen[game.trackX - 2][i] = cSlash;
		}
		else if (i == 3) {
			game.screen[game.trackX - 2][i] = cBackSlash;
			game.screen[game.trackX - 3][i] = cSlash;
		}
		else if (i == 6) {
			game.screen[game.trackX - 3][i] = cBackSlash;
		}
		else if (i == 12) { // forest
			game.screen[game.trackX - 1][i] = cSlash;
			game.screen[game.trackX - 2][i] = cSlash;
		}
		else if (i == 13) {
			game.screen[game.trackX - 1][i] = cBackSlash;
			game.screen[game.trackX - 2][i] = cBackSlash;
		}
		else if (i == 25) { // forest
			game.screen[game.trackX - 1][i] = cSlash;
			game.screen[game.trackX - 2][i] = cSlash;
		}
		else if (i == 26) {
			game.screen[game.trackX - 1][i] = cBackSlash;
			game.screen[game.trackX - 2][i] = cBackSlash;
		}
		else if (i == 27) {
			game.screen[game.trackX - 2][i] = cSlash;
			game.screen[game.trackX - 3][i] = cSlash;
		}
		else if (i == 28) {
			game.screen[game.trackX - 2][i] = cBackSlash;
			game.screen[game.trackX - 3][i] = cBackSlash;
		}
		else if (i == 29) {
			game.screen[game.trackX - 1][i] = cSlash;
			game.screen[game.trackX - 2][i] = cSlash;
		}
		else if (i == 30) {
			game.screen[game.trackX - 1][i] = cBackSlash;
			game.screen[game.trackX - 2][i] = cBackSlash;
		}
		else if (i == 31) {
			game.screen[game.trackX - 2][i] = cSlash;
			game.screen[game.trackX - 3][i] = cSlash;
		}
		else if (i == 32) {
			game.screen[game.trackX - 2][i] = cBackSlash;
			game.screen[game.trackX - 3][i] = cBackSlash;
		}
		else if (i == 33) {
			game.screen[game.trackX - 1][i] = cSlash;
			game.screen[game.trackX - 2][i] = cSlash;
		}
		else if (i == 34) {
			game.screen[game.trackX - 1][i] = cBackSlash;
			game.screen[game.trackX - 2][i] = cBackSlash;
		}
		else if (i == 35) {
			game.screen[game.trackX - 2][i] = cSlash;
			game.screen[game.trackX - 3][i] = cSlash;
		}
		else if (i == 36) {
			game.screen[game.trackX - 2][i] = cBackSlash;
			game.screen[game.trackX - 3][i] = cBackSlash;
		} // spectator areas
		else if (i == 67 || i == 75) {
			game.screen[game.trackX - 1][i] = cSlash;
			game.screen[game.trackX - 2][i + 1] = cSlash;
		}
		else if (i == 74 || i == 82) {
			game.screen[game.trackX - 1][i] = cSlash;
			game.screen[game.trackX - 2][i + 1] = cSlash;
			game.screen[game.trackX - 3][i - 1] = cTop;
			game.screen[game.trackX - 3][i] = cTop;
			game.screen[game.trackX - 3][i + 1] = cTop;
		}
		else if ((i > 68 && i < 74) || (i > 76 && i < 82)) {
			game.screen[game.trackX - 3][i] = cTop;
		}
		else if (i == 91) {
			game.screen[game.trackX - 1][i] = cSlash;
			game.screen[game.trackX - 2][i + 1] = cSlash;
		}
		else if (i == 98) {
			game.screen[game.trackX - 1][i] = cSlash;
			game.screen[game.trackX - 2][i + 1] = cSlash;
			game.screen[game.trackX - 3][i - 1] = cTop;
			game.screen[game.trackX - 3][i] = cTop;
			game.screen[game.trackX - 3][i + 1] = cTop;
		}
		else if (i > 92 && i < 98) {
			game.screen[game.trackX - 3][i] = cTop;
		}
	}

	// prepare spectators and flags
	for (int i = 0; i < game.sizeY; i++) {
		if (i == 74 || i == 82) {
			game.screen[game.trackX - 3][i] = getFlag(game);
			game.screen[game.trackX - 2][i] = getSpectator(game);
			game.screen[game.trackX - 1][i - 1] = getSpectator(game);
		}
		else if ((i > 68 && i < 74) || (i > 76 && i < 82)) {
			if (i % 2 == 0) {
				game.screen[game.trackX - 3][i] = getFlag(game);
			}
			game.screen[game.trackX - 2][i] = getSpectator(game);
			game.screen[game.trackX - 1][i - 1] = getSpectator(game);
		}
		else if (i == 98) {
			game.screen[game.trackX - 3][i] = getFlag(game);
			game.screen[game.trackX - 2][i] = getSpectator(game);
			game.screen[game.trackX - 1][i - 1] = getSpectator(game);
		}
		else if (i > 92 && i < 98) {
			if (i % 2 == 0) {
				game.screen[game.trackX - 3][i] = getFlag(game);
			}
			game.screen[game.trackX - 2][i] = getSpectator(game);
			game.screen[game.trackX - 1][i - 1] = getSpectator(game);
		}
	}

}

/*
Get Specator either sitting or cheering
*/
char getSpectator(levelEntity game) {
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
char getFlag(levelEntity game) {
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

void populateGround(levelEntity game) {
	char cGround = '.';
	for (int i = game.trackX + 1; i < game.sizeX; i++) {
		for (int j = 0; j < game.sizeY; j++)
		{
			if ((i + j) % 3 == 0) {
				game.screen[i][j] = cGround;
			}
			//else { gameScreen[i][j] = cEmpty;	}
		}
	}
	populateForeground(game);
}

void populateForeground(levelEntity game) {
	// moose + tracks
	int iRand = rand() % 13;
	if (iRand == 0) {
		game.screen[game.trackX - 3][29] = cMoose;
	}
	else {
		game.screen[game.trackX - 3][29] = cEmpty;
	}
	int oddEven = (game.trackX - 1) % 2;
	game.screen[game.trackX - 1][26 + oddEven] = cTrace;
	for (int i = game.trackX + 1; i < game.sizeX; i++) {
		oddEven = i % 2;
		game.screen[i][26 + oddEven] = cTrace;
	}
	// ADS
	populateAds(game);
}

void populateAds(levelEntity game) {
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
			game.screen[game.trackX + 2][i - 1] = cSlash;
			game.screen[game.trackX + 1][i] = cTop;
			game.screen[game.trackX + 2][i] = cBottom;
		}
		else if (i == adStartPos1 + adLength1 - 1 || i == adStartPos2 + adLength2 - 1) {
			game.screen[game.trackX + 1][i] = cTop;
			game.screen[game.trackX + 2][i] = cBottom;
			game.screen[game.trackX + 1][i + 1] = cTop;
			game.screen[game.trackX + 2][i + 1] = cSlash;
			game.screen[game.trackX + 2][i + 2] = cBackSlash;
		}
		else if (i < adStartPos1 + adLength1 || i > adStartPos2) {
			game.screen[game.trackX + 1][i] = cTop;
			game.screen[game.trackX + 2][i] = cBottom;
		}
	}
	if (game.player.posY > 20) {
		if ((game.player.posY / 10) % 2 == 0) {
			for (int i = 0; i < strlen(ad1); i++) {
				game.screen[game.trackX + 2][adStartPos1 + i] = ad1[i];
			}
			for (int i = 0; i < strlen(ad2); i++) {
				game.screen[game.trackX + 2][adStartPos2 + i] = ad2[i];
			}
		}
		else if ((game.player.posY / 10) % 2 == 1) {
			for (int i = 0; i < strlen(ad1b); i++) {
				game.screen[game.trackX + 2][adStartPos1 + i] = ad1b[i];
			}
			for (int i = 0; i < strlen(ad2b); i++) {
				game.screen[game.trackX + 2][adStartPos2 + i] = ad2b[i];
			}
		}
	}
}

void populateShootingPositions(levelEntity game) {
	const char cTableStart = '[';
	const char cTableEnd = ']';
	const char cTablePillar = '|';
	// populate shooting positions
	for (int i = 0; i < game.shootings; i++) {
		shootingEntity shooting = game.shootingList[i];
		game.screen[shooting.posX][shooting.posY] = shooting.character;
		// populate shooting table
		game.screen[shooting.shootingTableX][shooting.shootingTableY] = cTableStart;
		game.screen[shooting.shootingTableX][shooting.shootingTableY + 4] = cTableEnd;
		// if shooting standing add table pillars
		if (shooting.character == cAim) {
			game.screen[shooting.shootingTableX + 1][shooting.shootingTableY + 1] = cTablePillar;
			game.screen[shooting.shootingTableX + 1][shooting.shootingTableY + 3] = cTablePillar;
		}
		// if at shooting position show tables
		if (game.player.posY == shooting.posY && game.player.character == shooting.character) {
			game.screen[shooting.shootingTableX][shooting.shootingTableY + 1] = shooting.char1;
			game.screen[shooting.shootingTableX][shooting.shootingTableY + 2] = shooting.char2;
			game.screen[shooting.shootingTableX][shooting.shootingTableY + 3] = shooting.char3;
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

void populateTrack(levelEntity game) {
	for (int i = 0; i < game.sizeY; i++) {
		switch (i) {
		case 0:
			game.screen[game.trackX][i] = cEmpty;
			break;
		case 1:
			game.screen[game.trackX][i] = cFinished;
			break;
		default:
			if (i == game.sizeY - 2) {
				if (game.finished) {
					game.screen[game.trackX][i] = cFinished;
				}
				else {
					game.screen[game.trackX][i] = cGoal;
				}
			}
			else if ((game.sizeY - 1)) {
				game.screen[game.trackX][i] = cEmpty;
			}
			else {
				game.screen[game.trackX][i] = cTrack;
			}
		}
	}
}

void populatePlayer(levelEntity game) {
	game.screen[game.player.posX][game.player.posY] = game.player.character; // Add player icon
}

void printScreen(levelEntity game) {
	system("CLS");
	cout << "_______________________________ CONSOLE BIATHLON SIMULATOR ________________________________" << endl;
	for (int i = 0; i < game.sizeX; ++i)
	{
		for (int j = 0; j < game.sizeY; ++j)
		{
			cout << game.screen[i][j];
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