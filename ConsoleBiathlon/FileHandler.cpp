#include "pch.h"
#include "Header.h"
#include <fstream>
#include <iostream>

using namespace std;

int addToScores(scoreEntity*, scoreEntity, int);

const string fileName = "scores.dat";

int loadScoresFromFile(scoreEntity *scores, int scoresSize) {
	ifstream in(fileName, ios_base::binary || ios_base::app);
	if (in.is_open()) {
		while (in.peek() != EOF) {
			scoreEntity score;
			in.read((char *)&score, sizeof(scoreEntity));
			scoresSize = addToScores(scores, score, scoresSize);
		}
		in.close();
	}
	return scoresSize;
}

int addToScores(scoreEntity *scores, scoreEntity score, int scoresSize) {
	std::cout << endl << "addtoscores size " << scoresSize;
	scores[scoresSize] = score;
	scoresSize++;
	return scoresSize;
}

void saveScoresToFile(scoreEntity *scores, int scoresSize) {
	ofstream out(fileName, ios_base::binary);	// ::app would append. No need for that..
	if (out.is_open()) {
		for (int i = 0; i < scoresSize; i++) {
			const scoreEntity score = scores[i];
			out.write((char *)&score, sizeof(scoreEntity));
		}
		out.close();
	}
}