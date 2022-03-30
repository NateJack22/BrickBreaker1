#ifndef BRICKPILE_H
#define BRICKPILE_H

#include "aBrick.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

class BrickPile
{
private:
	//Private Variables
	const int NUMACROSS = 25;
	const int NUMDOWN = 10;
	float windowwidth, windowheight, x_spacer, y_spacer, fieldwidth, fieldheight;
	sf::Texture brick_a_texture;
	sf::Texture brick_b_texture;

public:
	//Constructor and Destructor
	BrickPile();
	~BrickPile();

	//Methods
	void makeBricks();
	void setUp(float Windowwidth, float Windowheight, float Fieldwidth, float Fieldheight, float X_spacer, float Y_spacer);
	void printBricks(sf::RenderWindow* window);
	void readSeed(const string seed);

	//Public Variables
	aBrick pile[25][10]; //someday will be a 1-d vector
	sf::FloatRect brickBoundingBox[25][10];
	int startingbricknumber = 0;
};

#endif