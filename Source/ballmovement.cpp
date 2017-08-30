#include "sdlfunctions.h"
#include "ppfunctions.h"

void PP::ball_motion()
{
	srand((unsigned int)time(NULL));

	if (lock_counter % 2 != 0)
	{
		lock = false;
	}

	int speedY = screenH * 1 / 80;
	int speedX = screenW * 1 / 80;

	if (direction < 0)
	{
		direction = rand() % 14 + 1;
	}

	if (direction == 1)             //E
	{
		ball_rect.x += speedX;
	}

	else if (direction == 2)       //NE
	{
		ball_rect.x += speedX;
		ball_rect.y -= speedY;
	}

	else if (direction == 3)       //NNE
	{
		if (!lock)
		{
			ball_rect.x += speedX;
			lock = true;
		}

		ball_rect.y -= speedY;
	}

	else if (direction == 4)      //NEE
	{
		ball_rect.x += speedX;

		if (!lock)
		{
			ball_rect.y -= speedY;
			lock = true;
		}
	}

	else if (direction == 5)      //SE
	{
		ball_rect.x += speedX;
		ball_rect.y += speedY;
	}

	else if (direction == 6)      //SSE
	{
		if (!lock)
		{
			ball_rect.x += speedX;
			lock = true;
		}

		ball_rect.y += speedY;
	}

	else if (direction == 7)      //SEE
	{
		ball_rect.x += speedX;

		if (!lock)
		{
			ball_rect.y += speedY;
			lock = true;
		}
	}

	else if (direction == 8)      //W
	{
		ball_rect.x -= speedX;
	}

	else if (direction == 9)      //NW
	{
		ball_rect.x -= speedX;
		ball_rect.y -= speedY;
	}

	else if (direction == 10)     //NNW
	{
		if (!lock)
		{
			ball_rect.x -= speedX;
			lock = true;
		}

		ball_rect.y -= speedY;
	}

	else if (direction == 11)     //NWW
	{
		ball_rect.x -= speedX;

		if (!lock)
		{
			ball_rect.y -= speedY;
			lock = true;
		}
	}

	else if (direction == 12)     //SW
	{
		ball_rect.x -= speedX;
		ball_rect.y += speedY;
	}

	else if (direction == 13)     //SSW
	{
		if (!lock)
		{
			ball_rect.x -= speedX;
			lock = true;
		}

		ball_rect.y += speedY;
	}

	else if (direction == 14)    //SWW
	{
		ball_rect.x -= speedX;

		if (!lock)
		{
			ball_rect.y += speedY;
		}
	}

	lock_counter++;
}