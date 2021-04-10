#include "interactive.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <cmath>
using namespace std;

interactive::interactive()
	: window(sf::VideoMode(1280, 720), "501 Darts!", sf::Style::Close) //create a window which is 1280 by 720 pixels
{
	markerOneX = 0;
	markerOneY = 0;
	markerTwoX = 0;
	markerTwoY = 0;
	markerThreeX = 0;
	markerThreeY = 0;
	markerColour = 0;
	sleepLength = 1;

	//make cursor not visible in the window
	window.setMouseCursorVisible(false);

	//SHAPES
	//this is the background shape to go behind game/set/world championship won messages during the game 
	winnerBack.setPosition(200, 290); //sets the position within the window
	winnerBack.setSize(sf::Vector2f(300, 120)); //sets the size in pixels
	winnerBack.setFillColor(sf::Color::Yellow); //sets the colour to yellow
	winnerBack.setOutlineThickness(5); //sets the outline to a thickness of 5 pixels
	winnerBack.setOutlineColor(sf::Color(0, 0, 0)); //makes the outline black

	//red circle shapes used to show where the players threw when deciding who goes first
	hitMarkerRed.setRadius(5);
	hitMarkerRed.setFillColor(sf::Color::Red);
	hitMarkerRed.setOutlineThickness(2);
	hitMarkerRed.setOutlineColor(sf::Color(0, 0, 100));

	hitMarkerBlue.setRadius(5);
	hitMarkerBlue.setFillColor(sf::Color::Blue);
	hitMarkerBlue.setOutlineThickness(2);
	hitMarkerBlue.setOutlineColor(sf::Color(0, 0, 100));

	//three hitmarkers used to show where the players hit during their turn
	hitMarker.setRadius(5);
	hitMarker.setFillColor(sf::Color::Red);
	hitMarker.setOutlineThickness(2);
	hitMarker.setOutlineColor(sf::Color(0, 0, 100));

	hitMarker2.setRadius(5);
	hitMarker2.setFillColor(sf::Color::Red);
	hitMarker2.setOutlineThickness(2);
	hitMarker2.setOutlineColor(sf::Color(0, 0, 100));

	hitMarker3.setRadius(5);
	hitMarker3.setFillColor(sf::Color::Red);
	hitMarker3.setOutlineThickness(2);
	hitMarker3.setOutlineColor(sf::Color(0, 0, 100));

	//load the image
	if (!t_dartboard.loadFromFile("dartboard.png"))
	{
		cout << "error" << endl;
	}

	s_dartboard.setTexture(t_dartboard);
	s_dartboard.setPosition(0, 0); //set the position
	s_dartboard.setScale(0.85f, 0.85f);

	//load the image
	if (!t_background.loadFromFile("brick.jfif"))
	{
		cout << "error" << endl;
	}

	//make the background sprite use the background texture
	s_background.setTexture(t_background);
	//set the scale of the sprite
	s_background.setScale(1.5f, 1.5f);

	//red dart
	if (!t_dartRed.loadFromFile("reddart.png"))
	{
		cout << "error" << endl;
	}

	s_dartRed.setTexture(t_dartRed);
	s_dartRed.setScale(0.4f, 0.4f);

	//blue dart
	if (!t_dartBlue.loadFromFile("bluedart.png"))
	{
		cout << "error" << endl;
	}

	s_dartBlue.setTexture(t_dartBlue);
	s_dartBlue.setScale(0.4f, 0.4f);

	//scoreboard
	if (!t_scoreboard.loadFromFile("blackboard.jpg"))
	{
		cout << "error" << endl;
	}

	s_scoreboard.setTexture(t_scoreboard);
	s_scoreboard.setPosition(804, 0);
	s_scoreboard.setScale(0.411f, 0.411f);

	//fonts
	if (!font.loadFromFile("arial.ttf"))
	{
		cout << "error" << endl;
	}

	if (!handwritten.loadFromFile("segoepr.ttf"))
	{
		cout << "error" << endl;
	}

	//text
	winnert.setFont(font); //sets the font to arial
	winnert.setCharacterSize(24); //sets the font size
	winnert.setPosition(220, 310);
	winnert.setFillColor(sf::Color::Black);
	winnert.setStyle(sf::Text::Bold); //sets the style to bold
	winnert.setString(""); //sets the string

	counter.setFont(font);
	counter.setCharacterSize(18);
	counter.setPosition(930, 80);
	counter.setFillColor(sf::Color::White);
	counter.setStyle(sf::Text::Bold | sf::Text::Underlined); //sets the style to bold and underlined

	scoreOne.setFont(handwritten); //use the handwritten font
	scoreOne.setCharacterSize(24);
	scoreOne.setPosition(910, 160);
	scoreOne.setFillColor(sf::Color::White);

	scoreTwo.setFont(handwritten);
	scoreTwo.setCharacterSize(24);
	scoreTwo.setPosition(1130, 160);
	scoreTwo.setFillColor(sf::Color::White);

	scoreTotalOne.setFont(font);
	scoreTotalOne.setCharacterSize(24);
	scoreTotalOne.setPosition(910, 400);
	scoreTotalOne.setFillColor(sf::Color::Red);
	scoreTotalOne.setString("501"); //sets it to whatever one.score is 
	scoreTotalOne.setOutlineThickness(2);
	scoreTotalOne.setOutlineColor(sf::Color(255, 255, 255));
	scoreTotalOne.setStyle(sf::Text::Bold);

	scoreTotalTwo.setFont(font);
	scoreTotalTwo.setCharacterSize(24);
	scoreTotalTwo.setPosition(1130, 400);
	scoreTotalTwo.setFillColor(sf::Color::Blue);
	scoreTotalTwo.setString("501"); //sets it to whatever two.score is 
	scoreTotalTwo.setOutlineThickness(2);
	scoreTotalTwo.setOutlineColor(sf::Color(255, 255, 255));
	scoreTotalTwo.setStyle(sf::Text::Bold);

	setsGamesWonOne.setFont(font);
	setsGamesWonOne.setCharacterSize(20);
	setsGamesWonOne.setPosition(850, 500);
	setsGamesWonOne.setFillColor(sf::Color::White);
	setsGamesWonOne.setString("Games Won: 0 + \nSets Won: 0");

	setsGamesWonTwo.setFont(font);
	setsGamesWonTwo.setCharacterSize(20);
	setsGamesWonTwo.setPosition(1060, 500);
	setsGamesWonTwo.setFillColor(sf::Color::White);
	setsGamesWonTwo.setString("Games Won: 0 + \nSets Won: 0");

	freq.setFont(font);
	freq.setCharacterSize(20);
	freq.setPosition(400, 200);
	freq.setFillColor(sf::Color::Black);

	starting.setFont(font);
	starting.setCharacterSize(40);
	starting.setPosition(740, 100);
	starting.setFillColor(sf::Color::Black);
	starting.setStyle(sf::Text::Bold);
	starting.setOutlineThickness(2);
	starting.setOutlineColor(sf::Color::White);

	playerOneName.setFont(font);
	playerOneName.setCharacterSize(24);
	playerOneName.setPosition(910, 110);
	playerOneName.setFillColor(sf::Color::Red);
	playerOneName.setOutlineThickness(1);
	playerOneName.setOutlineColor(sf::Color(255, 255, 255));
	playerOneName.setStyle(sf::Text::Bold);

	playerTwoName.setFont(font);
	playerTwoName.setCharacterSize(24);
	playerTwoName.setPosition(1130, 110);
	playerTwoName.setFillColor(sf::Color::Blue);
	playerTwoName.setOutlineThickness(1);
	playerTwoName.setOutlineColor(sf::Color(255, 255, 255));
	playerTwoName.setStyle(sf::Text::Bold);

	//sounds
	if (!b_dart_noise.loadFromFile("dart.wav"))
	{
		cout << "error" << endl;
	}

	s_dart_noise.setBuffer(b_dart_noise);

	if (!b_select.loadFromFile("select.wav"))
	{
		cout << "error" << endl;
	}

	s_select.setBuffer(b_select);

	if (!b_congrats.loadFromFile("congrats.wav"))
	{
		cout << "error" << endl;
	}

	s_congrats.setBuffer(b_congrats);
}
	
