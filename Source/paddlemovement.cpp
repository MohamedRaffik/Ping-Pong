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
