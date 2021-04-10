#pragma once
#include <string>
class player
{
private:
	std::string name;
	int hitPercentage;
	int shootingMethod;
public:
	int score;
	int dartsThrown;
	int totalThrown;
	int gamesWon;
	int setsWon;
	bool busted;
	int turnScores[3];

	//getter for name
	std::string getName();

	//getter for hitPercentage
	int getHitPercentage();

	int getShootingMethod();

	//setter for name
	void setName(std::string newName);

	//setter for hitPercentage
	void setHitPercentage(int hp);

	//setter for shootingMethod
	void setShootingMethod(int sm);

	player();

	bool decreaseScore(int scoreHit, int shotType);

	void sortScores(int shotType, std::string& totalScore, std::string& scores);
};

