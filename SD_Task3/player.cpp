#include "player.h"
#include <iostream>
using namespace std;

//getter for name
string player::getName() {
	return name;
}

//getter for hitPercentage
int player::getHitPercentage() {
	return player::hitPercentage;
}

//getter for shootingMethod
int player::getShootingMethod() {
	return shootingMethod;
}

//getter for shootingMethod
void player::setShootingMethod(int sm) {
	shootingMethod = sm;
}

//setter for name
void player::setName(string newName) {
	name = newName;
}

//setter for hitPercentage
void player::setHitPercentage(int hp) {
	hitPercentage = hp;
}

//constructor
player::player() {
	score = 501;
	dartsThrown = 0;
	totalThrown = 0;
	gamesWon = 0;
	setsWon = 0;
	hitPercentage = 70;
	busted = false;

	for (int i = 0; i < 3; i++)
	{
		turnScores[i] = -1;
	}
}

//function to check if the player is busted and decreases player's score
bool player::decreaseScore(int scoreHit, int shotType) {
	bool busted = false;
	//checks if they are busted.
	//reasons:
	//if the dart is going to take the score below 0 or to 1. Or if the dart has hit a single or treble (can't finish on that) and the score is 0
	if ((score < scoreHit) || ((score - scoreHit) == 1) || (score - scoreHit == 0 && (shotType == 2 || shotType < 1))) {
		busted = true;
	}
	//decrease score
	score -= scoreHit;
	return busted;
};

//sort display for scores on scoreboard
void player::sortScores(int shotType, string &totalScore, string &scores) {

	if (busted == true)
	{
		totalScore = "BUST"; //if the player is busted, BUST should be displayed instead of their score
	}
	else {
		totalScore = to_string(score);
	}

	//if the user doesn't have any scores yet don't display any scores
	if (turnScores[0] == -1) {
		scores = "";
	}
	else if (turnScores[1] == -1) { //if this is true, there must be a score in turnScores[0]
		if (shotType < 1 || shotType == 3 || turnScores[0] == 0) {
			//if it is a single or bull or 0
			scores = to_string(turnScores[0]); //set scores to a string of the score ready to be displayed on the scoreboard
		}
		else if (shotType == 1) {
			//if it is a double
			scores = "D" + to_string(turnScores[0] / 2);
		}
		else if (shotType == 2) {
			//if it is a treble
			scores = "T" + to_string(turnScores[0] / 3);
		}
	}
	else if (turnScores[2] == -1) { //if this is true, there must be a score in turnScores[1]
		scores += "\n\n"; //add 2 new lines
		if (shotType < 1 || shotType == 3 || turnScores[1] == 0) {
			scores += to_string(turnScores[1]); //add the next score on
		}
		else if (shotType == 1) {
			scores += "D" + to_string(turnScores[1] / 2);
		}
		else if (shotType == 2) {
			scores += "T" + to_string(turnScores[1] / 3);
		}
	}
	else {
		scores += "\n\n";
		if (shotType < 1 || shotType == 3 || turnScores[2] == 0) {
			scores += to_string(turnScores[2]);
		}
		else if (shotType == 1) {
			scores += "D" + to_string(turnScores[2] / 2);
		}
		else if (shotType == 2) {
			scores += "T" + to_string(turnScores[2] / 3);
		}
	}
}




