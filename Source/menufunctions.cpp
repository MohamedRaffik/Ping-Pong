#include "ppfunctions.h"
#include "sdlfunctions.h"

int PP::main_menu()
{
	load_background();

	SDL_Event e;

	int mouseX = 0, mouseY = 0;

	string title_text = "Ping Pong";

	SDL_Rect start_title_rect = { (screenW * 2 / 10) * 4, screenH * 1 / 10, screenW * 6 / 10, screenH * 2 / 10 };

	string start_text = "Start Game";
	string options_text = "Options";
	string howtoplay_text = "How To Play";
	string exit_text = "Exit";

	int menu_option = 0;

	bool cont = false;

	bool highlight[4] = { false, false, false, false };

	bool adjust = false;

	SDL_Rect title_rect = { screenW * 2 / 10, screenH * 1 / 10,  screenW * 6 / 10, screenH * 2 / 10 };
	SDL_Rect start_rect = { screenW * 3 / 10, screenH * 4 / 10,  screenW * 4 / 10, screenH * 1 / 10 };
	SDL_Rect options_rect = { screenW * 4 / 10, screenH * 11 / 20, screenW * 2 / 10, screenH * 1 / 10 };
	SDL_Rect howtoplay_rect = { screenW * 7 / 20, screenH * 14 / 20, screenW * 6 / 20, screenH * 1 / 10 };
	SDL_Rect exit_rect = { screenW * 9 / 20, screenH * 17 / 20, screenW * 2 / 20, screenH * 1 / 10 };

	while (!cont)
	{

		if (adjust)
		{
			start_title_rect = { (screenW * 2 / 10) * 4, screenH * 1 / 10, screenW * 6 / 10, screenH * 2 / 10 };
			adjust = false;
		}

		if (start_title_rect.x >= title_rect.x + screenW * 1 / 20)
		{
			start_title_rect.x -= screenW * 1 / 40;
			load_background();
		}

		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				menu_option = -1;
				cont = true;
			}

			if (e.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&mouseX, &mouseY);
			}

			if (rect_detection(start_rect, mouseX, mouseY))
			{
				highlight[0] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					menu_option = 0;
					cont = true;
				}
			}

			else
			{
				highlight[0] = false;
			}

			if (rect_detection(exit_rect, mouseX, mouseY))
			{
				highlight[1] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					menu_option = -1;
					cont = true;
				}
			}

			else
			{
				highlight[1] = false;
			}

			if (rect_detection(howtoplay_rect, mouseX, mouseY))
			{
				highlight[2] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					howtoplay_menu();
					adjust = true;
				}
			}

			else
			{
				highlight[2] = false;
			}

			if (rect_detection(options_rect, mouseX, mouseY))
			{
				highlight[3] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					if (option_menu() < 0)
					{
						menu_option = -1;
						cont = true;
					}

					title_rect = { screenW * 2 / 10, screenH * 1 / 10,  screenW * 6 / 10, screenH * 2 / 10 };
					start_rect = { screenW * 3 / 10, screenH * 4 / 10,  screenW * 4 / 10, screenH * 1 / 10 };
					options_rect = { screenW * 4 / 10, screenH * 11 / 20, screenW * 2 / 10, screenH * 1 / 10 };
					howtoplay_rect = { screenW * 7 / 20, screenH * 14 / 20, screenW * 6 / 20, screenH * 1 / 10 };
					exit_rect = { screenW * 9 / 20, screenH * 17 / 20, screenW * 2 / 20, screenH * 1 / 10 };
					adjust = true;
				}
			}

			else
			{
				highlight[3] = false;
			}
		}

		Uint32 start = SDL_GetTicks();

		change_font(FIRST_TEXT, 72);
		TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

		display_text(title_text, start_title_rect, false);

		change_font(SECOND_TEXT, 60);
		TTF_SetFontStyle(font, TTF_STYLE_BOLD);

		display_text(start_text, start_rect, highlight[0]);
		display_text(exit_text, exit_rect, highlight[1]);
		display_text(howtoplay_text, howtoplay_rect, highlight[2]);
		display_text(options_text, options_rect, highlight[3]);

		SDL_RenderPresent(wRenderer);

		Uint32 total = SDL_GetTicks();
		fps_cap(start, total);
	}

	return menu_option;
}



