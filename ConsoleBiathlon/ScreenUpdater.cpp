#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

/*const int maxShootings = 4;
int shootings;
const int sizeX = 10;
const int sizeY = 100;
const int trackX = 6;			// Track level on screen
int playerX = trackX;
int playerY = 1;


char gameScreen[10][100];

const char cHipHit = 'B';
const char cHit = 'O';
const char cMiss = 'X';

const char cReady = 'H';
const char cSki = 'X';
const char cDown = '<';
const char cLay = '_';
const char cStand = 'A';
const char cAim = 'T';
const char cWinner = 'Y';
const char cEmpty = ' ';
char cPlayer = cReady;

bool shootFromHipAllowed = true;
bool finished = false;

struct entity {
	char character;
	int posX;
	int posY;
};

struct shootingEntity {
	char character;
	char char1;
	char char2;
	char char3;
	int posX;
	int posY;
	int shootingTableX;
	int shootingTableY;
};

shootingEntity shootingList[maxShootings];
*/
void populateScreen();
void populateSky();
void populateTrack();
void populateGround();
void populateForeground();
void populateBackground();
void populateAds();
void populateShootingPositions();
void populatePlayer();
void printScreen();

void updateScreen() {
	populateScreen();
	printScreen();
}

void populateScreen() {
	populateSky();
	populateTrack();
	populateGround();
	populateShootingPositions();
	populatePlayer();
}

