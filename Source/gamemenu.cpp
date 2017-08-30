#include "ppfunctions.h"
#include "sdlfunctions.h"


int PP::game_menu()
{
	load_background();

	SDL_Event e;

	int mouseX = 0, mouseY = 0;

	string title_text = "Ping Pong";
	string paddle1_text = "Left Paddle";
	string paddle2_text = "Right Paddle";
	string computer_text = "Computer";
	string player_text = "Player";
	string confirm_text = "Confirm";

	bool highlight[5] = { false, false, false, false, false };

	bool cont = false;

	bool l_clicked = true;
	bool r_clicked = true;

	SDL_Rect title_rect = { screenW * 2 / 10,  screenH * 1 / 10,  screenW * 6 / 10, screenH * 2 / 10 };
	SDL_Rect paddle1_rect = { screenW * 1 / 10,  screenH * 4 / 10,  screenW * 3 / 10, screenH * 1 / 10 };
	SDL_Rect paddle2_rect = { screenW * 6 / 10,  screenH * 4 / 10,  screenW * 3 / 10, screenH * 1 / 10 };
	SDL_Rect computer1_rect = { screenW * 3 / 20,  screenH * 13 / 20, screenW * 2 / 10, screenH * 1 / 10 };
	SDL_Rect player1_rect = { screenW * 3 / 20,  screenH * 11 / 20, screenW * 2 / 10, screenH * 1 / 10 };
	SDL_Rect computer2_rect = { screenW * 13 / 20, screenH * 13 / 20, screenW * 2 / 10, screenH * 1 / 10 };
	SDL_Rect player2_rect = { screenW * 13 / 20, screenH * 11 / 20, screenW * 2 / 10, screenH * 1 / 10 };
	SDL_Rect confirm_rect = { screenW * 4 / 10,  screenH * 8 / 10,  screenW * 2 / 10, screenH * 1 / 10 };

	change_font(FIRST_TEXT, 72);
	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

	display_text(title_text, title_rect, false);
	display_text(paddle1_text, paddle1_rect, false);
	display_text(paddle2_text, paddle2_rect, false);

	change_font(SECOND_TEXT, 60);
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);

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

			if ((rect_detection(player1_rect, mouseX, mouseY)) || (r_clicked))
			{
				highlight[0] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					r_clicked = true;
				}
			}

			else
			{
				highlight[0] = false;
			}

			if ((rect_detection(computer1_rect, mouseX, mouseY)) || (!r_clicked))
			{
				highlight[1] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					r_clicked = false;
				}
			}

			else
			{
				highlight[1] = false;
			}

			if ((rect_detection(player2_rect, mouseX, mouseY)) || (l_clicked))
			{
				highlight[2] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					l_clicked = true;
				}
			}

			else
			{
				highlight[2] = false;
			}

			if ((rect_detection(computer2_rect, mouseX, mouseY)) || (!l_clicked))
			{
				highlight[3] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					l_clicked = false;
				}
			}

			else
			{
				highlight[3] = false;
			}

			if (rect_detection(confirm_rect, mouseX, mouseY))
			{
				highlight[4] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					cont = true;
				}
			}

			else
			{
				highlight[4] = false;
			}
		}

		Uint32 start = SDL_GetTicks();

		display_text(player_text, player1_rect, highlight[0]);
		display_text(computer_text, computer1_rect, highlight[1]);
		display_text(player_text, player2_rect, highlight[2]);
		display_text(computer_text, computer2_rect, highlight[3]);
		display_text(confirm_text, confirm_rect, highlight[4]);

		SDL_RenderPresent(wRenderer);

		Uint32 total = SDL_GetTicks();
		fps_cap(start, total);
	}

	players[0] = l_clicked;
	players[1] = r_clicked;

	load_background();

	return 0;
}