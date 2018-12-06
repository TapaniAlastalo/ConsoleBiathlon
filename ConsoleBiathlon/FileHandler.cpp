#include "pch.h"
#include "Header.h"
#include <fstream>

using namespace std;

void loadScoresFromFile(scoreEntity*, int*);
void addToScores(scoreEntity*, scoreEntity, int*);
void saveScoresToFile(scoreEntity*, int*);

const string fileName = "scores.txt";

void loadScoresFromFile(scoreEntity *scores, int *scoresSize) {
	ifstream in(fileName, ios_base::binary || ios_base::app);
	if (in.is_open()) {
		while (in.peek() != EOF) {
			scoreEntity score;
			in.read((char *)&score, sizeof(scoreEntity));
			addToScores(scores, score, scoresSize);
		}
		in.close();
	}
}

void addToScores(scoreEntity *scores, scoreEntity score, int *scoresSize) {
	scores[*scoresSize] = score;
	(*scoresSize)++;
}

void saveScoresToFile(scoreEntity *scores, int *scoresSize) {
	ofstream out(fileName, ios_base::binary);
	if (out.is_open()) {
		const int size = *scoresSize;
		for (int i = 0; i < size; i++) {
			const scoreEntity score = scores[i];
			out.write((char *)&score, sizeof(scoreEntity));
		}
		out.close();
	}
}