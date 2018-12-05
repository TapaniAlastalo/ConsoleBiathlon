#pragma once

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <cstring>
#include "TimeHandler.h"

const char cHipHit = 'B';
const char cHit = 'O';
const char cMiss = 'X';
const char cShootUp = 'T';
const char cShootDown = '_';

const char cReady = 'H';
const char cSki = 'X';
const char cDown = '<';
const char cLay = cShootDown;
const char cStand = 'A';
const char cAim = cShootUp;
const char cWinner = 'Y';

const char cEmpty = ' ';
const char cStar = '*';
const char cMoonDark = 'C';
const char cMoonHalf = 'D';
const char CMoonFull = 'O';

const char cPole = '|';
const char cSlash = '/';
const char cBackSlash = '\\';
const char cTop = '_';
const char cBottom = cTop;

const char cSpectate = 'o';
const char cCheer = 'Y';
const char cFlag = 'P';
const char cStill = '|';

const char cTrace = 'u';
const char cMoose = 'w';
const char cTrack = '=';
const char cGoal = 'M';
const char cFinished = 'F';

const int MAX_SIZE_X = 10;
const int MAX_SIZE_Y = 100; 
const int MAX_SHOOTINGS = 4;

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

struct playerEntity {
	char character;
	int posX;
	int posY;
};

struct levelEntity {
	int sizeX;
	int sizeY;
	int trackX;
	int shootings;
	bool finished;
	playerEntity player;
	shootingEntity shootingList [MAX_SHOOTINGS];
};
#endif //HEADER_H
