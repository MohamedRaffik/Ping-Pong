#include "ppfunctions.h"
#include "sdlfunctions.h"


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