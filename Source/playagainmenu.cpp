#include "ppfunctions.h"
#include "sdlfunctions.h"


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
