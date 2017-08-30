#include "sdlfunctions.h"

SDL_Window* mWindow = NULL;
SDL_Surface* wSurface = NULL;
SDL_Renderer* wRenderer = NULL;
TTF_Font* font = NULL;

int screenW = 1024;
int screenH = 600;

Uint32 black;
Uint32 white;
Uint32 grey;

SDL_Color black_col;
SDL_Color white_col;
SDL_Color red_col;
SDL_Color blue_col;
SDL_Color green_col;
SDL_Color orange_col;
SDL_Color yellow_col;
SDL_Color purple_col;
SDL_Color pink_col;

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	int imgflags = IMG_INIT_PNG;

	if (IMG_Init(imgflags) != imgflags)
	{
		return false;
	}

	SDL_Surface* test_image = IMG_Load("controls.png");

	if (test_image == NULL)
	{
		return false;
	}

	mWindow = SDL_CreateWindow("Ping Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW, screenH, SDL_WINDOW_SHOWN);

	if (mWindow == NULL)
	{
		return false;
	}

	wSurface = SDL_GetWindowSurface(mWindow);

	white = SDL_MapRGB(wSurface->format, 0xFF, 0xFF, 0xFF);
	black = SDL_MapRGB(wSurface->format, 0x00, 0x00, 0x00);
	grey = SDL_MapRGB(wSurface->format, 0x5E, 0x5E, 0x5E);

	white_col = { 0xFF, 0xFF, 0xFF, 0xFF };
	black_col = { 0x00, 0x00, 0x00, 0xFF };
	red_col = { 0xFF, 0x00, 0x00, 0xFF };
	blue_col = { 0x00, 0x00, 0xFF, 0xFF };
	green_col = { 0x00, 0x80, 0x00, 0xFF };
	orange_col = { 0xFF, 0x57, 0x33, 0xFF };
	yellow_col = { 0xFF, 0xFF, 0x00, 0xFF };
	purple_col = { 0x80, 0x00, 0x80, 0xFF };
	pink_col = { 0xFF, 0x00, 0xFF, 0xFF };

	wRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(wRenderer, white_col.r, white_col.g, white_col.b, white_col.a);

	if (wRenderer == NULL)
	{
		return false;
	}

	if (TTF_Init() < 0)
	{
		return false;
	}

	font = TTF_OpenFont("COMPUTERAMOK.ttf", 100);

	if (font == NULL)
	{
		return false;
	}

	font = TTF_OpenFont("Pixel Countdown.ttf", 100);

	if (font == NULL)
	{
		return false;
	}

	return true;
}

int load_background()
{
	SDL_Rect screen = { 0, 0, screenW, screenH };
	SDL_SetRenderDrawColor(wRenderer, 0x5E, 0x5E, 0x5E, 0xFF);
	SDL_RenderFillRect(wRenderer, &screen);
	SDL_SetRenderDrawColor(wRenderer, white_col.r, white_col.g, white_col.b, white_col.a);
	return 0;
}


void load_image(SDL_Rect pos, string file_name)
{
	SDL_Surface* image_surface = IMG_Load(file_name.c_str());
	SDL_Texture* image_texture = SDL_CreateTextureFromSurface(wRenderer, image_surface);

	SDL_RenderCopy(wRenderer, image_texture, NULL, &pos);

	SDL_FreeSurface(image_surface);
	SDL_DestroyTexture(image_texture);

	image_surface = NULL;
	image_texture = NULL;
}


void change_font(TEXT x, int fsize)
{
	if (x == FIRST_TEXT)
	{
		TTF_CloseFont(font);
		font = NULL;
		font = TTF_OpenFont("COMPUTERAMOK.ttf", fsize);
	}

	else if (x == SECOND_TEXT)
	{
		TTF_CloseFont(font);
		font = NULL;
		font = TTF_OpenFont("Pixel Countdown.ttf", fsize);
	}
}

bool rect_detection(SDL_Rect pos, int mouseX, int mouseY)
{
	if ((mouseX >= pos.x) && (mouseX <= pos.x + pos.w) && (mouseY >= pos.y) && (mouseY <= pos.y + pos.h))
	{
		return true;
	}

	return false;
}

void display_text(string text, SDL_Rect pos, bool highlight)
{
	SDL_Surface* text_surface;
	SDL_Texture* text_texture;

	if (highlight)
	{
		text_surface = TTF_RenderText_Blended(font, text.c_str(), black_col);
	}

	else
	{
		text_surface = TTF_RenderText_Blended(font, text.c_str(), white_col);
	}

	text_texture = SDL_CreateTextureFromSurface(wRenderer, text_surface);

	SDL_RenderCopy(wRenderer, text_texture, NULL, &pos);

	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(text_texture);

	text_surface = NULL;
	text_texture = NULL;
}


void change_resolution(int res)
{
	if (res == 0)
	{
		screenW = 800;
		screenH = 600;
	}

	else if (res == 1)
	{
		screenW = 1024;
		screenH = 600;
	}

	else if (res == 2)
	{
		screenW = 1280;
		screenH = 720;
	}

	else if (res == 3)
	{
		screenW = 1366;
		screenH = 768;
	}

	else if (res == 4)
	{
		screenW = 1920;
		screenH = 1080;
	}

	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	init();
	load_background();
}

void fps_cap(Uint32 start, Uint32 total)
{
	int delay = 1000 / 60 - (total - start);

	if (delay > 0)
	{
		SDL_Delay(delay);
	}
}


void close()
{
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}