//function to check if a string can be converted to a number
bool isNum(string q, int v)
{
	//is every character a number
	for (int i = 0; i < q.length(); i++) {
		if (isdigit(q[i]) == false) {
			return false;
		}	
	}

	//when checking accuracy, check if it in the right range
	if (v == 0)
	{
		if (std::stoi(q) > 20 && std::stoi(q) < 85)
		{
			return true;
		}
	}
	//when checking world champ number, check if it in the right range
	else if (v == 1) {
		if (std::stoi(q) > 0 && std::stoi(q) < 1000)
		{
			return true;
		}
	}
	return false;
}

//work out where the dot should be drawn when it actually is thrown
void interactive::markerPos(int cThrow, int shotType, float &posx, float &posy) {
	float radius;
	float angle = 0;
	float calcAngle;

	//generate random radius within that section
	if (cThrow == 25)
	{
		//outer bull
		radius = rand() % 149 + 131;
	}
	else if (cThrow == 0)
	{
		//missed the board
		radius = rand() % 300 + 2871;
	}
	else if (shotType == 3) {
		//bull
		radius = rand() % 13;
	}
	else if (shotType == 2) {
		//treble
		radius = rand() % 179 + 1591;
		cThrow = cThrow / 3;
	}
	else if (shotType == 1){
		//double
		radius = rand() % 189 + 2621;
		cThrow = cThrow / 2;
	}
	else if (shotType == 0) {
		//single
		radius = rand() % 1309 + 281;
	}
	else if (shotType == -1) {
		//outer single
		radius = rand() % 849 + 1771;
	}

	//divide by 10 to get it back to having a decimal point
	radius = radius / 10;

	//generate random angle within that section
	if (cThrow == 20)
	{
		angle = rand() % 18;
	}
	else if (cThrow == 1)
	{
		angle = rand() % 18 + 18;
	}
	else if (cThrow == 18)
	{
		angle = rand() % 18 + 36;
	}
	else if (cThrow == 4)
	{
		angle = rand() % 18 + 54;
	}
	else if (cThrow == 13)
	{
		angle = rand() % 18 + 72;
	}
	else if (cThrow == 6)
	{
		angle = rand() % 18 + 90;
	}
	else if (cThrow == 10)
	{
		angle = rand() % 18 + 108;
	}
	else if (cThrow == 15)
	{
		angle = rand() % 18 + 126;
	}
	else if (cThrow == 2)
	{
		angle = rand() % 18 + 144;
	}
	else if (cThrow == 17)
	{
		angle = rand() % 18 + 162;
	}
	else if (cThrow == 3)
	{
		angle = rand() % 18 + 180;
	}
	else if (cThrow == 19)
	{
		angle = rand() % 18 + 198;
	}
	else if (cThrow == 7)
	{
		angle = rand() % 18 + 216;
	}
	else if (cThrow == 16)
	{
		angle = rand() % 18 + 234;
	}
	else if (cThrow == 8)
	{
		angle = rand() % 18 + 252;
	}
	else if (cThrow == 11)
	{
		angle = rand() % 18 + 270;
	}
	else if (cThrow == 14)
	{
		angle = rand() % 18 + 288;
	}
	else if (cThrow == 9)
	{
		angle = rand() % 18 + 306;
	}
	else if (cThrow == 12)
	{
		angle = rand() % 18 + 324;
	}
	else if (cThrow == 5)
	{
		angle = rand() % 18 + 342;
	}
	else {
		angle = rand() % 360;
	}

	angle = angle - 9; //fix the angle (as the dartboard's lines are rotated)

	//if the angle goes below 0, make it is set to the correct angle
	if (angle < 0)
	{
		angle = 360 + angle;
	}

	//get angle used for calulation (uses triangles)
	if (angle > 90 && angle <= 180)
	{
		calcAngle = 180 - angle;
	}
	else if (angle > 180 && angle <= 270)
	{
		calcAngle = 180 - angle;
	}
	else if (angle > 270 && angle <= 360)
	{
		calcAngle = 360 - angle;
	}
	else {
		calcAngle = angle;
	}

	float ry = cos(calcAngle * 3.1415 / 180) * radius; //using hypotenuse and angle, get ry
	float rx = sqrt(pow(radius, 2) - pow(ry, 2)); //once have ry, can get other side of the triangle using radius and ry

	//find out coords in window
	if (angle <= 90)
	{
		posx = 358 + rx;
		posy = 357 - ry;
	}
	else if (angle <= 180)
	{
		posx = 358 + rx;
		posy = 357 + ry;
	}
	else if (angle <= 270)
	{
		posx = 358 - rx;
		posy = 357 + ry;
	}
	else if (angle <= 360)
	{
		posx = 358 - rx;
		posy = 357 - ry;
	}
}

