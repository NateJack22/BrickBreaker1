#pragma once

//#include "Brick.hpp"
#include "BrickPile.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <time.h>
//#include <Randomizer.hpp>

class Game
{
private:
	//Overall Variables:
	float step; //ye olde delta t
	bool start, over, pause, win;
	sf::Texture texture;
	sf::Texture texture2;
	sf::Texture texture3;
	sf::Texture texture4;
	sf::Sprite StartScreenSprite;
	sf::Sprite PauseScreen;
	sf::Sprite LossScreen;
	sf::Sprite VictoryScreen;
	float debugvalue;
	int level = 0;

	sf::Texture heart_texture;
	sf::Sprite heart_sprite[5];

	int lives = 5;

	//Score Keeping
	int yourgoals, hisgoals, bricksleft;

	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	float windowwidth;
	float windowheight;

	//Fonts
	sf::Font font;

	//Text
	sf::Text curr;
	sf::Text curr2;
	//Colors
	sf::Color fieldcolor;
	sf::Color bordercolor;
	sf::Color plankcolor;

	//Field
	float y_spacer, x_spacer, fieldheight, fieldwidth;
	sf::RectangleShape field;

	//Plank Stuff
	float plank1_y;
	int plankheight;
	int plankwidth;
	float plank1_x;
	float plankspeed = 0.1;
	sf::RectangleShape plank1;

	//Brick Array Someday
	//Brick block;
	int NUMACROSS = 25; //These two need changed in BrickPile as well
	int NUMDOWN = 10;	//INCLUDING THE pile vector

	float brickwidth;
	float brickheight;
	bool previoustouch2;
	BrickPile gamePile;

	//Ball
	float ballsize, ball_x, ball_y, initialdirection;
	float mod, ballspeed_x, ballspeed_y;
	bool previoustouch;
	sf::CircleShape ball;

	//Collisions
	sf::FloatRect ballboundingBox;
	sf::FloatRect plank1boundingbox;

	//Methods:
	void initializeVariables();
	void initWindow();

	//Helper functions
	void setConditions();
	void ballCollisions();

public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Accessors
	bool running() const;

	//Methods
	void pollEvents();
	void update();
	void render();
};