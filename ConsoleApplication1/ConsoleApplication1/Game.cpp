#include "Game.h"

//Private Functions
void Game::initializeVariables()
{
	//Overall
	debugvalue = 0;
	step = 1;
	start = false;
	over = false;
	pause = false;
	win = false;

	//Start Screen Sprite
	if (!texture.loadFromFile("src/StartScreen.png"))
	{
		std::cout << "Error Sprite";
		system("pause:");
	}
	StartScreenSprite.setTexture(texture);
	StartScreenSprite.scale(0.5, 0.5);
	StartScreenSprite.setOrigin(StartScreenSprite.getTexture()->getSize().x / 2, StartScreenSprite.getTexture()->getSize().y / 2);
	StartScreenSprite.setPosition(300, 400); //windowwidth

	//Pause Screen Sprite
	if (!texture2.loadFromFile("src/PauseScreen.png"))
	{
		std::cout << "Error Sprite";
		system("pause:");
	}
	PauseScreen.setTexture(texture2);
	PauseScreen.scale(0.5, 0.5);
	PauseScreen.setOrigin(PauseScreen.getTexture()->getSize().x / 2, PauseScreen.getTexture()->getSize().y / 2);
	PauseScreen.setPosition(300, 400); //windowwidth

	//Lose Screen Sprite
	if (!texture3.loadFromFile("src/LossScreen.png"))
	{
		std::cout << "Error Sprite!";
		system("pause:");
	}

	LossScreen.setTexture(texture3);
	LossScreen.scale(0.5, 0.5);
	LossScreen.setOrigin(LossScreen.getTexture()->getSize().x / 2, LossScreen.getTexture()->getSize().y / 2);
	LossScreen.setPosition(300, 400); //windowwidth

	//Lose Screen Sprite
	if (!texture4.loadFromFile("src/WinScreen.png"))
	{
		std::cout << "Error Sprite!";
		system("pause:");
	}
	VictoryScreen.setTexture(texture4);
	VictoryScreen.scale(0.5, 0.5);
	VictoryScreen.setOrigin(VictoryScreen.getTexture()->getSize().x / 2, VictoryScreen.getTexture()->getSize().y / 2);
	VictoryScreen.setPosition(300, 400); //windowwidth

	//Heart Sprite
	if (!heart_texture.loadFromFile("src/heart_sprite.png"))
	{
		std::cout << "Error Sprite!";
		system("pause:");
	}

	for (int i = 0; i < 5; i++)
	{
		heart_sprite[i].setTexture(heart_texture);
		heart_sprite[i].scale(0.5, 0.5);
		heart_sprite[i].setOrigin(heart_sprite[i].getTexture()->getSize().x / 2, heart_sprite[i].getTexture()->getSize().y / 2);
		heart_sprite[i].setPosition(300 + 43 * i, 780); //windowwidth
	}

	//Score Keeping
	yourgoals = 0;
	hisgoals = 0;

	//Window Setup

	//windowwidth = window->getSize().x;
	//windowheight = window->getSize().y;
	windowwidth = 600;
	windowheight = 800;
	this->window = nullptr;

	// windowwidth = window->getSize().x;
	// windowheight = window->getSize().y;

	//Font
	if (!font.loadFromFile("src/arial.ttf"))
	{
		std::cout << "Errrrrrror bro!";
		system("pause:");
	}

	//Text
	curr.setFont(font);
	curr.setCharacterSize(20);
	curr.setFillColor(sf::Color::White);
	curr2.setFont(font);
	curr2.setCharacterSize(20);
	curr2.setFillColor(sf::Color::White);

	//Color
	fieldcolor = sf::Color(36, 115, 57, 255);
	bordercolor = sf::Color(54, 33, 18, 255);
	plankcolor = sf::Color(255, 255, 255, 255);

	//Field Setup
	y_spacer = 0.05 * windowheight;
	fieldheight = 0.9 * windowheight;
	x_spacer = 0.05 * windowwidth;
	fieldwidth = 0.9 * windowwidth;

	field.setSize(sf::Vector2f(.9 * windowwidth, .9 * windowheight));
	field.setFillColor(fieldcolor);
	field.setOrigin(field.getSize().x / 2, field.getSize().y / 2);
	field.setPosition((windowwidth / 2), (windowheight / 2));

	//Plank Setup
	plank1_y = fieldheight * 0.8 + y_spacer;
	plankheight = 10;
	plankwidth = 70;
	plank1_x = windowwidth / 2;
	plankspeed = 0.2;

	plank1.setSize(sf::Vector2f(plankwidth, plankheight));
	plank1.setFillColor(plankcolor);
	plank1.setOrigin(plankwidth / 2, plankheight / 2);
	plank1.setPosition(plank1_x, plank1_y);

	//BrickPile Setup
	gamePile.setUp(windowwidth, windowheight, x_spacer, y_spacer, fieldwidth, fieldheight);
	gamePile.makeBricks();
	bricksleft = gamePile.startingbricknumber;
	previoustouch2 = false;

	//Ball Setup
	ballsize = 7; //radius btw
	ball_x = windowwidth / 2;
	ball_y = windowheight / 2;
	srand(100 * time(NULL));

	initialdirection = (rand() + 17000) % 62830; //tau * 10000
	mod = .2;									 //initial speed modifier
	previoustouch = false;

	ball.setRadius(ballsize);
	ball.setFillColor(plankcolor);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
	ball.setPosition(windowwidth / 2, windowheight / 2);

	ballspeed_x = sin(initialdirection / 10000) * mod;
	ballspeed_y = cos(initialdirection / 10000) * mod;

	//Collisions (I'm not sure if it really even needs initialized, but it won't hurt)
	ballboundingBox = ball.getGlobalBounds();
	plank1boundingbox = plank1.getGlobalBounds();
}

