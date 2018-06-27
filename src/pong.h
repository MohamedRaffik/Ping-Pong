#ifndef __PONG_H__
#define __PONG_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "textbox.h"
#include "objects.h"
#include <cstdio>
#include <ctime>
#include <sstream>

using namespace std;

typedef enum
{
    MAIN = 0,
    OPTIONS,
    HTP,
    COLOR,
    GAME,
    QUIT,
} MenuCodes;


class Pong
{
public:

    Pong();

    bool init();

    void quit();

    int game_loop();

    MenuCodes main_menu();

    MenuCodes option_menu();

    MenuCodes howtoplay_menu();

    int color_menu();

    int game_menu();

    bool play_again();

private:

    string int_to_string(int num);
    void change_resolution(string new_resolution);
    void clear_screen(const SDL_Color & color);
    void fps_cap(Uint32 start, Uint32 end, int frames);
    Direction determine_movement(const Ball & ball, const Paddle & paddle, const int & diff);
    int rally_counter;
    int playerL_points;
    int playerR_points;
    int l_cpu_difficulty;
    int r_cpu_difficulty;
    SDL_Window * main_Window;
    SDL_Surface * main_Surface;
    SDL_Renderer * main_Renderer;
    int window_width;
    int window_height;
    string resolutions[5];
    int R;
    SDL_Color colors[8];
    int C1;
    int C2;
    Paddle Left_paddle;
    Paddle Right_paddle;
    Ball ball;
};

#endif // __PONG_H__