//works out radius
int interactive::radius(float posx, float posy) {
	int xr;
	int yr;

	//work out distances from centre (centre is at (358, 357))
	if (posx < 358) {
		xr = 358 - posx;
	}
	else {
		xr = posx - 358;
	}

	if (posy < 357) {
		yr = 357 - posy;
	}
	else {
		yr = posy - 357;
	}

	//Pythagoras' theorem
	 return sqrt(pow(xr, 2) + pow(yr, 2));
}

//works out which sector they are in determined by the angle
int interactive::sector(float angle) {
	if (angle > 351 || angle < 9)
	{
		return 20;
	}
	else if (angle < 27)
	{
		return 1;
	}
	else if (angle < 45)
	{
		return 18;
	}
	else if (angle < 63)
	{
		return 4;
	}
	else if (angle < 81)
	{
		return 13;
	}
	else if (angle < 99)
	{
		return 6;
	}
	else if (angle < 117)
	{
		return 10;
	}
	else if (angle < 135)
	{
		return 15;
	}
	else if (angle < 153)
	{
		return 2;
	}
	else if (angle < 171)
	{
		return 17;
	}
	else if (angle < 189)
	{
		return 3;
	}
	else if (angle < 207)
	{
		return 19;
	}
	else if (angle < 225)
	{
		return 7;
	}
	else if (angle < 243)
	{
		return 16;
	}
	else if (angle < 261)
	{
		return 8;
	}
	else if (angle < 279)
	{
		return 11;
	}
	else if (angle < 297)
	{
		return 14;
	}
	else if (angle < 315)
	{
		return 9;
	}
	else if (angle < 333)
	{
		return 12;
	}
	else if (angle < 351)
	{
		return 5;
	}
}

