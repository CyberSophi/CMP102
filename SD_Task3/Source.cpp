#include <iostream>
#include <stdlib.h>   
#include <time.h>
#include "player.h"
#include "dartboard.h"
#include "interactive.h"
#include <Windows.h>
#include <cmath>
using namespace std;

int main() {
	cout << "501 Darts Started" << endl;
	//initialise
	srand(time(0));
	bool playAgain = true;
	int playerTurn;
	int worldChampNum;
	int gameNumber = 0;
	int setNumber = 0;
	int turnTotal;
	int currThrow;
	dartboard board;
	player one;
	player two;
	int hitPerc1;
	int hitPerc2;
	int shootMethOne = 0;
	int shootMethTwo = 0;
	int shotType = 0;
	int aim;
	string scores = "";
	string totalScore;
	int gameMode;
	int startingPlayer;
	interactive game;

	//while playAgain is true, this loop will repeat
	while (playAgain)
	{
		//initialise
		string nameone;
		string nametwo;
		int worldChampWins[8][8] = { 0 };

		//go to menu
		gameMode = game.menu(worldChampNum, hitPerc1, hitPerc2, nameone, nametwo, shootMethOne, shootMethTwo);

		//set names and shoot methods
		one.setName(nameone);
		two.setName(nametwo);
		one.setShootingMethod(shootMethOne);
		two.setShootingMethod(shootMethTwo);

		//sets playerOneName and playerTwoName to the corresponding names
		game.playerOneName.setString(one.getName());
		game.playerTwoName.setString(two.getName());

		//sets the accuracy for each player
		one.setHitPercentage(hitPerc1);
		two.setHitPercentage(hitPerc2);

		//repeats until all world championships are complete
		for (int i = 1; i < worldChampNum + 1; i++)
		{
			//get which player is starting
			startingPlayer = game.startingPlayer(one.getHitPercentage(), two.getHitPercentage(), one.getName(), two.getName(), gameMode);
			//reset the amount of sets each player has won
			one.setsWon = 0;
			two.setsWon = 0;
			//reset the setNumber to 0
			setNumber = 0;
			//reset the amount of sets each player has won
			while (one.setsWon != 7 && two.setsWon != 7) {
				//reset the amount of games each player has won
				one.gamesWon = 0;
				two.gamesWon = 0;
				//reset the gameNumber to 0
				gameNumber = 0;
				//increase the set number
				setNumber++;
				while (one.gamesWon != 3 && two.gamesWon != 3)
				{
					//sets the players turn variable to whoever is starting
					playerTurn = startingPlayer;
					//increase the game number
					gameNumber++;
					//this will be displayed on the scoreboard to show what wc/set/game it is
					game.counter.setString("WC: " + to_string(i) + " - Set: " + to_string(setNumber) + " - Game: " + to_string(gameNumber));
					//displayed on scoreboard to show how many games/sets each of the players have won
					game.setsGamesWonOne.setString("Games Won: " + to_string(one.gamesWon) + "\nSets Won: " + to_string(one.setsWon));
					game.setsGamesWonTwo.setString("Games Won: " + to_string(two.gamesWon) + "\nSets Won: " + to_string(two.setsWon));
					//reset variables
					one.score = 501;
					two.score = 501;
					one.dartsThrown = 0;
					two.dartsThrown = 0;
					//reset the scores for each of the turns
					for (int r = 0; r < 3; r++)
					{
						one.turnScores[r] = -1;
						two.turnScores[r] = -1;
					}
					//clear the strings which hold the 3 scores
					game.scoreOne.setString("");
					game.scoreTwo.setString("");
					//update the score which is displayed
					game.scoreTotalOne.setString(to_string(one.score));
					game.scoreTotalTwo.setString(to_string(two.score));
					//will keep looping until a player wins the game (score is 0)
					while (one.score != 0 && two.score != 0) {
						if (playerTurn == 1) {
							//player one's turn
							//checks if the board needs to be cleared
							if (playerTurn == startingPlayer && (one.turnScores[2] != -1 || one.busted)) {
								for (int r = 0; r < 3; r++)
								{
									one.turnScores[r] = -1;
									two.turnScores[r] = -1;
								}
								game.scoreOne.setString("");
								game.scoreTwo.setString("");
								game.scoreTotalOne.setString(to_string(one.score));
								game.scoreTotalTwo.setString(to_string(two.score));
							}
							turnTotal = 0;
							one.busted = false;
							//when this is set to 0, it means the markers will be red 
							game.markerColour = 0;
							//will loop around the player's 3 turns
							for (int i = 0; i < 3; i++)
							{
								//checks if they should have their turn (if they have won or are bust they shouldn't throw any more)
								if (one.score > 0 && one.busted == false) {
									//if the gameMode varaible is 2, this means it is computer vs computer - so will aim without user input
									if (gameMode == 2) {
										//if it is the player's first dart, should display the board (otherwise AI is so fast that you never the score as 501)
										if (i == 0)
										{
											//just displays the window updated
											game.play(shotType, -1, playerTurn);
										}
										//aims automatically
										if (one.getShootingMethod() == 2)
										{
											aim = board.aim(one.score, i, two.score, shotType);
										}
										else {
											aim = board.aim_task_one(one.score);
											if (aim == 50) {
												shotType = 3;
											}
											//shoot for double
											else if (aim % 2 == 0 && aim <= 40) {
												shotType = 1;
											}
											//shoot for single or outer bull
											else if (aim < 21 || aim == 25) {
												shotType = 0;
											}
											//shoot for treble
											else {
												shotType = 2;
											}
										}
									}
									else //if it is gamemode 0 or 1, then the user will choose where it is aimed at
									{
										//user decides where to aim
										aim = game.play(shotType, i, playerTurn);
									}

									//currThrow is set to whatever they actually hit
									currThrow = board.shootInteractive(one.getHitPercentage(), aim, shotType);
									//player score is decreased. bust variable is set to true if they go bust
									one.busted = one.decreaseScore(currThrow, shotType);
									//keep track of what has been hit this turn
									one.turnScores[i] = currThrow;

									//sorts the display
									one.sortScores(shotType, totalScore, scores);
									game.scoreOne.setString(scores);
									game.scoreTotalOne.setString(totalScore);

									//displays the window with all the markers on it for a period of time
									game.display(currThrow, shotType, i);

									//add the value the player hit to their turn total (this is so the score can be reverted if they are busted)
									turnTotal += currThrow;
									one.dartsThrown++;
								}
							}
							if (one.busted == true) {
								one.score += turnTotal;
							}
							playerTurn = 2;

						}
						else {
							//player two's turn
							if (playerTurn == startingPlayer && (two.turnScores[2] != -1 || two.busted)) {
								for (int r = 0; r < 3; r++)
								{
									one.turnScores[r] = -1;
									two.turnScores[r] = -1;
								}
								game.scoreOne.setString("");
								game.scoreTwo.setString("");
								game.scoreTotalOne.setString(to_string(one.score));
								game.scoreTotalTwo.setString(to_string(two.score));
							}

							turnTotal = 0;
							two.busted = false;
							game.markerColour = 1;
							for (int i = 0; i < 3; i++)
							{
								if (two.score > 0 && two.busted == false) {

									//to display a screen update before it starts shooting (otherwise no screen update until display function)

									if (gameMode == 0)
									{
										aim = game.play(shotType, i, playerTurn);
									}
									else {
										if (i == 0)
										{
											game.play(shotType, -1, playerTurn);
										}
										if (two.getShootingMethod() == 2)
										{
											aim = board.aim(two.score, i, one.score, shotType);
										}
										else {
											aim = board.aim_task_one(two.score);
											if (aim == 50) {
												shotType = 3;
											}
											//shoot for double
											else if (aim % 2 == 0 && aim <= 40) {
												shotType = 1;
											}
											//shoot for single or outer bull
											else if (aim < 21 || aim == 25) {
												shotType = 0;
											}
											//shoot for treble
											else {
												shotType = 2;
											}
										}
									}
									currThrow = board.shootInteractive(two.getHitPercentage(), aim, shotType);
									two.busted = two.decreaseScore(currThrow, shotType);
									two.turnScores[i] = currThrow;

									two.sortScores(shotType, totalScore, scores);
									game.scoreTwo.setString(scores);
									game.scoreTotalTwo.setString(totalScore);

									game.display(currThrow, shotType, i);

									turnTotal += currThrow;
									two.dartsThrown++;
								}
							}
							if (two.busted == true) {
								two.score += turnTotal;
							}
							playerTurn = 1;
						}
					}
					//work out who won the game
					if (one.score == 0) {
						//increase amount of games won
						one.gamesWon++;
						//set the winner message
						game.setsGamesWonOne.setString("Games Won: " + to_string(one.gamesWon) + "\nSets Won: " + to_string(one.setsWon));
						game.winnert.setString(one.getName() + " won the game.\nThey threw " + to_string(one.dartsThrown) + " darts.\nPress Enter");
					}
					else if (two.score == 0) {
						//increase amount of games won
						two.gamesWon++;
						//set the winner message
						game.setsGamesWonTwo.setString("Games Won: " + to_string(two.gamesWon) + "\nSets Won: " + to_string(two.setsWon));
						game.winnert.setString(two.getName() + " won the game.\nThey threw " + to_string(two.dartsThrown) + " darts.\nPress Enter");
					}
					//display screen with winner message
					game.winner(gameMode);

					//reset 
					for (int r = 0; r < 3; r++)
					{
						one.turnScores[r] = -1;
						two.turnScores[r] = -1;
					}

					//switch starting player
					if (startingPlayer == 1) {
						startingPlayer = 2;
					}
					else {
						startingPlayer = 1;
					}
				}
				//if a player wins 3 games, they win the set
				if (one.gamesWon == 3) {
					//increase the amount of sets they have won
					one.setsWon++;
					//change winner message
					game.setsGamesWonOne.setString("Games Won: " + to_string(one.gamesWon) + "\nSets Won: " + to_string(one.setsWon));
					game.winnert.setString(one.getName() + " won the set.\nPress Enter");
				}
				else if (two.gamesWon == 3) {
					two.setsWon++;
					game.setsGamesWonTwo.setString("Games Won: " + to_string(one.gamesWon) + "\nSets Won: " + to_string(one.setsWon));
					game.winnert.setString(two.getName() + " won the set.\nPress Enter");
				}
				//display screen with winner message
				game.winner(gameMode);
			}
			//if a player wins 7 sets, they win the world championship
			if (one.setsWon == 7) {
				//change winner message
				game.winnert.setString(one.getName() + " won the W.C.\nPress Enter");
			}
			else if (two.setsWon == 7) {
				//change winner message
				game.winnert.setString(two.getName() + " won the W.C.\nPress Enter");
			}
			//store result of that world championship
			worldChampWins[one.setsWon][two.setsWon]++;
			//display screen with winner message
			game.winner(gameMode);
		}

		//set frequency variable
		string frequency = one.getName() + " : " + two.getName() + "\n";

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				//only add them if they have happened
				if (worldChampWins[i][j] != 0) {
					//add to frequency variable i (player one's sets won) and j (player two's sets won) and calculate the percentage 
					frequency += to_string(i) + " : " + to_string(j) + " " + to_string(float(worldChampWins[i][j]) / float(worldChampNum) * 100) + "%\n";
				}
			}
		}
		//set freq to what the frequency variable is
		game.freq.setString(frequency);
		//display results of world championship(s) and find out if player wants to exit or go back to the start
		playAgain = game.result();
	}
}
	