void populateSky() {
	char cEmpty = ' ';
	char cStar = '*';
	char cMoonDark = 'C';
	char cMoonHalf = 'D';
	char CMoonFull = 'O';
	for (int i = 0; i < trackX - 1; i++)			// Käydään pelikenttä läpi ja lisätään "." jokaiseen 'peliruutuun'
	{
		for (int j = 0; j < sizeY; j++)
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
	populateBackground();
}

char getSpectator();
char getFlag();

void populateBackground() {
	char cPole = '|';
	char cSlash = '/';
	char cBackSlash = '\\';
	char cRoof = '_';
	// populate poles and roofs
	for (int i = 0; i < sizeY; i++) {
		if (i == 1) {
			gameScreen[trackX - 1][i] = cPole;
		}
		else if (i == 3 || i == 6) {
			gameScreen[trackX - 1][i] = cPole;
			gameScreen[trackX - 2][i] = cPole;
		}
		else if (i == 2) {
			gameScreen[trackX - 3][i] = cRoof;
		}
		else if (i == 4) {
			gameScreen[trackX - 4][i] = cRoof;
		}
		else if (i == 5) {
			gameScreen[trackX - 4][i] = cRoof;
		}
	}
	// populate slashes
	for (int i = 0; i < sizeY; i++) {
		if (i == 1) { // buildings
			gameScreen[trackX - 2][i] = cSlash;
		}
		else if (i == 3) {
			gameScreen[trackX - 2][i] = cBackSlash;
			gameScreen[trackX - 3][i] = cSlash;
		}
		else if (i == 6) {
			gameScreen[trackX - 3][i] = cBackSlash;
		}
		else if (i == 12) { // forest
			gameScreen[trackX - 1][i] = cSlash;
			gameScreen[trackX - 2][i] = cSlash;
		}
		else if (i == 13) {
			gameScreen[trackX - 1][i] = cBackSlash;
			gameScreen[trackX - 2][i] = cBackSlash;
		}
		else if (i == 25) { // forest
			gameScreen[trackX - 1][i] = cSlash;
			gameScreen[trackX - 2][i] = cSlash;
		}
		else if (i == 26) {
			gameScreen[trackX - 1][i] = cBackSlash;
			gameScreen[trackX - 2][i] = cBackSlash;
		}
		else if (i == 27) {
			gameScreen[trackX - 2][i] = cSlash;
			gameScreen[trackX - 3][i] = cSlash;
		}
		else if (i == 28) {
			gameScreen[trackX - 2][i] = cBackSlash;
			gameScreen[trackX - 3][i] = cBackSlash;
		}
		else if (i == 29) {
			gameScreen[trackX - 1][i] = cSlash;
			gameScreen[trackX - 2][i] = cSlash;
		}
		else if (i == 30) {
			gameScreen[trackX - 1][i] = cBackSlash;
			gameScreen[trackX - 2][i] = cBackSlash;
		}
		else if (i == 31) {
			gameScreen[trackX - 2][i] = cSlash;
			gameScreen[trackX - 3][i] = cSlash;
		}
		else if (i == 32) {
			gameScreen[trackX - 2][i] = cBackSlash;
			gameScreen[trackX - 3][i] = cBackSlash;
		}
		else if (i == 33) {
			gameScreen[trackX - 1][i] = cSlash;
			gameScreen[trackX - 2][i] = cSlash;
		}
		else if (i == 34) {
			gameScreen[trackX - 1][i] = cBackSlash;
			gameScreen[trackX - 2][i] = cBackSlash;
		}
		else if (i == 35) {
			gameScreen[trackX - 2][i] = cSlash;
			gameScreen[trackX - 3][i] = cSlash;
		}
		else if (i == 36) {
			gameScreen[trackX - 2][i] = cBackSlash;
			gameScreen[trackX - 3][i] = cBackSlash;
		} // spectator areas
		else if (i == 67 || i == 75) {
			gameScreen[trackX - 1][i] = cSlash;
			gameScreen[trackX - 2][i + 1] = cSlash;
		}
		else if (i == 74 || i == 82) {
			gameScreen[trackX - 1][i] = cSlash;
			gameScreen[trackX - 2][i + 1] = cSlash;
			gameScreen[trackX - 3][i - 1] = cRoof;
			gameScreen[trackX - 3][i] = cRoof;
			gameScreen[trackX - 3][i + 1] = cRoof;
		}
		else if ((i > 68 && i < 74) || (i > 76 && i < 82)) {
			gameScreen[trackX - 3][i] = cRoof;
		}
		else if (i == 91) {
			gameScreen[trackX - 1][i] = cSlash;
			gameScreen[trackX - 2][i + 1] = cSlash;
		}
		else if (i == 98) {
			gameScreen[trackX - 1][i] = cSlash;
			gameScreen[trackX - 2][i + 1] = cSlash;
			gameScreen[trackX - 3][i - 1] = cRoof;
			gameScreen[trackX - 3][i] = cRoof;
			gameScreen[trackX - 3][i + 1] = cRoof;
		}
		else if (i > 92 && i < 98) {
			gameScreen[trackX - 3][i] = cRoof;
		}
	}

	// prepare spectators and flags
	for (int i = 0; i < sizeY; i++) {
		if (i == 74 || i == 82) {
			gameScreen[trackX - 3][i] = getFlag();
			gameScreen[trackX - 2][i] = getSpectator();
			gameScreen[trackX - 1][i - 1] = getSpectator();
		}
		else if ((i > 68 && i < 74) || (i > 76 && i < 82)) {
			if (i % 2 == 0) {
				gameScreen[trackX - 3][i] = getFlag();
			}
			gameScreen[trackX - 2][i] = getSpectator();
			gameScreen[trackX - 1][i - 1] = getSpectator();
		}
		else if (i == 98) {
			gameScreen[trackX - 3][i] = getFlag();
			gameScreen[trackX - 2][i] = getSpectator();
			gameScreen[trackX - 1][i - 1] = getSpectator();
		}
		else if (i > 92 && i < 98) {
			if (i % 2 == 0) {
				gameScreen[trackX - 3][i] = getFlag();
			}
			gameScreen[trackX - 2][i] = getSpectator();
			gameScreen[trackX - 1][i - 1] = getSpectator();
		}
	}

}

const char cSpectate = 'o';
const char cCheer = 'Y';
const char cFlag = 'P';
const char cStill = '|';

/*
Get Specator either sitting or cheering
*/
char getSpectator() {
	int propability;
	if (finished) {
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
char getFlag() {
	int propability = 3;
	if (finished) {
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

void populateGround() {
	char cGround = '.';
	for (int i = trackX + 1; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++)
		{
			if ((i + j) % 3 == 0) {
				gameScreen[i][j] = cGround;
			}
			//else { gameScreen[i][j] = cEmpty;	}
		}
	}
	populateForeground();
}

void populateForeground() {
	// moose + tracks
	char cTrace = 'u';
	char cMoose = 'w';
	int iRand = rand() % 13;
	if (iRand == 0) {
		gameScreen[trackX - 3][29] = cMoose;
	}
	else {
		gameScreen[trackX - 3][29] = cEmpty;
	}
	int oddEven = (trackX - 1) % 2;
	gameScreen[trackX - 1][26 + oddEven] = cTrace;
	for (int i = trackX + 1; i < sizeX; i++) {
		oddEven = i % 2;
		gameScreen[i][26 + oddEven] = cTrace;
	}
	// ADS
	populateAds();
}

void populateAds(void) {
	char cSlash = '/';
	char cBackSlash = '\\';
	char cTop = '_';
	char cBottom = '_';

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
			gameScreen[trackX + 2][i - 1] = cSlash;
			gameScreen[trackX + 1][i] = cTop;
			gameScreen[trackX + 2][i] = cBottom;
		}
		else if (i == adStartPos1 + adLength1 - 1 || i == adStartPos2 + adLength2 - 1) {
			gameScreen[trackX + 1][i] = cTop;
			gameScreen[trackX + 2][i] = cBottom;
			gameScreen[trackX + 1][i + 1] = cTop;
			gameScreen[trackX + 2][i + 1] = cSlash;
			gameScreen[trackX + 2][i + 2] = cBackSlash;
		}
		else if (i < adStartPos1 + adLength1 || i > adStartPos2) {
			gameScreen[trackX + 1][i] = cTop;
			gameScreen[trackX + 2][i] = cBottom;
		}
	}
	if (playerY > 20) {
		if ((playerY / 10) % 2 == 0) {
			for (int i = 0; i < strlen(ad1); i++) {
				gameScreen[trackX + 2][adStartPos1 + i] = ad1[i];
			}
			for (int i = 0; i < strlen(ad2); i++) {
				gameScreen[trackX + 2][adStartPos2 + i] = ad2[i];
			}
		}
		else if ((playerY / 10) % 2 == 1) {
			for (int i = 0; i < strlen(ad1b); i++) {
				gameScreen[trackX + 2][adStartPos1 + i] = ad1b[i];
			}
			for (int i = 0; i < strlen(ad2b); i++) {
				gameScreen[trackX + 2][adStartPos2 + i] = ad2b[i];
			}
		}
	}
}

void populateShootingPositions() {
	const char cTableStart = '[';
	const char cTableEnd = ']';
	const char cTablePillar = '|';
	// populate shooting positions
	for (int i = 0; i < shootings; i++) {
		shootingEntity shooting = shootingList[i];
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
		if (playerY == shooting.posY && cPlayer == shooting.character) {
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

void populateTrack() {
	const char cTrack = '=';
	const char cGoal = 'M';
	const char cFinished = 'F';
	const char cEmpty = ' ';

	for (int i = 0; i < sizeY; i++) {
		switch (i) {
		case 0:
			gameScreen[trackX][i] = cEmpty;
			break;
		case 1:
			gameScreen[trackX][i] = cFinished;
			break;
		case sizeY - 2:
			if (finished) {
				gameScreen[trackX][i] = cFinished;
			}
			else {
				gameScreen[trackX][i] = cGoal;
			}
			break;
		case sizeY - 1:
			gameScreen[trackX][i] = cEmpty;
			break;
		default:
			gameScreen[trackX][i] = cTrack;
		}
	}
}

void populatePlayer() {
	gameScreen[playerX][playerY] = cPlayer; // Add player icon
}

void printScreen() {
	system("CLS");
	cout << "_______________________________ CONSOLE BIATHLON SIMULATOR ________________________________" << endl;
	for (int i = 0; i < sizeX; ++i)
	{
		for (int j = 0; j < sizeY; ++j)
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