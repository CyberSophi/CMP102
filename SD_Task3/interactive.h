#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class interactive
{
public:
	sf::RenderWindow window;
	//background texture - brick wall
	sf::Texture t_background;
	//background sprite
	sf::Sprite s_background;
	sf::RectangleShape winnerBack;
	sf::CircleShape hitMarkerRed;
	sf::CircleShape hitMarkerBlue;
	sf::CircleShape hitMarker;
	sf::CircleShape hitMarker2;
	sf::CircleShape hitMarker3;
	//dartboard texture
	sf::Texture t_dartboard;
	//dartboard sprite
	sf::Sprite s_dartboard;
	//red dart - used like a cursor for a player
	sf::Texture t_dartRed;
	sf::Sprite s_dartRed;
	//blue dart - used like a cursor for a player
	sf::Texture t_dartBlue;
	sf::Sprite s_dartBlue;
	//scoreboard
	sf::Texture t_scoreboard;
	sf::Sprite s_scoreboard;
	//fonts
	//basic font - arial
	sf::Font font;
	//handwritten font for parts of the scoreboard
	sf::Font handwritten;
	//text
	//winner - used in the winner messages
	sf::Text winnert;
	//game num - displayed to show what game/set/world championship they are on
	sf::Text counter;
	//holds what player one has hit on their turn
	sf::Text scoreOne;
	//holds what player two has hit on their turn
	sf::Text scoreTwo;
	//player one's score
	sf::Text scoreTotalOne;
	//player two's score
	sf::Text scoreTotalTwo;
	//Sets won and games won - player one
	sf::Text setsGamesWonOne;
	//Sets won and games won - player two
	sf::Text setsGamesWonTwo;
	//Frequencies
	sf::Text freq;
	//starting
	sf::Text starting;
	//scoreboard names
	sf::Text playerOneName;
	sf::Text playerTwoName;
	//sounds
	sf::SoundBuffer b_dart_noise;
	sf::Sound s_dart_noise;
	sf::SoundBuffer b_select;
	sf::Sound s_select;
	sf::SoundBuffer b_congrats;
	sf::Sound s_congrats;

	float markerOneX;
	float markerOneY;
	float markerTwoX;
	float markerTwoY;
	float markerThreeX;
	float markerThreeY;
	int markerColour;
	int sleepLength;

	interactive();

	void markerPos(int cThrow, int shotType, float& posx, float& posy);

	int radius(float posx, float posy);

	int sector(float angle);
	float workOutAngle(float xr, float yr, float r, float mousepos_x, float mousepos_y);
	int throwIt(float mousepos_x, float mousepos_y, int &type);

	void display(int cThrow, int shotType, int dartNum);

	int menu(int& wcNum, int& hitPerc, int& hitPerc2, std::string& name1, std::string& name2, int& shootMeth1, int& shootMeth2);
	int play(int& typeOfShot, int dartNum, int playerTurn);
	void winner(int gameMode);

	bool result();

	int startingPlayer(int hpOne, int hpTwo, std::string oneName, std::string twoName, int gameMode);
};

