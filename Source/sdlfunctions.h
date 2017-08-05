#pragma once

#ifndef SDL_FUNCTIONS
#define SDL_FUNCTIONS

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

extern SDL_Window* mWindow;
extern SDL_Surface* wSurface;
extern SDL_Renderer* wRenderer;
extern TTF_Font* font;

extern int screenW;
extern int screenH;

extern Uint32 black;
extern Uint32 white;
extern Uint32 grey;

extern SDL_Color white_col;
extern SDL_Color black_col;
extern SDL_Color blue_col;
extern SDL_Color red_col;
extern SDL_Color green_col;
extern SDL_Color yellow_col;
extern SDL_Color orange_col;
extern SDL_Color purple_col;
extern SDL_Color pink_col;

typedef enum
{
	FIRST_TEXT = 1,
	SECOND_TEXT
} TEXT;

bool init();

void write_error_to_file();

int load_background();

void load_image(SDL_Rect pos, string file_name);

void clear_screen();

void change_font(TEXT x, int fsize);

bool rect_detection(SDL_Rect pos, int mouseX, int mouseY);

void display_text(string text, SDL_Rect pos, bool highlight);

void change_resolution(int res);

void fps_cap(Uint32 start, Uint32 total);

void close();

#endif // SDL_FUNCTIONS
