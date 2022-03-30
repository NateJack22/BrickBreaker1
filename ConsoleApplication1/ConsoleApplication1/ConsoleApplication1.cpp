//#define _USE_MATH_DEFINES

//#include "Brick.hpp"
#include "Game.h"
//#include "Levels.txt"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	//Init Game Engine
	Game game;

	//Game Loop
	while (game.running())
	{
		//Update
		game.update();

		//Render
		game.render();
	}

	return 0;
}