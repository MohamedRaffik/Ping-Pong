#ifndef PP_FUNCTIONS
#define PP_FUNCTIONS

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <string>
#include <iostream>

using namespace std;

class PP
{
public:

    void init_variables();

    bool game_loop();

    int main_menu();
    int option_menu();
    int game_menu();
    int color_menu();
    int howtoplay_menu();

    void draw_board();

    void draw_objects();

    void paddle_motion(SDL_Rect &paddle, int movement);

    void ball_motion();

    int deflection();

    void reset();

    void computer_paddle_motion(string side);

    bool game_over();

    bool play_again();

private:

    bool players[2];

    SDL_Rect r_paddle_rect;
    SDL_Rect l_paddle_rect;
    SDL_Rect ball_rect;

    SDL_Color player1_col;
    SDL_Color player2_col;
    SDL_Color ball_col;

    SDL_Rect borders[4];

    int rally_counter;

    bool lock;

    int lock_counter;

    int direction;

    int player_points[2];

    int l_cpu_difficulty;

    int r_cpu_difficulty;
};

#endif // PP_FUNCTIONS
