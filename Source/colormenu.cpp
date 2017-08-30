#include "ppfunctions.h"
#include "sdlfunctions.h"


int PP::color_menu()
{
	load_background();

	srand((unsigned int)time(NULL));

	SDL_Color colors[9] = { black_col, white_col, red_col, blue_col, green_col, yellow_col, purple_col, pink_col, orange_col };

	int random_1 = rand() % 10;
	int random_2 = rand() % 10;

	SDL_Event e;

	int mouseX = 0, mouseY = 0;

	string title_text = "Ping Pong";
	string paddle1_text = "Left Paddle Color";
	string paddle2_text = "Right Paddle Color";
	string confirm_text = "Confirm";

	bool cont = false;

	bool button_release = true;

	bool highlight = false;

	SDL_Rect title_rect = { screenW * 2 / 10,  screenH * 1 / 10,  screenW * 6 / 10, screenH * 2 / 10 };
	SDL_Rect paddle1_rect = { screenW * 1 / 10,  screenH * 4 / 10,  screenW * 3 / 10, screenH * 1 / 10 };
	SDL_Rect paddle2_rect = { screenW * 6 / 10,  screenH * 4 / 10,  screenW * 3 / 10, screenH * 1 / 10 };
	SDL_Rect color1_rect = { screenW * 3 / 20,  screenH * 11 / 20, screenW * 2 / 10, screenH * 1 / 20 };
	SDL_Rect color2_rect = { screenW * 13 / 20, screenH * 11 / 20, screenW * 2 / 10, screenH * 1 / 20 };
	SDL_Rect confirm_rect = { screenW * 4 / 10,  screenH * 8 / 10,  screenW * 2 / 10, screenH * 1 / 10 };

	change_font(FIRST_TEXT, 72);
	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

	display_text(title_text, title_rect, false);

	change_font(SECOND_TEXT, 60);
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);

	display_text(paddle1_text, paddle1_rect, false);
	display_text(paddle2_text, paddle2_rect, false);

	while (!cont)
	{
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				return -1;
			}

			if (e.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&mouseX, &mouseY);
			}

			if (rect_detection(color1_rect, mouseX, mouseY))
			{
				if ((e.type == SDL_MOUSEBUTTONDOWN) && (button_release))
				{
					random_1++;
					button_release = false;
				}
			}

			if (rect_detection(color2_rect, mouseX, mouseY))
			{
				if ((e.type == SDL_MOUSEBUTTONDOWN) && (button_release))
				{
					random_2++;
					button_release = false;
				}
			}

			if (rect_detection(confirm_rect, mouseX, mouseY))
			{
				highlight = true;

				if ((e.type == SDL_MOUSEBUTTONDOWN) && (button_release))
				{
					if (!((colors[random_1].r == colors[random_2].r) && (colors[random_1].g == colors[random_2].g) && (colors[random_1].b == colors[random_2].b)))
					{
						cont = true;
						button_release = false;
					}
				}
			}

			else
			{
				highlight = false;
			}

			if (random_1 >= 9)
			{
				random_1 = 0;
			}

			if (random_2 >= 9)
			{
				random_2 = 0;
			}

			if (e.type == SDL_MOUSEBUTTONUP)
			{
				button_release = true;
			}
		}

		Uint32 start = SDL_GetTicks();

		SDL_SetRenderDrawColor(wRenderer, colors[random_1].r, colors[random_1].g, colors[random_1].b, colors[random_1].a);
		SDL_RenderFillRect(wRenderer, &color1_rect);

		SDL_SetRenderDrawColor(wRenderer, colors[random_2].r, colors[random_2].g, colors[random_2].b, colors[random_2].a);
		SDL_RenderFillRect(wRenderer, &color2_rect);

		SDL_SetRenderDrawColor(wRenderer, white_col.r, white_col.g, white_col.b, white_col.a);

		display_text(confirm_text, confirm_rect, highlight);

		SDL_RenderPresent(wRenderer);

		Uint32 total = SDL_GetTicks();
		fps_cap(start, total);

	}

	SDL_Color ball_colors[5] = { white_col, red_col, pink_col, yellow_col, orange_col };

	int random_3 = rand() % 5;
	ball_col = ball_colors[random_3];

	player1_col = colors[random_1];
	player2_col = colors[random_2];

	load_background();

	return 0;
}
