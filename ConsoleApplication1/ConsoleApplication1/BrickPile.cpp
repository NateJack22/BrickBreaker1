#include "BrickPile.h"

BrickPile::BrickPile()
{
	readSeed("joe");
}

BrickPile::~BrickPile()
{
}

//This method will setup each brick in the array of bricks
//ALWAYS CALL SETSIZES FIRST
void BrickPile::makeBricks()
{
	startingbricknumber = 0;
	float brickwidth = fieldwidth / NUMACROSS;
	float brickheight = fieldheight / (NUMDOWN * 5); //The 10 is from the third of the screen bricks take up

	for (int i = 0; i < NUMACROSS; i++)
	{
		for (int j = 0; j < NUMDOWN; j++)
		{
			pile[i][j].rect.setSize(sf::Vector2f(brickwidth, brickheight));
			pile[i][j].rect.setOrigin(sf::Vector2f(brickwidth / 2, brickwidth / 2));
			pile[i][j].rect.setPosition(x_spacer + brickwidth * (i + .5), y_spacer + brickheight * (j + .5));
			//pile[i][j].rect.setFillColor(sf::Color(255 - 30 * j* i, 70 + 40 * i, 70 + 40 * i * j, 255));
			brickBoundingBox[i][j] = pile[i][j].rect.getGlobalBounds();

			pile[i][j].type = 'a';

			if ((i + j) % 3 + j % 2 == 0)
			{
				pile[i][j].type = 'b';
				pile[i][j].hitpoints = 2;
			}

			if (pile[i][j].type == 'a')
			{
				pile[i][j].rect.setTexture(&brick_a_texture);
			}
			if (pile[i][j].type == 'b')
			{
				pile[i][j].rect.setTexture(&brick_b_texture);
			}

			if ((j < 3) || (j == 5) || (i <= 1) || (i >= 23))
			{
				pile[i][j].hitpoints = pile[i][j].hitpoints - 10;
			}
			else
			{
				startingbricknumber++;
			}
		}
	}
}

void BrickPile::setUp(float Windowwidth, float Windowheight, float X_spacer, float Y_spacer, float Fieldwidth, float Fieldheight)
{
	windowwidth = Windowwidth;
	windowheight = Windowheight;
	x_spacer = X_spacer;
	y_spacer = Y_spacer;
	fieldheight = Fieldheight;
	fieldwidth = Fieldwidth;

	if (!brick_a_texture.loadFromFile("src/brick_a_texture.png"))
	{
		std::cout << "Error Sprite";
		system("pause:");
	}

	if (!brick_b_texture.loadFromFile("src/brick_b_texture.png"))
	{
		std::cout << "Error Sprite";
		system("pause:");
	}
}

void BrickPile::printBricks(sf::RenderWindow* window)
{
	for (int j = 0; j < NUMDOWN; j++)
	{
		for (int i = 0; i < NUMACROSS; i++)
		{
			if (!pile[i][j].isBroken())
			{
				window->draw(pile[i][j].rect);
				//block[i].printBrick(window,100,100);
			}
		}
	}
}

void BrickPile::readSeed(const string seed) //will implement later
{
	string temp;
	if (seed == "1")
	{
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				temp = seed;
			}
		}
	}
}