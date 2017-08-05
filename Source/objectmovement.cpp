#include "sdlfunctions.h"
#include "ppfunctions.h"

void PP::paddle_motion(SDL_Rect &paddle, int movement)
{
	if (!movement)
	{
		paddle.y += screenH * 1 / 40;

		if (paddle.y + paddle.h > borders[0].y + borders[0].h)
		{
			paddle.y -= screenH * 1 / 40;
		}
	}

	else if (movement)
	{
		paddle.y -= screenH * 1 / 40;

		if (paddle.y < borders[0].y)
		{
			paddle.y += screenH * 1 / 40;
		}
	}
}


void PP::computer_paddle_motion(string side)
{
	int diff_l;
	int diff_r;

	diff_l = (3 * 2) + ((l_cpu_difficulty - 1) * 2);
	diff_r = (3 * 2) + ((r_cpu_difficulty - 1) * 2);

	if (side == "left")
	{
		if ((ball_rect.x >= l_paddle_rect.x + l_paddle_rect.w) && (l_paddle_rect.x + l_paddle_rect.w + (ball_rect.w * diff_l) >= ball_rect.x))
		{
			if (l_paddle_rect.y >= ball_rect.y)
			{
				l_paddle_rect.y -= screenH * 1 / 40;

				if (l_paddle_rect.y < borders[0].y)
				{
					l_paddle_rect.y += screenH * 1 / 40;
				}
			}

			if (l_paddle_rect.y + l_paddle_rect.h <= ball_rect.y + ball_rect.h)
			{
				l_paddle_rect.y += screenH * 1 / 40;

				if (l_paddle_rect.y + l_paddle_rect.h > borders[0].y + borders[0].h)
				{
					l_paddle_rect.y -= screenH * 1 / 40;
				}
			}
		}
	}

	if (side == "right")
	{
		if ((ball_rect.x <= r_paddle_rect.x) && (r_paddle_rect.x - (ball_rect.w * diff_r) <= ball_rect.x))
		{
			if (r_paddle_rect.y >= ball_rect.y)
			{
				r_paddle_rect.y -= screenH * 1 / 40;

				if (r_paddle_rect.y < borders[0].y)
				{
					r_paddle_rect.y += screenH * 1 / 40;
				}
			}

			if (r_paddle_rect.y + l_paddle_rect.h <= ball_rect.y + ball_rect.h)
			{
				r_paddle_rect.y += screenH * 1 / 40;

				if (r_paddle_rect.y + l_paddle_rect.h > borders[0].y + borders[0].h)
				{
					r_paddle_rect.y -= screenH * 1 / 40;
				}
			}
		}
	}
}


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


int PP::deflection()
{
	SDL_Rect intersection;

	int cont = 0;

	if (SDL_IntersectRect(&ball_rect, &borders[1], &intersection))
	{
		direction += 3;
		if ((direction != 6) || (direction != 13))
		{
			lock = false;
		}

		else
		{
			lock = true;
		}
	}

	if (SDL_IntersectRect(&ball_rect, &borders[3], &intersection))
	{
		direction -= 3;
		if ((direction != 3) || (direction != 10))
		{
			lock = false;
		}

		else
		{
			lock = true;
		}
	}

	if (SDL_IntersectRect(&ball_rect, &l_paddle_rect, &intersection))
	{
		direction = rand() % 7 + 1;
		ball_rect.x += intersection.w;
		lock = false;
		rally_counter++;
	}

	if (SDL_IntersectRect(&ball_rect, &r_paddle_rect, &intersection))
	{
		direction = rand() % 7 + 1;
		direction += 7;
		ball_rect.x -= intersection.w;
		lock = false;
		rally_counter++;
	}

	if (SDL_IntersectRect(&ball_rect, &borders[0], &intersection))
	{
		cont = 1;
		player_points[1]++;
	}

	if (SDL_IntersectRect(&ball_rect, &borders[2], &intersection))
	{
		cont = 2;
		player_points[0]++;
	}

	return cont;
}
