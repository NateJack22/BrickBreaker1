#include "aBrick.h"

aBrick::aBrick()
{
}

aBrick::~aBrick()
{
}

bool aBrick::isBroken()
{
	if (hitpoints <= 0)
	{
		broken = true;
	}
	return broken;
}
