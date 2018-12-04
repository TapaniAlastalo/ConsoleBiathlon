#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

const int maxShootings = 4;
int shootings;
const int sizeY = 10;
const int sizeX = 100;
const int trackY = 6;			// Track level on screen
int playerX = 1;
int playerY = trackY;

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
	int shootingTableY;
	int shootingTableX;
};

shootingEntity shootingList[maxShootings];

void populateScreen();
void populateSky();
void populateTrack();
void populateGround();
void populateShootingPositions();
void populatePlayer();
void printScreen();
void createShootings();
bool tryToShoot(char cShot);
void playerMove(int deltaX, int deltaY);
void raise();
void lower();

int main()
{
	createShootings();
	populateScreen();
	printScreen();

	bool updateScreen = false;
	int input = 0;
	/*while (input != 27) {
		input = _getch();
		char c = input;
		cout << input << "-" << c << "; ";
	}*/
	while (input != 27 && !finished) {
		cout << endl;
		cout << "Move using the arrow keys (>>, up-up, down-down), Quit ESC " << endl;
		input = _getch();
		switch (input) {
		case 72:						// Up Arrow - H
			playerMove(0, 1);
			updateScreen = true;
			break;
		case 80:						// Down Arrow - P
			playerMove(0, -1);
			updateScreen = true;
			break;
		case 75:						// Left Arrow - K
			playerMove(-1, 0);
			updateScreen = true;
			break;
		case 77:						// Right Arrow - M
			playerMove(1, 0);
			updateScreen = true;
			break;
		case 0:
		case 224:		// do nothing
			updateScreen = false;
			break;
		default:
			updateScreen = tryToShoot(input);
			break;
		}
		if (updateScreen) {
			system("CLS"); // Clear console
			populateScreen();
			printScreen();
		}
	}
	if (finished) {
		cPlayer = cWinner;
	}
	system("CLS");
	populateScreen();
	printScreen();
}

