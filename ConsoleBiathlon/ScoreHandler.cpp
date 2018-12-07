#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Header.h"
#include "TimeHandler.h"
#include "TestHeader.h"

using namespace std;

int loadScoresFromFile(scoreEntity*, int);
void saveScoresToFile(scoreEntity*, int);

const int MAX_SCORES_SAVED = 100;
const int MAX_SCORES_SHOW = 100;
const int SCORE_SHOW_SNAP = 10;
scoreEntity scores[MAX_SCORES_SAVED];
int scoresSize;

void loadScores() {
	scoresSize = 0;
	scoresSize = loadScoresFromFile(scores, scoresSize);
}


void tryToSaveScores(scoreEntity newScore) {
	if (newScore.points > 0) {
		// Arrange so best are first etc..
		bool found = false;
		for (int i = 0; !found && i < scoresSize && i < MAX_SCORES_SAVED; i++) { // newScore -> i=(0...MAX), 0->1, 1->2, 2->3... MAX->out
			if (scores[i].points < newScore.points) {						// new points are greater -> change positions				
				if (scoresSize < MAX_SCORES_SAVED) {						// if size less than MAX -> grow array
					scoresSize++;
				}															// else leave last score out
				for (int j = scoresSize - 1; j > i; j--) {
					scores[j] = scores[j - 1];								// [MAX-1]<-[MAX-2]...[i+2]<-[i+1], [i+1]<-[i+0]
				}
				scores[i] = newScore;										// newScore -> i
				found = true;
			}// else go for next
		}
		if (!found) {
			if (scoresSize < MAX_SCORES_SAVED) {		// first results
				scores[scoresSize] = newScore;
				scoresSize++;
				found = true;
			}
		}
		if (found) {
			saveScoresToFile(scores, scoresSize);
		}
	}		// no minus scores allowed
}

void showHighScoresSnap() {
	if (scoresSize > 0) {
		cout << endl << endl << "________________HIGH SCORES________________";
		cout << endl << "## - " << "POINTS" << " : " << "TIME" << " : " << "ACCURACY" << " : " << "BONUS" << endl;
		TimeHandler time;
		for (int i = 0; i < scoresSize && i < SCORE_SHOW_SNAP; i++) {
			scoreEntity score = scores[i];
			float accuracy = (float(score.hits) / float(score.hits + score.misses)) * 100;
			cout << (i + 1) << " - " << score.points << " : " << time.getHumanReadableTime(score.time) << " : " << accuracy << "% : " << scores->bonuses << endl;
		}
	}
}

void showHighScores() {
	if (scoresSize > 0) {
		cout << endl << endl << "________________HIGH SCORES________________";
		cout << endl << "## - " << "POINTS" << " : " << "TIME" << " : " << "ACCURACY" << " : " << "BONUS" << endl;
		TimeHandler time;
		for (int i = 0; i < scoresSize && MAX_SCORES_SHOW; i++) {
			scoreEntity score = scores[i];
			float accuracy = (float(score.hits) / float(score.hits + score.misses)) * 100;
			cout << (i + 1) << " - " << score.points << " : " << time.getHumanReadableTime(score.time) << " : " << accuracy << "% : " << scores->bonuses << endl;
		}
	}
}

/*void showHighScoresByTime() {
	if (scoresSize > 0) {
		cout << endl << endl << "________________HIGH SCORES BY TIME____________";
		cout << endl << "## - " << "POINTS" << " : " << "TIME" << " : " << "ACCURACY" << " : " << "BONUS" << endl;
		TimeHandler time;
		scoreEntity tempScores[MAX_SCORES_SAVED];
		for (int i = 0; i < scoresSize && MAX_SCORES_SHOW; i++) {
			scoreEntity score = tempScores[i];
			for (int j = 0; j < scoresSize; j++) {

			}
		}
		
		for (int i = 0; i < scoresSize && MAX_SCORES_SHOW; i++) {
			scoreEntity score = tempScores[i];
			float accuracy = (float(score.hits) / float(score.hits + score.misses)) * 100;
			cout << (i + 1) << " - " << score.points << " : " << time.getHumanReadableTime(score.time) << " : " << accuracy << "% : " << scores->bonuses << endl;
		}
	}
}*/