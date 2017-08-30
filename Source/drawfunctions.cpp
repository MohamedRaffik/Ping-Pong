#include "ppfunctions.h"
#include "sdlfunctions.h"


void PP::draw_board()
{
	load_background();

	string title_text = "Ping Pong";
	string rally_text = "Rally: ";
	string game_point_text = "Game Point";

	string numbers[11] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

	string l_point_text = numbers[player_points[0]];
	string r_point_text = numbers[player_points[1]];

	char ral[10];

	sprintf_s(ral, 10, "%d", rally_counter);

	rally_text += ral;

	SDL_Rect title_rect = { screenW * 4 / 10,  screenH * 1 / 20, screenW * 2 / 10, screenH * 1 / 10 };
	SDL_Rect left_p_rect = { screenW * 2 / 10,  screenH * 2 / 20, screenW * 1 / 20, screenH * 1 / 10 };
	SDL_Rect right_p_rect = { screenW * 8 / 10,  screenH * 2 / 20, screenW * 1 / 20, screenH * 1 / 10 };
	SDL_Rect rally_rect = { screenW * 17 / 40, screenH * 7 / 40, screenW * 6 / 40, screenH * 1 / 20 };
	SDL_Rect left_game_point = { screenW * 3 / 20,  screenH * 1 / 20, screenW * 3 / 20, screenH * 1 / 20 };
	SDL_Rect right_game_point = { screenW * 15 / 20, screenH * 1 / 20, screenW * 3 / 20, screenH * 1 / 20 };

	change_font(FIRST_TEXT, 72);
	TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

	display_text(title_text, title_rect, false);

	change_font(SECOND_TEXT, 60);
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);

	display_text(l_point_text, left_p_rect, false);
	display_text(r_point_text, right_p_rect, false);
	display_text(rally_text, rally_rect, false);

	if (player_points[0] == 9)
	{
		display_text(game_point_text, left_game_point, false);
	}

	if (player_points[1] == 9)
	{
		display_text(game_point_text, right_game_point, false);
	}

	SDL_Rect boxes[4];
	boxes[0] = { borders[0].x,                borders[0].y - borders[1].h, borders[0].w, borders[1].h };
	boxes[1] = { borders[1].x + borders[1].w, borders[1].y,                borders[0].w, borders[1].h };
	boxes[2] = { borders[0].x,                borders[0].y + borders[0].h, borders[0].w, borders[1].h };
	boxes[3] = { borders[3].x + borders[3].w, borders[3].y,                borders[0].w, borders[1].h };

	SDL_RenderFillRects(wRenderer, borders, 4);
	SDL_RenderFillRects(wRenderer, boxes, 4);

	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 2 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 4 / 40, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 6 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 8 / 40, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 10 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 12 / 40, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 14 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 16 / 40, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 18 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 20 / 40, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 22 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 24 / 40, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 26 / 40);
	SDL_RenderDrawLine(wRenderer, borders[1].x + (borders[1].w / 2), borders[1].y + borders[1].h + screenH * 28 / 40, borders[1].x + (borders[1].w / 2), borders[3].y);
}


void PP::draw_objects()
{

	SDL_SetRenderDrawColor(wRenderer, player1_col.r, player1_col.g, player1_col.b, player1_col.a);
	SDL_RenderFillRect(wRenderer, &l_paddle_rect);
	SDL_RenderDrawRect(wRenderer, &l_paddle_rect);

	SDL_SetRenderDrawColor(wRenderer, player2_col.r, player2_col.g, player2_col.b, player2_col.a);
	SDL_RenderFillRect(wRenderer, &r_paddle_rect);
	SDL_RenderDrawRect(wRenderer, &r_paddle_rect);

	SDL_SetRenderDrawColor(wRenderer, ball_col.r, ball_col.g, ball_col.b, ball_col.a);
	SDL_RenderFillRect(wRenderer, &ball_rect);
	SDL_RenderDrawRect(wRenderer, &ball_rect);

	SDL_SetRenderDrawColor(wRenderer, white_col.r, white_col.g, white_col.b, white_col.a);
}