//works out which angle it is at
float interactive::workOutAngle(float xr, float yr, float r, float mousepos_x, float mousepos_y) {
	float a;
	//must be at 0 (or 360 technically) degrees
	if (xr == 0 && mousepos_y < 357)
	{
		return 0;
	}
	//at 180 degrees
	else if (xr == 0 && mousepos_y > 357)
	{
		return 180;
	}
	//at 270 degrees
	else if (yr == 0 && mousepos_x < 357)
	{
		return 270;
	}
	//at 90 degrees
	else if (yr == 0 && mousepos_x > 357)
	{
		return 90;
	}
	else { 
		//work out angle and convert it to degrees from radians
		a = (atan(yr / xr)) * 180 / 3.1415;

		//work out angle from diameter line running from top to bottom
		//top right
		if (mousepos_x > 358 && mousepos_y < 357) {
			return 90 - a;
		}
		//bottom right
		else if (mousepos_x > 358 && mousepos_y > 357) {
			return 90 + a;
		}
		//bottom left
		else if (mousepos_x < 358 && mousepos_y > 357) {
			return 270 - a;
		}
		//top left
		else if (mousepos_x < 358 && mousepos_y < 357) {
			return 270 + a;
		}
	}
}

//work out where the dart was aimed at on the board
int interactive::throwIt(float mousepos_x, float mousepos_y, int &type) {
	float xr;
	float yr;
	float r;
	float angle;

	//work out the distance to the centre on the x axis 
	if (mousepos_x < 358) {
		xr = 358 - mousepos_x;
	}
	else {
		xr = mousepos_x - 358;
	}

	//work out the distance to the centre on the y axis 
	if (mousepos_y < 357) {
		yr = 357 - mousepos_y;
	}
	else {
		yr = mousepos_y - 357;
	}

	//calculate radius using Pythagoras' Theorem
	r = sqrt(pow(xr, 2) + pow(yr, 2));
	
	//work out if it is in the bull, outer bull, inner single, treble, outer single or double area
	//bull
	if (r < 13.1)
	{
		type = 3;
		return 50;
	}
	//outer bull
	else if (r < 28.1)
	{
		type = 0;
		return 25;
	}
	//single
	else if (r < 159.1)
	{
		angle = workOutAngle(xr, yr, r, mousepos_x, mousepos_y);
		type = 0;
		return sector(angle);
	}
	//treble
	else if (r < 177.1)
	{
		angle = workOutAngle(xr, yr, r, mousepos_x, mousepos_y);
		type = 2;
		return sector(angle) * 3;
	}
	//outer single
	else if (r < 262.1)
	{
		angle = workOutAngle(xr, yr, r, mousepos_x, mousepos_y);
		type = -1;
		return sector(angle);
	}
	//double
	else if (r < 281.1)
	{
		angle = workOutAngle(xr, yr, r, mousepos_x, mousepos_y);
		type = 1;
		return sector(angle) * 2;
	}
	else {
		//if it's in none of those areas, they have definately missed
		type = 0;
		return 0;
	}
}

