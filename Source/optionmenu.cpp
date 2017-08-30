#include "ppfunctions.h"
#include "sdlfunctions.h"


int PP::option_menu()
{
	load_background();

	SDL_Event e;

	int mouseX = 0, mouseY = 0;

	bool highlight[8] = { false, false, false, false, false, false, false, false };

	string title_text = "Options";
	string resOne_text = "800 x 600";
	string resTwo_text = "1024 x 600";
	string resThree_text = "1280 x 720";
	string resFour_text = "1366 x 768";
	string resFive_text = "1920 x 1080";
	string apply_text = "Apply";
	string back_text = "Back";

	bool cont = false;

	bool change = false;

	int clicked;

	if (screenW == 800)
	{
		clicked = 0;
	}

	if (screenW == 1024)
	{
		clicked = 1;
	}

	if (screenW == 1280)
	{
		clicked = 2;
	}

	if (screenW == 1366)
	{
		clicked = 3;
	}

	if (screenW == 1920)
	{
		clicked = 4;
	}

	SDL_Rect title_rect = { screenW * 2 / 10,  screenH * 1 / 10,  screenW * 6 / 10, screenH * 2 / 10 };
	SDL_Rect resOne_rect = { screenW * 4 / 10,  screenH * 7 / 20,  screenW * 2 / 10, screenH * 1 / 10 };
	SDL_Rect resTwo_rect = { screenW * 4 / 10,  screenH * 9 / 20,  screenW * 2 / 10, screenH * 1 / 10 };
	SDL_Rect resThree_rect = { screenW * 4 / 10,  screenH * 11 / 20, screenW * 2 / 10, screenH * 1 / 10 };
	SDL_Rect resFour_rect = { screenW * 4 / 10,  screenH * 13 / 20, screenW * 2 / 10, screenH * 1 / 10 };
	SDL_Rect resFive_rect = { screenW * 4 / 10,  screenH * 15 / 20, screenW * 2 / 10, screenH * 1 / 10 };
	SDL_Rect apply_rect = { screenW * 5 / 20,  screenH * 17 / 20, screenW * 2 / 20, screenH * 1 / 10 };
	SDL_Rect back_rect = { screenW * 13 / 20, screenH * 17 / 20, screenW * 2 / 20, screenH * 1 / 10 };

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

			if ((rect_detection(resOne_rect, mouseX, mouseY)) || (clicked == 0))
			{
				highlight[0] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					clicked = 0;
				}
			}

			else
			{
				highlight[0] = false;
			}

			if ((rect_detection(resTwo_rect, mouseX, mouseY)) || (clicked == 1))
			{
				highlight[1] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					clicked = 1;
				}
			}

			else
			{
				highlight[1] = false;
			}

			if ((rect_detection(resThree_rect, mouseX, mouseY)) || (clicked == 2))
			{
				highlight[2] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					clicked = 2;
				}
			}

			else
			{
				highlight[2] = false;
			}

			if ((rect_detection(resFour_rect, mouseX, mouseY)) || (clicked == 3))
			{
				highlight[3] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					clicked = 3;
				}
			}

			else
			{
				highlight[3] = false;
			}

			if ((rect_detection(resFive_rect, mouseX, mouseY)) || (clicked == 4))
			{
				highlight[4] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					clicked = 4;
				}
			}

			else
			{
				highlight[4] = false;
			}

			if (rect_detection(back_rect, mouseX, mouseY))
			{
				highlight[5] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					cont = true;
				}
			}

			else
			{
				highlight[5] = false;
			}

			if (rect_detection(apply_rect, mouseX, mouseY))
			{
				highlight[6] = true;

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					change = true;
				}
			}

			else
			{
				highlight[6] = false;
			}
		}

		Uint32 start = SDL_GetTicks();

		display_text(resOne_text, resOne_rect, highlight[0]);
		display_text(resTwo_text, resTwo_rect, highlight[1]);
		display_text(resThree_text, resThree_rect, highlight[2]);
		display_text(resFour_text, resFour_rect, highlight[3]);
		display_text(resFive_text, resFive_rect, highlight[4]);
		display_text(back_text, back_rect, highlight[5]);
		display_text(apply_text, apply_rect, highlight[6]);

		if (change)
		{
			change_resolution(clicked);

			title_rect = { screenW * 2 / 10,  screenH * 1 / 10,  screenW * 6 / 10, screenH * 2 / 10 };
			resOne_rect = { screenW * 4 / 10,  screenH * 7 / 20,  screenW * 2 / 10, screenH * 1 / 10 };
			resTwo_rect = { screenW * 4 / 10,  screenH * 9 / 20,  screenW * 2 / 10, screenH * 1 / 10 };
			resThree_rect = { screenW * 4 / 10,  screenH * 11 / 20, screenW * 2 / 10, screenH * 1 / 10 };
			resFour_rect = { screenW * 4 / 10,  screenH * 13 / 20, screenW * 2 / 10, screenH * 1 / 10 };
			resFive_rect = { screenW * 4 / 10,  screenH * 15 / 20, screenW * 2 / 10, screenH * 1 / 10 };
			apply_rect = { screenW * 5 / 20,  screenH * 17 / 20, screenW * 2 / 20, screenH * 1 / 10 };
			back_rect = { screenW * 13 / 20, screenH * 17 / 20, screenW * 2 / 20, screenH * 1 / 10 };

			change_font(FIRST_TEXT, 72);
			TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

			display_text(title_text, title_rect, false);

			change_font(SECOND_TEXT, 60);
			TTF_SetFontStyle(font, TTF_STYLE_BOLD);

			change = false;
		}

		SDL_RenderPresent(wRenderer);

		Uint32 total = SDL_GetTicks();
		fps_cap(start, total);
	}

	load_background();

	return 0;
}