void Game::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 600;

	this->window = new sf::RenderWindow(this->videoMode, "PinBall Rebuild");
}

void Game::setConditions()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //HERE
	{
		start = true;
		pause = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) //HERE
	{
		pause = true;
	}

	if (lives < 0) //HERE
	{
		over = true;
	}

	if (bricksleft < 1) //HERE
	{
		win = true;
		over = true;
	}
}

void Game::ballCollisions()
{
	sf::FloatRect ballboundingBox = ball.getGlobalBounds();
	sf::FloatRect plank1boundingBox = plank1.getGlobalBounds();

	//Ball and plank collision
	if ((ballboundingBox.intersects(plank1boundingBox)))
	{
		if (previoustouch == false)
		{
			//This code guarantees the ball goes upward after collision, at an angle dependent on contact position.
			//The code also guarentees the ball will remain at the same speed (unless speedup is called)
			float ballspeed_mag = sqrt(ballspeed_x * ballspeed_x + ballspeed_y * ballspeed_y); //magnitude
			float difx = ball_x - plank1.getPosition().x;

			//ballspeed_x = sin((3.14159265 * 2 * difx) / plankwidth) * ballspeed_mag;  //any continuous function f[2*difx/(plankwidth)] whose image is f[-1,1] = [-1,1]
			//on the interval [-1,1], requiring f(-1)=-1 and f(1)=1. sin(pi * x) worked,
			//but I like y=x better.
			ballspeed_x = ((difx * 2) / (plankwidth + 2 * ball.getRadius())) * ballspeed_mag;
			debugvalue = abs(((difx * 2) / plankwidth));
			float bllspd_y2 = abs(ballspeed_mag * ballspeed_mag - ballspeed_x * ballspeed_x);
			ballspeed_y = -sqrt(bllspd_y2);

			previoustouch = true;
			//speedup(speedincrease, ballspeed_x, ballspeed_y);
		}
	}
	else
	{
		previoustouch = false;
	}

	//Ball Hits a Brick
	for (int j = 0; j < NUMDOWN; j++)
	{
		for (int i = 0; i < NUMACROSS; i++)
		{
			if ((gamePile.brickBoundingBox[i][j].intersects(ballboundingBox)) && (gamePile.pile[i][j].isBroken() == false))
			{
				if (previoustouch2 == false)
				{
					//This section deals with the breaking of the blocks
					previoustouch2 = true;
					gamePile.pile[i][j].hitpoints--;
					if (gamePile.pile[i][j].hitpoints == 0)
					{
						bricksleft--;
					}

					//This section consists of the variables to determine which velocity axis needs to be negated

					//bool yCompFlipped = false; //true if we're negating the y component of the velocity
					sf::Vector2f diff = ball.getPosition() - gamePile.pile[i][j].rect.getPosition(); //the difference between the center of the ball and center of the brick
					bool abovebelow = (abs(diff.y) > (gamePile.pile[i][j].rect.getSize().y) / 2); //true if center of ball is above or below brick (not next to)
					float slope = gamePile.pile[i][j].rect.getSize().y / gamePile.pile[i][j].rect.getSize().x; //positive slope of diagonal
					float posLine = diff.x * slope; //y-value of the positive diagonal line, evaluated at the x-value of the ball
					float negLine = diff.x * -slope;//y-value of the negative diagonal line, evaluated at the x-value of the ball
					bool abovePos = diff.y > posLine;
					bool aboveNeg = diff.y > negLine;

					if ((abovebelow && abovePos && aboveNeg) || (abovebelow && !abovePos && !aboveNeg))
					{
						ballspeed_y = -ballspeed_y;
					}
					else
					{
						ballspeed_x = -ballspeed_x;
					}
				}
				else
				previoustouch2 = false;
			}
		}
	}

	//Hitting sides
	if (((ball_x + ballsize) > (fieldwidth + x_spacer)) || ((ball_x - ballsize) < (x_spacer)))
	{
		ballspeed_x = -ballspeed_x;
	}
	if ((ball_y - ballsize) < (y_spacer))
	{
		ballspeed_y = -ballspeed_y;
	}
	if ((ball_y + ballsize) > (fieldheight + y_spacer))
	{
		ballspeed_y = -ballspeed_y;
		lives--;
		// if (ballspeed_y > 0)
		// {
		// 	lives--;
		// }
	}
}
//Constructors /Destructors
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
bool Game::running() const
{
	return this->window->isOpen();
}