//display screen
void interactive::display(int cThrow, int shotType, int dartNum) {
	if (markerColour == 0) //display red dots
	{
		hitMarker.setFillColor(sf::Color::Red);
		hitMarker2.setFillColor(sf::Color::Red);
		hitMarker3.setFillColor(sf::Color::Red);
	}
	else //display blue dots
	{
		hitMarker.setFillColor(sf::Color::Blue);
		hitMarker2.setFillColor(sf::Color::Blue);
		hitMarker3.setFillColor(sf::Color::Blue);
	}
	
	//display the correct number of dots, depending on how many have been thrown
	if (dartNum == 0)
	{
		//calculate position
		markerPos(cThrow, shotType, markerOneX, markerOneY); 
		//draw it (circle has a radius of 5 which is why it is offset)
		hitMarker.setPosition(markerOneX - 5, markerOneY - 5);
	}
	else if (dartNum == 1)
	{
		markerPos(cThrow, shotType, markerTwoX, markerTwoY);
		hitMarker2.setPosition(markerTwoX - 5, markerTwoY - 5);
	}
	else if (dartNum == 2)
	{
		markerPos(cThrow, shotType, markerThreeX, markerThreeY);
		hitMarker3.setPosition(markerThreeX - 5, markerThreeY - 5);
	}
	s_dart_noise.play();
	window.clear();
	window.draw(s_background);
	window.draw(s_dartboard);
	window.draw(s_scoreboard);
	window.draw(playerOneName);
	window.draw(playerTwoName);
	window.draw(counter);
	window.draw(scoreOne);
	window.draw(scoreTwo);
	window.draw(scoreTotalOne);
	window.draw(scoreTotalTwo);
	window.draw(setsGamesWonOne);
	window.draw(setsGamesWonTwo);

	//draw the appropriate markers
	if (dartNum == 0)
	{
		window.draw(hitMarker);
	}
	else if (dartNum == 1)
	{
		window.draw(hitMarker);
		window.draw(hitMarker2);
	}
	else {
		window.draw(hitMarker);
		window.draw(hitMarker2);
		window.draw(hitMarker3);
	}
	
	window.display();
	Sleep(500 * sleepLength);
}

