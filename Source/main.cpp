#include "sdlfunctions.h"
#include "ppfunctions.h"

int main(int argc, char* argv[])
{
	SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");

	if (!init())
	{
		close();
		return 0;
	}

	bool cont = false;

	PP Game;

	while (!cont)
	{
		cont = Game.game_loop();
	}

	close();

	return 0;
}
