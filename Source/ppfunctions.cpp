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

bool PP::game_loop()
{
	bool cont = false;

	SDL_Event e;

	if (load_background() < 0)
	{
		return true;
	}

	if (main_menu() < 0)
	{
		return true;
	}

	init_variables();

	if (game_menu() < 0)
	{
		return true;
	}

	if (color_menu() < 0)
	{
		return true;
	}

	while (!cont)
	{
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				return true;
			}
		}

		const Uint8* key = SDL_GetKeyboardState(NULL);

		if (players[0])
		{
			if (key[SDL_SCANCODE_UP])
			{
				paddle_motion(r_paddle_rect, 1);
			}

			if (key[SDL_SCANCODE_DOWN])
			{
				paddle_motion(r_paddle_rect, 0);
			}
		}

		else
		{
			computer_paddle_motion("right");
		}

		if (players[1])
		{
			if (key[SDL_SCANCODE_W])
			{
				paddle_motion(l_paddle_rect, 1);
			}

			if (key[SDL_SCANCODE_S])
			{
				paddle_motion(l_paddle_rect, 0);
			}
		}

		else
		{
			computer_paddle_motion("left");
		}

		ball_motion();

		if (deflection() > 0)
		{
			reset();
			SDL_Delay(1000);

		}

		Uint32 start = SDL_GetTicks();

		draw_board();

		draw_objects();

		cont = game_over();

		SDL_RenderPresent(wRenderer);

		Uint32 total = SDL_GetTicks();
		fps_cap(start, total);
	}

	bool again = play_again();

	return again;
}

void PP::draw_board()
{
	load_background();

	string title_text = "Ping Pong";
	string rally_text = "Rally: ";
	string game_point_text = "Game Point";

	string numbers[11] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

	string l_point_text = numbers[player_points[0]];
	string r_point_text = numbers[player_points[1]];

	char ral[10];

	sprintf_s(ral, 10, "%d", rally_counter);

	rally_text += ral;

	SDL_Rect title_rect = { screenW * 4 / 10,  screenH * 1 / 20, screenW * 2 / 10, screenH * 1 / 10 };
	SDL_Rect left_p_rect = { screenW * 2 / 10,  screenH * 2 / 20, screenW * 1 / 20, screenH * 1 / 10 };
	SDL_Rect right_p_rect = { screenW * 8 / 10,  screenH * 2 / 20, screenW * 1 / 20, screenH * 1 / 10 };
	SDL_Rect rally_rect = { screenW * 17 / 40, screenH * 7 / 40, screenW * 6 / 40, screenH * 1 / 20 };
	SDL_Rect left_game_point = { screenW * 3 / 20,  screenH * 1 / 20, screenW * 3 / 20, screenH * 1 / 20 };
	SDL_Rect right_game_point = { screenW * 15 / 20, screenH * 1 / 20, screenW * 3 / 20, screenH * 1 / 20 };

	change_font(FIRST_TEXT, 72);
	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

	display_text(title_text, title_rect, false);

	change_font(SECOND_TEXT, 60);
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);

	display_text(l_point_text, left_p_rect, false);
	display_text(r_point_text, right_p_rect, false);
	display_text(rally_text, rally_rect, false);

	if (player_points[0] == 9)
	{
		display_text(game_point_text, left_game_point, false);
	}

	if (player_points[1] == 9)
	{
		display_text(game_point_text, right_game_point, false);
	}

	SDL_Rect boxes[4];
	boxes[0] = { borders[0].x,                borders[0].y - borders[1].h, borders[0].w, borders[1].h };
	boxes[1] = { borders[1].x + borders[1].w, borders[1].y,                borders[0].w, borders[1].h };
	boxes[2] = { borders[0].x,                borders[0].y + borders[0].h, borders[0].w, borders[1].h };
	boxes[3] = { borders[3].x + borders[3].w, borders[3].y,                borders[0].w, borders[1].h };

	SDL_RenderFillRects(wRenderer, borders, 4);
	SDL_RenderFillRects(wRenderer, boxes, 4);

	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 2 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 4 / 40, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 6 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 8 / 40, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 10 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 12 / 40, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 14 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 16 / 40, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 18 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 20 / 40, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 22 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 24 / 40, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 26 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 28 / 40, borders[1].x + (borders[1].w / 2), borders[3].y);
}


void PP::draw_objects()
{

	SDL_SetRenderDrawColor(wRenderer, player1_col.r, player1_col.g, player1_col.b, player1_col.a);
	SDL_RenderFillRect(wRenderer, &l_paddle_rect);

	SDL_SetRenderDrawColor(wRenderer, player2_col.r, player2_col.g, player2_col.b, player2_col.a);
	SDL_RenderFillRect(wRenderer, &r_paddle_rect);

	SDL_SetRenderDrawColor(wRenderer, ball_col.r, ball_col.g, ball_col.b, ball_col.a);
	SDL_RenderFillRect(wRenderer, &ball_rect);

	SDL_SetRenderDrawColor(wRenderer, white_col.r, white_col.g, white_col.b, white_col.a);
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


bool PP::play_again()
{
	SDL_Delay(3000);

	load_background();

	SDL_Event e;

	int mouseX, mouseY;

	string title_text = "Play Again";
	string yes_text = "Yes";
	string no_text = "No";

	SDL_Rect title_rect = { screenW * 2 / 10,  screenH * 1 / 10,  screenW * 6 / 10, screenH * 2 / 10 };
	SDL_Rect yes_rect = { screenW * 3 / 20,  screenH * 11 / 20, screenW * 2 / 10, screenH * 1 / 10 };
	SDL_Rect no_rect = { screenW * 13 / 20, screenH * 11 / 20, screenW * 2 / 10, screenH * 1 / 10 };

	change_font(FIRST_TEXT, 72);
	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

	display_text(title_text, title_rect, false);

	change_font(SECOND_TEXT, 60);
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);

	bool highlight[2] = { false, false };

	bool cont = false;

	bool return_val = false;

	while (!cont)
	{
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				cont = true;
				return_val = true;
			}

			if (e.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&mouseX, &mouseY);
			}

			if (rect_detection(yes_rect, mouseX, mouseY))
			{
				highlight[0] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					cont = true;
					return_val = false;
				}
			}

			else
			{
				highlight[0] = false;
			}

			if (rect_detection(no_rect, mouseX, mouseY))
			{
				highlight[1] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					cont = true;
					return_val = true;
				}
			}

			else
			{
				highlight[1] = false;
			}
		}

		Uint32 start = SDL_GetTicks();

		display_text(yes_text, yes_rect, highlight[0]);
		display_text(no_text, no_rect, highlight[1]);

		SDL_RenderPresent(wRenderer);

		Uint32 total = SDL_GetTicks();
		fps_cap(start, total);
	}

	return return_val;
}