//menu screen used for letting the user make decisions 
int interactive::menu(int& wcNum, int& hitPerc, int& hitPerc2, std::string& name1, std::string& name2, int& shootMeth1, int& shootMeth2) {
	//rectangle shape 
	sf::RectangleShape backing;
	backing.setPosition(380, 200);
	backing.setSize(sf::Vector2f(500, 200));
	backing.setFillColor(sf::Color(255, 255, 255));
	backing.setOutlineThickness(5);
	backing.setOutlineColor(sf::Color(0, 0, 0));

	//title of the menu
	sf::Text title;
	title.setFont(font);
	title.setString("INTERACTIVE 501 DARTS");
	title.setCharacterSize(50);
	title.setPosition(320, 100);
	title.setFillColor(sf::Color(255, 51, 0));
	title.setStyle(sf::Text::Bold);
	title.setOutlineThickness(5);
	title.setOutlineColor(sf::Color(0, 0, 0));

	//start message
	sf::Text startMessage;
	startMessage.setFont(font);
	startMessage.setString("Press number 1, 2, 3, or 4\n(1)Player vs Player\n(2)Player vs Computer\n(3)Computer vs Computer\n(4)Quick Computer vs Computer");
	startMessage.setCharacterSize(30);
	startMessage.setPosition(400, 200);
	startMessage.setFillColor(sf::Color::Black);
	startMessage.setStyle(sf::Text::Bold);

	//text input - changed when the user types answers so they can see what they are entering
	string str;
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setPosition(410, 350);
	text.setFillColor(sf::Color::Blue);

	int stage = 0; //variable holds which stage of the menu the user is at
	int gameMode = 0;
	string wcNumStr;
	string hitPercStr;
	bool done = false;
	while (window.isOpen() && done == false)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//Choose gamemode, pressing 1, 2 or 3
			if ((event.type == sf::Event::KeyReleased) && stage == 0)
			{
				if (event.key.code == sf::Keyboard::Num1)
				{
					gameMode = 0;
					stage++; 
					startMessage.setString("Name of player 1:"); //displays next menu message
					sleepLength = 1;
					s_select.play();
				}
				if (event.key.code == sf::Keyboard::Num2)
				{
					gameMode = 1;
					stage++;
					startMessage.setString("Name of player:");
					sleepLength = 1;
					s_select.play();
				}
				if (event.key.code == sf::Keyboard::Num3)
				{
					gameMode = 2;
					stage++;
					startMessage.setString("Name of computer 1:");
					sleepLength = 1;
					s_select.play();
				}
				if (event.key.code == sf::Keyboard::Num4)
				{
					gameMode = 2;
					stage++;
					startMessage.setString("Name of computer 1:");
					s_select.play();
					sleepLength = 0;
				}
			}

			//shooting method player two
			if ((event.type == sf::Event::KeyReleased) && stage == 6)
			{
				if (event.key.code == sf::Keyboard::Num1)
				{
					shootMeth2 = 1;
					startMessage.setString("Number of World\nChampionships:");
					stage++;
					s_select.play();
				}
				if (event.key.code == sf::Keyboard::Num2)
				{
					shootMeth2 = 2;
					startMessage.setString("Number of World\nChampionships:");
					stage++;
					s_select.play();
				}
			}

			//shooting method player one
			if ((event.type == sf::Event::KeyReleased) && stage == 5)
			{
				if (event.key.code == sf::Keyboard::Num1)
				{
					shootMeth1 = 1;
					if (gameMode == 2)
					{
						startMessage.setString("Aiming method of computer 2:\n(1)simple\n(2)advanced");
						stage++;
					}
					else {
						startMessage.setString("Number of World\nChampionships:");
						stage = 7;
					}
					s_select.play();
				}
				if (event.key.code == sf::Keyboard::Num2)
				{
					shootMeth1 = 2;
					if (gameMode == 2)
					{
						startMessage.setString("Aiming method of computer 2:\n(1)simple\n(2)advanced");
						stage++;
					}
					else {
						startMessage.setString("Number of World\nChampionships:");
						stage = 7;
					}
					s_select.play();
				}
			}

			//as long as the text being entered isnt the enter key
			if ((event.type == sf::Event::TextEntered && event.text.unicode != 13))
			{
				//Player One Name
				//allow for backspace
				if (event.text.unicode == '\b' && stage == 1) {
					//if the name1 variable has something in it
					if (name1.size() > 0) {
						//get rid of the last character
						name1.erase(name1.size() - 1, 1);
						//update it so it looks correct on screen when it is displayed
						text.setString(name1);
					}
				}
				//if it isn't a backspace, the size isn't bigger than five and it is this stage of the menu
				else if (event.text.unicode < 128 && name1.size() < 5 && stage == 1)
				{
					//add the character onto the variable
					name1 += static_cast<char>(event.text.unicode);
					text.setString(name1);

				}
				//Player Two Name
				else if (event.text.unicode == '\b' && stage == 2) {
					if (name2.size() > 0) {
						name2.erase(name2.size() - 1, 1);
						text.setString(name2);
					}
				}
				else if (event.text.unicode < 128 && name2.size() < 5 && stage == 2)
				{
					name2 += static_cast<char>(event.text.unicode);
					text.setString(name2);
				}
				//Player One HP
				else if (event.text.unicode == '\b' && stage == 3) {
					if (hitPercStr.size() > 0) {
						hitPercStr.erase(hitPercStr.size() - 1, 1);
						text.setString(hitPercStr);
					}
				}
				else if (event.text.unicode < 128 && hitPercStr.size() < 2 && stage == 3)
				{
					hitPercStr += static_cast<char>(event.text.unicode);
					text.setString(hitPercStr);
				}
				//Player Two HP
				else if (event.text.unicode == '\b' && stage == 4) {
					if (hitPercStr.size() > 0) {
						hitPercStr.erase(hitPercStr.size() - 1, 1);
						text.setString(hitPercStr);
					}
				}
				else if (event.text.unicode < 128 && hitPercStr.size() < 2 && stage == 4)
				{
					hitPercStr += static_cast<char>(event.text.unicode);
					text.setString(hitPercStr);
				}
				//WC Number
				else if (event.text.unicode == '\b' && stage == 7) {
					if (wcNumStr.size() > 0) {
						wcNumStr.erase(wcNumStr.size() - 1, 1);
						text.setString(wcNumStr);
					}
				}
				else if (event.text.unicode < 128 && wcNumStr.size() < 3 && stage == 7)
				{
					wcNumStr += static_cast<char>(event.text.unicode);
					text.setString(wcNumStr);
				}
			}

			//if the enter key is pressed
			if ((event.type == sf::Event::KeyReleased))
			{
				//Enter after player one name
				if (event.key.code == sf::Keyboard::Enter && stage == 1)
				{
					//if a name has been chosen
					if (name1.size() > 0)
					{
						//increase the stage
						stage++;
						//clear the text on screen where the user has been typing
						text.setString("");
						//show appropriate message according to the gameMode
						if (gameMode == 0)
						{
							startMessage.setString("Name of player 2:");
						}
						else if (gameMode == 1) {
							startMessage.setString("Name of computer:");
						}
						else {
							startMessage.setString("Name of computer 2:");
						}
						s_select.play();
					}
				}
				//Enter after player two name
				else if (event.key.code == sf::Keyboard::Enter && stage == 2)
				{
					if (name2.size() > 0) {
						stage++;
						text.setString("");

						if (gameMode == 0)
						{
							startMessage.setString("Accuracy for Player 1:\n>20 and <85");
						}
						else if (gameMode == 1) {
							startMessage.setString("Accuracy of player:\n>20 and <85");
						}
						else {
							startMessage.setString("Accuracy of computer 1:\n>20 and <85");
						}
						s_select.play();
					}
				}
				//Enter after player one HP
				else if (event.key.code == sf::Keyboard::Enter && stage == 3)
				{
					if (hitPercStr.size() > 0 && isNum(hitPercStr, 0)) //make sure it is a number and within appropriate values
					{
						hitPerc = std::stoi(hitPercStr); //set int of the string to int variable
						stage++;
						text.setString("");
						if (gameMode == 0)
						{
							startMessage.setString("Accuracy for Player 2:\n>20 and <85");
						}
						else if (gameMode == 1) {
							startMessage.setString("Accuracy of computer:\n>20 and <85");
						}
						else {
							startMessage.setString("Accuracy of computer 2:\n>20 and <85");
						}
						hitPercStr = "";
						s_select.play();
					}
				}
				//Enter after player two accuracy
				else if (event.key.code == sf::Keyboard::Enter && stage == 4)
				{
					if (hitPercStr.size() > 0 && isNum(hitPercStr, 0)) {
						hitPerc2 = std::stoi(hitPercStr);
						text.setString("");
						if (gameMode == 0)
						{
							startMessage.setString("Number of World\nChampionships:");
							stage = 7;
						}
						else if (gameMode == 1) {
							startMessage.setString("Aiming method of computer:\n(1)simple\n(2)advanced");
							stage++;
						}
						else {
							startMessage.setString("Aiming method of computer 1:\n(1)simple\n(2)advanced");
							stage++;
						}
						s_select.play();
					}
				}
				//Enter after WC number
				else if (event.key.code == sf::Keyboard::Enter && stage == 7)
				{
					if (wcNumStr.size() > 0 && isNum(wcNumStr, 1)) {
						wcNum = std::stoi(wcNumStr);
						stage++;
						text.setString("");
						startMessage.setString("Thank you :)");
						done = true;
						s_select.play();
					}
				}
			}
		}
		window.clear();
		window.draw(s_background);
		window.draw(backing);
		window.draw(startMessage);
		window.draw(text);
		window.draw(title);
		window.display();
	}
	return gameMode;
}