//Functions
void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	pollEvents();
	setConditions();

	if ((start == true) && (over == false) && (pause == false))
	{ //main if statement begins

		//Move Plank
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (plank1_x >= (x_spacer + plankwidth / 2))
			{
				plank1_x = plank1_x - step * plankspeed;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (plank1_x <= fieldwidth + x_spacer - plankwidth / 2)
			{
				plank1_x = plank1_x + step * plankspeed;
			}
		}

		//Ball Collisions
		ballCollisions();

		//Updating Positions
		plank1.setPosition(plank1_x, plank1_y);
		ball_x = ball_x + ballspeed_x * step;
		ball_y = ball_y + ballspeed_y * step;
		ball.setPosition(ball_x, ball_y);
	}
}

void Game::render()
{
	this->window->clear(sf::Color::Black);

	window->draw(field);
	window->draw(plank1);
	window->draw(ball);
	if (start == false)
	{
		window->draw(StartScreenSprite);
	}

	if ((start == true) && (pause == true))
	{
		window->draw(PauseScreen);
	}

	if (over == true)
	{
		if (win)
		{
			window->draw(VictoryScreen);
		}
		else
		{
			window->draw(LossScreen);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			//call function to reset stuff. Maybe setUp? idk worth trying first
			over = false;
			win = false;
			for (int i = 0; i < NUMACROSS; i++)
			{
				for (int j = 0; j < NUMDOWN; j++)
				{
					gamePile.pile[i][j].hitpoints = 1;
					gamePile.pile[i][j].broken = false;
				}
			}
			bricksleft = gamePile.startingbricknumber;
			lives = 4;
			ball.setPosition(sf::Vector2f(windowwidth / 2, windowheight / 2));
		}
	}

	gamePile.printBricks(window);

	curr.setPosition(100, 0);
	curr.setString(std::to_string(bricksleft));
	curr2.setPosition(200, 0);
	curr2.setString(std::to_string(gamePile.pile[1][1].rect.getSize().x));

	window->draw(curr);
	window->draw(curr2);

	for (int i = 0; i < lives; i++)
	{
		window->draw(heart_sprite[i]);
	}
	//Draw game objects
	window->display();
}