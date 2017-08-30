#include "sdlfunctions.h"
#include "ppfunctions.h"


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
