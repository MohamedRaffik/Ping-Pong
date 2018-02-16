#include "objects.h"

Paddle::Paddle() { orig_rect.x = -1, orig_rect.y = -1, orig_rect.w = -1, orig_rect.h = -1; }

Paddle::Paddle(int x, int y, int w, int h, const SDL_Color & new_color)
{
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;

    orig_rect.x = x;
    orig_rect.y = y;
    orig_rect.w = w;
    orig_rect.h = h;

    Color = new_color;
}

void Paddle::Render(SDL_Renderer * renderer, const SDL_Color & background, const Direction & new_movement, const SDL_Rect & game_rect, const int & y)
{
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
    SDL_RenderFillRect(renderer, &rectangle);

    move(new_movement, game_rect, y);

    SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);
    SDL_RenderFillRect(renderer, &rectangle);
}

void Paddle::move(const Direction & movement, const SDL_Rect & game_rect, const int & y)
{
    if (movement == UP)
    {
        rectangle.y -= y;
        if (game_rect.y > rectangle.y) { rectangle.y += y; }
    }

    else if (movement == DOWN)
    {
        rectangle.y += y;
        if (game_rect.y + game_rect.h < rectangle.y + rectangle.h) { rectangle.y -= y; }
    }
}

void Paddle::reset()
{
    rectangle.x = orig_rect.x;
    rectangle.y = orig_rect.y;
    rectangle.w = orig_rect.w;
    rectangle.h = orig_rect.h;
}

void Paddle::set_color(const SDL_Color & new_color) { Color = new_color; }

SDL_Color Paddle::get_color() const { return Color; }

void Paddle::set_dimensions(const SDL_Rect & new_rect)
{
    if (orig_rect.x == -1) { orig_rect = new_rect; }
    rectangle = new_rect;
}

void Paddle::set_dimensions(int x, int y, int w, int h)
{
    if (orig_rect.x == -1)
    {
        orig_rect.x = x;
        orig_rect.y = y;
        orig_rect.w = w;
        orig_rect.h = h;
    }

    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
}

SDL_Rect Paddle::get_dimensions() const { return rectangle; }


Ball::Ball() {}

Ball::Ball(int x, int y, int w, int h, const SDL_Color & new_color)
{
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;

    orig_rect.x = x;
    orig_rect.y = y;
    orig_rect.w = w;
    orig_rect.h = h;

    Color = new_color;

    Direction begin_move[14] = {LEFT, RIGHT, UR, UL, DR, DL, UUR, UUL, DDR, DDL, URR, ULL, DRR, DLL};

    srand(time(NULL));

    movement = begin_move[rand() % 14];
}

void Ball::Render(SDL_Renderer * renderer, const SDL_Color & background)
{
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
    SDL_RenderFillRect(renderer, &rectangle);

    move();

    SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);
    SDL_RenderFillRect(renderer, &rectangle);
}

void Ball::move()
{
    if (movement == LEFT) { rectangle.x -= rectangle.w; }
    else if (movement == RIGHT) { rectangle.x += rectangle.w; }
    else if (movement == UR) { rectangle.x += rectangle.w; rectangle.y -= rectangle.h; }
    else if (movement == UL) { rectangle.x -= rectangle.w; rectangle.y -= rectangle.h; }
    else if (movement == DR) { rectangle.x += rectangle.w; rectangle.y += rectangle.h; }
    else if (movement == DL) { rectangle.x -= rectangle.w; rectangle.y += rectangle.h; }
    else if (movement == UUR) { rectangle.x += rectangle.w / 2; rectangle.y -= rectangle.h; }
    else if (movement == UUL) { rectangle.x -= rectangle.w / 2; rectangle.y -= rectangle.h; }
    else if (movement == DDR) { rectangle.x += rectangle.w / 2; rectangle.y += rectangle.h; }
    else if (movement == DDL) { rectangle.x -= rectangle.w / 2; rectangle.y += rectangle.h; }
    else if (movement == URR) { rectangle.x += rectangle.w; rectangle.y -= rectangle.h / 2; }
    else if (movement == ULL) { rectangle.x -= rectangle.w; rectangle.y -= rectangle.h / 2; }
    else if (movement == DRR) { rectangle.x += rectangle.w; rectangle.y += rectangle.h / 2; }
    else if (movement == DLL) { rectangle.x -= rectangle.w; rectangle.y += rectangle.h / 2; }
}

void Ball::reset()
{
    rectangle.x = orig_rect.x;
    rectangle.y = orig_rect.y;
    rectangle.w = orig_rect.w;
    rectangle.h = orig_rect.h;

    Direction begin_move[14] = {LEFT, RIGHT, UR, UL, DR, DL, UUR, UUL, DDR, DDL, URR, ULL, DRR, DLL};

    srand(time(NULL));

    movement = begin_move[rand() % 14];
}

int Ball::collision(const SDL_Rect & border_rect, const Paddle & left_paddle, const Paddle & right_paddle)
{
    srand(time(NULL));

    SDL_Rect temp;
    SDL_Rect left = left_paddle.get_dimensions();
    SDL_Rect right = right_paddle.get_dimensions();

    left.w += rectangle.w * 1/2;
    left.y -= rectangle.h * 1/2;
    left.h += rectangle.h;
    right.x -= rectangle.w * 1/2;
    right.y -= rectangle.h * 1/2;
    right.h += rectangle.h;

    if (SDL_IntersectRect(&left, &rectangle, &temp))
    {
        Direction new_movements[7] = {RIGHT, UR, DR, UUR, DDR, URR, DRR};
        movement = new_movements[rand() % 7];
        return 1;
    }

    else if (SDL_IntersectRect(&right, &rectangle, &temp))
    {
        Direction new_movements[7] = {LEFT, UL, DL, UUL, DDL, ULL, DLL};
        movement = new_movements[rand() % 7];
        return 1;
    }

    else if (rectangle.y <= border_rect.y)
    {
        if (movement == UR) { movement = DR; }
        else if (movement == UL) { movement = DL; }
        else if (movement == UUR) { movement = DDR; }
        else if (movement == UUL) { movement = DDL; }
        else if (movement == URR) { movement = DRR; }
        else if (movement == ULL) { movement = DLL; }
        return 0;
    }

    else if (rectangle.y + rectangle.h >= border_rect.y + border_rect.h)
    {
        if (movement == DR) { movement = UR; }
        else if (movement == DL) { movement = UL; }
        else if (movement == DDR) { movement = UUR; }
        else if (movement == DDL) { movement = UUL; }
        else if (movement == DRR) { movement = URR; }
        else if (movement == DLL) { movement = ULL; }
        return 0;
    }

    else if (rectangle.x <= border_rect.x) { return -1; }
    else if (rectangle.x + rectangle.w >= border_rect.x + border_rect.w) { return -2; }

    return 0;
}

void Ball::set_color(const SDL_Color & new_color) { Color = new_color; }

SDL_Color Ball::get_color() const { return Color; }

void Ball::set_dimensions(const SDL_Rect & new_rect) { rectangle = new_rect; }

void Ball::set_dimensions(int x, int y, int w, int h)
{
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
}

SDL_Rect Ball::get_dimensions() const { return rectangle; }