int interactive::play(int& typeOfShot, int dartNum, int playerTurn) {
	int aiming;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					//get what the user is aiming at with their mouse
					aiming = throwIt(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, typeOfShot);
					return aiming;
				}
			}
		}
		window.clear();
		window.draw(s_background);
		window.draw(s_dartboard);
		window.draw(s_scoreboard);
		window.draw(playerOneName);
		window.draw(playerTwoName);
		window.draw(counter);
		window.draw(scoreOne);
		window.draw(scoreTwo);
		window.draw(scoreTotalOne);
		window.draw(scoreTotalTwo);
		window.draw(setsGamesWonOne);
		window.draw(setsGamesWonTwo);

		if (dartNum == -1) //just displays the screen
		{
			window.display();
			Sleep(250 * sleepLength);
			return 0;
		}
		else if (dartNum == 1) //display the first marker
		{
			window.draw(hitMarker);
		}
		else if (dartNum == 2) //display the first and marker
		{
			window.draw(hitMarker);
			window.draw(hitMarker2);
		}

		//if the user is actually playing, display the dart
		if (dartNum != -1)
		{
			if (playerTurn == 1)
			{
				window.draw(s_dartRed);
				s_dartRed.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			}
			else {
				window.draw(s_dartBlue);
				s_dartBlue.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			}
		}
		window.display();
	}
}

//winner screen (shows messages)
void interactive::winner(int gameMode){
	bool done = false;
	s_congrats.play();
	while (window.isOpen() && done == false)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					done = true; //once the user presses enter, they are done and it moves on
				}
			}
		}
		window.clear();
		window.draw(s_background);
		window.draw(s_dartboard);
		window.draw(s_scoreboard);
		window.draw(playerOneName);
		window.draw(playerTwoName);
		window.draw(counter);
		window.draw(scoreOne);
		window.draw(scoreTwo);
		window.draw(scoreTotalOne);
		window.draw(scoreTotalTwo);
		window.draw(winnerBack);
		window.draw(winnert);
		window.draw(setsGamesWonOne);
		window.draw(setsGamesWonTwo);
		window.display();

		if (gameMode == 2)
		{
			Sleep(1000 * sleepLength);
			done = true;
		}
	}
}

