#include "ppfunctions.h"
#include "sdlfunctions.h"


void PP::init_variables()
{
	borders[0] = { screenW * 1 / 40 - screenW * 1 / 160, screenH * 5 / 20,              screenW * 1 / 160, screenH * 29 / 40 };
	borders[1] = { screenW * 1 / 40,                   borders[0].y - borders[0].w, screenW * 38 / 40, borders[0].w };
	borders[2] = { borders[1].x + borders[1].w,      screenH * 5 / 20,              screenW * 1 / 160, screenH * 29 / 40 };
	borders[3] = { screenW * 1 / 40,                   screenH * 39 / 40,             screenW * 38 / 40, borders[1].h };

	r_paddle_rect = { borders[2].x - screenW * 1 / 40,                  screenH * 19 / 40, screenW * 1 / 80, screenH * 8 / 40 };
	l_paddle_rect = { (borders[0].x + borders[0].w) + screenW * 1 / 80, screenH * 19 / 40, screenW * 1 / 80, screenH * 8 / 40 };

	ball_rect = { borders[1].x + (borders[1].w / 2), borders[0].y + (borders[0].h / 2), screenW * 1 / 80, screenW * 1 / 80 };
	ball_rect.x -= ball_rect.w / 2;
	ball_rect.y -= ball_rect.h / 2;

	player_points[0] = 0;
	player_points[1] = 0;

	direction = -1;

	lock_counter = 0;

	rally_counter = 0;

	lock = false;

	srand((unsigned int)time(NULL));

	l_cpu_difficulty = rand() % 3 + 1;

	r_cpu_difficulty = rand() % 3 + 1;
}



void PP::reset()
{
	r_paddle_rect = { borders[2].x - screenW * 1 / 40, screenH * 19 / 40, screenW * 1 / 80, screenH * 8 / 40 };
	l_paddle_rect = { (borders[0].x + borders[0].w) + screenW * 1 / 80, screenH * 19 / 40, screenW * 1 / 80, screenH * 8 / 40 };

	ball_rect = { borders[1].x + (borders[1].w / 2), borders[0].y + (borders[0].h / 2), screenW * 1 / 80, screenW * 1 / 80 };
	ball_rect.x -= ball_rect.w / 2;
	ball_rect.y -= ball_rect.h / 2;

	direction = -1;

	lock_counter = 0;

	rally_counter = 0;

	lock = false;

	srand((unsigned)time(NULL));

	l_cpu_difficulty = rand() % 3 + 1;
	r_cpu_difficulty = rand() % 3 + 1;
}


bool PP::game_over()
{
	if ((player_points[0] == 10) || (player_points[1] == 10))
	{
		load_background();

		string title_text = "Game Over";
		string player_win_text;
		string winner_text = "is the Winner";

		if (player_points[0] == 10)
		{
			player_win_text = "Left Paddle";
		}

		else if (player_points[1] == 10)
		{
			player_win_text = "Right Paddle";
		}

		SDL_Rect title_rect = { screenW * 2 / 10, screenH * 1 / 10, screenW * 6 / 10, screenH * 2 / 10 };
		SDL_Rect player_win_rect = { screenW * 7 / 20, screenH * 4 / 10, screenW * 6 / 20, screenH * 1 / 10 };
		SDL_Rect winner_rect = { screenW * 3 / 10, screenH * 5 / 10, screenW * 4 / 10, screenH * 1 / 10 };

		change_font(FIRST_TEXT, 72);
		TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

		display_text(title_text, title_rect, false);

		change_font(SECOND_TEXT, 60);
		TTF_SetFontStyle(font, TTF_STYLE_BOLD);

		display_text(player_win_text, player_win_rect, false);
		display_text(winner_text, winner_rect, false);

		return true;
	}

	return false;
}