void populateBackground();
void populateForeground();

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
	for (int i = 0; i < trackY-1; i++)			// Käydään pelikenttä läpi ja lisätään "." jokaiseen 'peliruutuun'
	{
		for (int j = 0; j < sizeX; j++)
		{
			if (j != 0) {
				if (i == 0 && j % 29 == 0) {		// rand() % 7
					gameScreen[i][j] = cStar;
				} else	if (i == 1 && j % 7 == 0) {		// rand() % 7
					gameScreen[i][j] = cStar;
				} else if (i == 2 && j % 13 == 0) {		// rand() % 7
					gameScreen[i][j] = cStar;
				} else if (i == 3 && j % 37 == 0) {		// rand() % 7
					gameScreen[i][j] = cStar;
				} else {
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
	for (int i = 0; i < sizeX; i++) {
		if (i == 1) {
			gameScreen[trackY - 1][i] = cPole;
		}
		else if (i == 3 || i == 6) {
			gameScreen[trackY - 1][i] = cPole;
			gameScreen[trackY - 2][i] = cPole;
		}
		else if (i == 2) {
			gameScreen[trackY - 3][i] = cRoof;
		}
		else if (i == 4) {
			gameScreen[trackY - 4][i] = cRoof;
		}
		else if (i == 5) {
			gameScreen[trackY - 4][i] = cRoof;
		}
	}
	// populate slashes
	for (int i = 0; i < sizeX; i++) {
		if (i == 1) { // buildings
			gameScreen[trackY - 2][i] = cSlash;
		} else if (i == 3) {
			gameScreen[trackY - 2][i] = cBackSlash;
			gameScreen[trackY - 3][i] = cSlash;
		} else if (i == 6) {
			gameScreen[trackY - 3][i] = cBackSlash;
		}
		else if (i == 12) { // forest
			gameScreen[trackY - 1][i] = cSlash;
			gameScreen[trackY - 2][i] = cSlash;
		}
		else if (i == 13) {
			gameScreen[trackY - 1][i] = cBackSlash;
			gameScreen[trackY - 2][i] = cBackSlash;
		}
		else if (i == 25) { // forest
			gameScreen[trackY - 1][i] = cSlash;
			gameScreen[trackY - 2][i] = cSlash;
		} else if (i == 26) {
			gameScreen[trackY - 1][i] = cBackSlash;
			gameScreen[trackY - 2][i] = cBackSlash;
		} else if (i == 27) { 
			gameScreen[trackY - 2][i] = cSlash;
			gameScreen[trackY - 3][i] = cSlash;
		} else if (i == 28) {
			gameScreen[trackY - 2][i] = cBackSlash;
			gameScreen[trackY - 3][i] = cBackSlash;
		} else if (i == 29) {
			gameScreen[trackY - 1][i] = cSlash;
			gameScreen[trackY - 2][i] = cSlash;
		} else if (i == 30) {
			gameScreen[trackY - 1][i] = cBackSlash;
			gameScreen[trackY - 2][i] = cBackSlash;
		} else if (i == 31) {
			gameScreen[trackY - 2][i] = cSlash;
			gameScreen[trackY - 3][i] = cSlash;
		} else if (i == 32) {
			gameScreen[trackY - 2][i] = cBackSlash;
			gameScreen[trackY - 3][i] = cBackSlash;
		} else if (i == 33) {
			gameScreen[trackY - 1][i] = cSlash;
			gameScreen[trackY - 2][i] = cSlash;
		} else if (i == 34) {
			gameScreen[trackY - 1][i] = cBackSlash;
			gameScreen[trackY - 2][i] = cBackSlash;
		} else if (i == 35) {
			gameScreen[trackY - 2][i] = cSlash;
			gameScreen[trackY - 3][i] = cSlash;
		} else if (i == 36) {
			gameScreen[trackY - 2][i] = cBackSlash;
			gameScreen[trackY - 3][i] = cBackSlash;
		} // spectator areas
		else if (i == 67 || i == 75) {
			gameScreen[trackY - 1][i] = cSlash;
			gameScreen[trackY - 2][i+1] = cSlash;
		}
		else if (i == 74 || i == 82) {
			gameScreen[trackY - 1][i] = cSlash;
			gameScreen[trackY - 2][i+1] = cSlash;
			gameScreen[trackY - 3][i - 1] = cRoof;
			gameScreen[trackY - 3][i] = cRoof;
			gameScreen[trackY - 3][i + 1] = cRoof;
		}
		else if ((i > 68 && i < 74) || (i > 76 && i < 82)) {
			gameScreen[trackY - 3][i] = cRoof;
		}
		else if (i == 91) {
			gameScreen[trackY - 1][i] = cSlash;
			gameScreen[trackY - 2][i+1] = cSlash;
		}
		else if (i == 98) {
			gameScreen[trackY - 1][i] = cSlash;
			gameScreen[trackY - 2][i+1] = cSlash;
			gameScreen[trackY - 3][i-1] = cRoof;
			gameScreen[trackY - 3][i] = cRoof;
			gameScreen[trackY - 3][i+1] = cRoof;
		}
		else if (i > 92 && i < 98) {
			gameScreen[trackY - 3][i] = cRoof;
		}
	}
	
	// prepare spectators and flags
	for (int i = 0; i < sizeX; i++) {
		if (i == 74 || i == 82) {
			gameScreen[trackY - 3][i] = getFlag();
			gameScreen[trackY - 2][i] = getSpectator();
			gameScreen[trackY - 1][i - 1] = getSpectator();
		}
		else if ((i > 68 && i < 74) || (i > 76 && i < 82)) {
			if (i % 2 == 0) {
				gameScreen[trackY - 3][i] = getFlag();
			}
			gameScreen[trackY - 2][i] = getSpectator();
			gameScreen[trackY - 1][i - 1] = getSpectator();
		}
		else if (i == 98) {
			gameScreen[trackY - 3][i] = getFlag();
			gameScreen[trackY - 2][i] = getSpectator();
			gameScreen[trackY - 1][i - 1] = getSpectator();
		}
		else if (i > 92 && i < 98) {
			if (i % 2 == 0) {
				gameScreen[trackY - 3][i] = getFlag();
			}
			gameScreen[trackY - 2][i] = getSpectator();
			gameScreen[trackY - 1][i - 1] = getSpectator();
		}
	}

}

const char cSpectate = 'o';
const char cCheer = 'Y';
const char cFlag = 'P';
const char cStill = '|';

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
	char cEmpty = ' ';
	for (int i = trackY+1; i < sizeY; i++)	{
		for (int j = 0; j < sizeX; j++)
		{
			if ((i + j) % 3 == 0) {
				gameScreen[i][j] = cGround;
			}
			else {
				//gameScreen[i][j] = cEmpty;
			}
		}
	}
	populateForeground();
}

void populateForeground() {
	char cTrace = 'u';
	char cMoose = 'w';
	int iRand = rand() % 13;
	if (iRand == 0) {
		gameScreen[trackY - 3][29] = cMoose;
	}
	else {
		gameScreen[trackY - 3][29] = cEmpty;
	}
	int oddEven = (trackY - 1) % 2;
	gameScreen[trackY -1][26 + oddEven] = cTrace;
	for (int i = trackY + 1; i < sizeY; i++) {
		oddEven = i % 2;
		gameScreen[i][26 + oddEven] = cTrace;
	}
}

void populateShootingPositions() {
	const char cTableStart = '[';
	const char cTableEnd = ']';
	const char cTablePillar = '|';
	// populate shooting positions
	for (int i = 0; i < shootings; i++) {
		shootingEntity shooting = shootingList[i];
		gameScreen[shooting.posY][shooting.posX] = shooting.character;
		// populate shooting table
		gameScreen[shooting.shootingTableY][shooting.shootingTableX] = cTableStart;
		gameScreen[shooting.shootingTableY][shooting.shootingTableX + 4] = cTableEnd;
		// if shooting standing add table pillars
		if (shooting.character == cAim) {
			gameScreen[shooting.shootingTableY + 1][shooting.shootingTableX + 1] = cTablePillar;
			gameScreen[shooting.shootingTableY + 1][shooting.shootingTableX + 3] = cTablePillar;
		}
		// if at shooting position show tables
		if (playerX == shooting.posX && cPlayer == shooting.character) {
			gameScreen[shooting.shootingTableY][shooting.shootingTableX + 1] = shooting.char1;
			gameScreen[shooting.shootingTableY][shooting.shootingTableX + 2] = shooting.char2;
			gameScreen[shooting.shootingTableY][shooting.shootingTableX + 3] = shooting.char3;
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

	for (int i = 0; i < sizeX; i++) {
		switch (i) {
		case 0:
			gameScreen[trackY][i] = cEmpty;
			break;
		case 1:
			gameScreen[trackY][i] = cFinished;
			break;
		case sizeX - 2:
			if (finished) {
				gameScreen[trackY][i] = cFinished;
			}
			else {
				gameScreen[trackY][i] = cGoal;
			}
			break;
		case sizeX -1:
			gameScreen[trackY][i] = cEmpty;
			break;
		default:
			gameScreen[trackY][i] = cTrack;
		} 
	}
}

void populatePlayer() {
	gameScreen[playerY][playerX] = cPlayer; // Add player icon
}

void printScreen() {
	cout << "_______________________________ CONSOLE BIATHLON SIMULATOR ________________________________" << endl;
	for (int i = 0; i < sizeY; ++i)
	{
		for (int j = 0; j < sizeX; ++j)
		{
			cout << gameScreen[i][j];
		}
		cout << endl;
	}
}

void createShootings() {
	const char cShootUp = 'T';
	const char cShootDown = '_';
	const int shootingsDefaultInterval = 20;
	shootings = (sizeX - shootingsDefaultInterval) / shootingsDefaultInterval;
	int iRand;
	int shootingPosition;
	for (int i = 0; i < shootings; i++) {
		shootingPosition = ((i * shootingsDefaultInterval) + ((shootingsDefaultInterval / 2) + 4)) + (rand() % 13);
		shootingList[i].posX = shootingPosition;
		shootingList[i].posY = trackY;
		// Shooting tables
		shootingList[i].char1 = 97 + rand() % 26;
		shootingList[i].char2 = 97 + rand() % 26;
		shootingList[i].char3 = 97 + rand() % 26;
		// Shooting character and table locations
		if (i % 2 == 0) {
			shootingList[i].character = cShootDown;
			shootingList[i].shootingTableY = shootingList[i].posY - 1;
		}
		else {
			shootingList[i].character = cShootUp;
			shootingList[i].shootingTableY = shootingList[i].posY - 2;
		}
		shootingList[i].shootingTableX = shootingList[i].posX;
	}
}

bool tryToShoot(char cShot) {
	if (cShot < 200 && cShot != 72 && cShot != 75 && cShot != 77 && cShot != 80) { // Ignore empty inputs etc and moving
		if (cShot != cHit && cShot != cMiss && cShot != cHipHit) {
			bool fromHip = shootFromHipAllowed && cPlayer == cStand;
			for (int i = 0; i < shootings; i++) {
				if (playerX == shootingList[i].posX && (cPlayer == shootingList[i].character || fromHip)) {
					if (cShot == shootingList[i].char1) {
						if (fromHip) {
							shootingList[i].char1 = cHipHit;
						}
						else {
							shootingList[i].char1 = cHit;
						}
					}
					else if (cShot == shootingList[i].char2) {
						if (fromHip) {
							shootingList[i].char2 = cHipHit;
						}
						else {
							shootingList[i].char2 = cHit;
						}
					}
					else if (cShot == shootingList[i].char3) {
						if (fromHip) {
							shootingList[i].char3 = cHipHit;
						}
						else {
							shootingList[i].char3 = cHit;
						}
					}
					else {
						if (shootingList[i].char1 != cHit && shootingList[i].char1 != cMiss && shootingList[i].char1 != cHipHit) {
							shootingList[i].char1 = cMiss;
						}
						else if (shootingList[i].char2 != cHit && shootingList[i].char2 != cMiss && shootingList[i].char2 != cHipHit) {
							shootingList[i].char2 = cMiss;
						}
						else if (shootingList[i].char3 != cHit && shootingList[i].char3 != cMiss && shootingList[i].char3 != cHipHit) {
							shootingList[i].char3 = cMiss;
						}
					}
				}
			}
		}
		return true;
	}
	return false;
}

void playerMove(int deltaX, int deltaY) {
	if (deltaX != 0) {
		switch (cPlayer) {
		case cAim:
		case cStand:
			lower();
			break;
		case cLay:
			raise();
			break;
		case cReady:
			cPlayer = cSki;
			break;
		case cDown:		// Traditional style allowed
		default:
			cPlayer = cReady;
			if (deltaX < 0 && playerX < 2) { // No backing too much..
			} else{
				playerX += deltaX;
			}
			if (playerX == sizeX - 1) {
				finished = true;
			}
		}
	}
	else if (deltaY != 0) {
		if (deltaY > 0) {
			raise();
		}
		else {
			lower();
		}
	}
}

void raise() {
	switch (cPlayer){
		case cAim:
			break;
		case cStand:
			cPlayer = cAim;
			break;
		case cDown:
			cPlayer = cReady;
			break;
		case cLay:
			cPlayer = cDown;
			break;
		default:
			cPlayer = cStand;
	}
}

void lower() {
	switch (cPlayer) {
	case cAim:
		cPlayer = cStand;
		break;
	case cStand:
		cPlayer = cReady;
		break;
	case cDown:
		cPlayer = cLay;
		break;
	case cLay:
		break;
	default:
		cPlayer = cDown;
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