#ifndef aBRICK_H
#define aBRICK_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class aBrick
{
public:
	aBrick();
	~aBrick();
	void setUp(const float rectWidth, const float rectHeight, sf::Color color);
	void place(const float xpos, const float ypos);

	sf::RectangleShape rect;
	bool isBroken();
	int hitpoints = 1;
	char type;
	bool broken = false;

private:
	float rectWidth;
	float rectHeight;
	//const int BRICKACROSS = 25;
	//const int BRICKDOWN = 10;
	sf::Color rectColor;
};
#endif