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