//result screen
bool interactive::result() {
	s_congrats.play();
	//title
	sf::Text title;
	title.setFont(font);
	title.setString("RESULTS");
	title.setCharacterSize(50);
	title.setPosition(510, 50);
	title.setFillColor(sf::Color(255, 51, 0));
	title.setStyle(sf::Text::Bold);
	title.setOutlineThickness(5);
	title.setOutlineColor(sf::Color(0, 0, 0));

	//results message
	sf::Text resMess;
	resMess.setFont(font);
	resMess.setCharacterSize(21);
	resMess.setPosition(380, 650);
	resMess.setFillColor(sf::Color::Blue);
	resMess.setOutlineThickness(1);
	resMess.setOutlineColor(sf::Color::White);
	resMess.setStyle(sf::Text::Bold);
	resMess.setString("Press enter to go back to menu and Esc to exit");

	sf::RectangleShape backing;
	backing.setPosition(380, 200);
	backing.setSize(sf::Vector2f(500, 400));
	backing.setFillColor(sf::Color(255, 255, 255));
	backing.setOutlineThickness(5);
	backing.setOutlineColor(sf::Color(0, 0, 0));
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					s_select.play();
					return true;
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					s_select.play();
					return false;
				}
			}
		}
		window.clear();
		window.draw(s_background);
		window.draw(backing);
		window.draw(freq);
		window.draw(title);
		window.draw(resMess);
		window.display();
	}
}

//used to decide who starts
int interactive::startingPlayer(int hpOne, int hpTwo, string oneName, string twoName, int gameMode) {
	float rOne; //radius - player one
	float rTwo; //radius - player two
	float oneX; //x - player one
	float oneY; //y - player one
	float twoX; //x - player two
	float twoY; //y - player two

	do {
		do {
			//generate a random number for the x coord and y cood 
			oneX = rand() % (639 - (hpOne * 2) - (77 + (hpOne * 2)) + 1) + (77 + (hpOne * 2)); //(maximum 639 and minimum 77 with the added help of their accuracy (higher is better as it hones it into the centre))
			oneY = rand() % (638 - (hpOne * 2) - (76 + (hpOne * 2)) + 1) + (76 + (hpOne * 2));  //(maximum 638 and minimum 76)
			rOne = radius(oneX, oneY);
		} while (rOne > 281); //if the radius is outside the determined circle, repeat 

		do {
			twoX = rand() % (639 - (hpTwo * 2) - (77 + (hpTwo * 2)) + 1) + (77 + (hpTwo * 2));
			twoY = rand() % (638 - (hpTwo * 2) - (76 + (hpTwo * 2)) + 1) + (76 + (hpTwo * 2));
			rTwo = radius(twoX, twoY);
		} while (rTwo > 281);
	} while (rOne == rTwo); //repeat the process if the two radii are equal

	//this is a message displayed to the user
	starting.setString("Choosing starting player\nPlayer closest to bull starts");
	
	//display to the window
	window.clear();
	window.draw(s_background);
	window.draw(s_dartboard);
	window.draw(starting);
	window.display();

	//pause for effect
	s_dart_noise.play();
	Sleep(500 * sleepLength);
	s_dart_noise.play();

	int starter;
	if (rOne < rTwo) //if player one is closer
	{
		starting.setString("Choosing starting player\nPlayer closest to bull starts\n\n" + oneName + " (Red) was closest.\n\nPress enter");
		starter = 1;
	}
	else { //if player two is closer
		starting.setString("Choosing starting player\nPlayer closest to bull starts\n\n" + twoName + " (Blue) was closest.\n\nPress enter");
		starter = 2;
	}

	//set the hitmarker positions to where they were thrown (minus 5 because the circles have a radius of 5)
	hitMarkerRed.setPosition(oneX - 5, oneY - 5);
	hitMarkerBlue.setPosition(twoX - 5, twoY - 5);

	bool done = false;
	while (window.isOpen() && done == false)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					done = true; //when the user presses enter, the loop will end and it will move past this
					s_select.play();
				}
			}
		}
		window.clear();
		window.draw(s_background);
		window.draw(s_dartboard);
		window.draw(starting);
		window.draw(hitMarkerRed);
		window.draw(hitMarkerBlue);
		window.display();
		if (gameMode == 2)
		{
			Sleep(1000 * sleepLength);
			done = true;
		}
	}
	return starter; //returns which player is starting
}