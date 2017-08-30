#include "ppfunctions.h"
#include "sdlfunctions.h"


int PP::howtoplay_menu()
{
	load_background();

	string title_text = "How To Play";
	string back_text = "Back";

	SDL_Event e;

	int mouseX = 0, mouseY = 0;

	bool cont = false;

	bool highlight = false;

	SDL_Rect title_rect = { screenW * 2 / 10, screenH * 1 / 10, screenW * 6 / 10, screenH * 2 / 10 };
	SDL_Rect back_rect = { screenW * 9 / 20, screenH * 8 / 10, screenW * 2 / 20, screenH * 1 / 10 };
	SDL_Rect image_rect = { screenW * 1 / 10, screenH * 2 / 10, screenW * 8 / 10, screenH * 15 / 20 };

	load_image(image_rect, "controls.png");

	change_font(FIRST_TEXT, 72);
	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

	display_text(title_text, title_rect, false);

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

			if (rect_detection(back_rect, mouseX, mouseY))
			{
				highlight = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					cont = true;
				}
			}

			else
			{
				highlight = false;
			}
		}

		Uint32 start = SDL_GetTicks();

		display_text(back_text, back_rect, highlight);

		SDL_RenderPresent(wRenderer);

		Uint32 total = SDL_GetTicks();
		fps_cap(start, total);
	}

	load_background();

	return 0;
}