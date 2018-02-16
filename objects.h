#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include <SDL2/SDL.h>
#include <cstdio>
#include <ctime>

using namespace std;

/** Enumeration to indicate the Direction that the ball will be moving **/
typedef enum
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    UR,
    UL,
    DR,
    DL,
    UUR,
    UUL,
    DDR,
    DDL,
    URR,
    ULL,
    DRR,
    DLL,
    NONE,
} Direction;


class Paddle
{
public:

    /** Constructor of the Paddle Class **/
    Paddle();

    /** Constructor of the Paddle Class with parameters **/
    Paddle(int x, int y, int w, int h, const SDL_Color & new_color);

    /** Render() - function that renders the Paddle Object onto the screen
     * @pre    - SDL systems are initialized
     * @post   - The Paddle will be rendered on the dimensions of the object
     * @param  - SDL_Renderer * renderer [Pointer to the renderer]
                 SDL_Color & Background  [Color of the Window Background]
                 Direction movement      [Indicates to move paddle to a new position]
                 SDL_Rect & game_rect    [Boundaries of the game]
                 Const int & y           [Distance to be moved]
     * @return - None
     */
    void Render(SDL_Renderer * renderer, const SDL_Color & background, const Direction & new_movement, const SDL_Rect & game_rect, const int & y);

    /** reset() - function that resets the paddle to its original set coordinates **/
    void reset();

    /** set_color() - function that sets the color of the paddle **/
    void set_color(const SDL_Color & new_color);

    /** get_color() - function that returns the color of the paddle **/
    SDL_Color get_color() const;

    /** set_dimensions() - function that sets the dimensions of the paddle **/
    void set_dimensions(int x, int y, int w, int h);

    /** set_dimensions() - function that sets the dimensions of the paddle using a SDL_Rect **/
    void set_dimensions(const SDL_Rect & new_rect);

    /** get_dimensions() - function that returns the dimensions of the paddle **/
    SDL_Rect get_dimensions() const;

private:

    /** move() - function that changes the paddle dimension **/
    void move(const Direction & movement, const SDL_Rect & game_rect, const int & y);

    SDL_Rect orig_rect; //Dimensions of the original state
    SDL_Rect rectangle; //Dimensions of the current state
    SDL_Color Color;    //Color of the paddle
};



class Ball
{
public:

    /** Constructor of the Ball object **/
    Ball();

    /** Constructor of the Ball object with parameters **/
    Ball(int x, int y, int w, int h, const SDL_Color & new_color);

    /** Render() - function that renders the ball to the screen
     * @pre    - SDL systems are initialized
     * @post   - The ball object is rendered to the screen
     * @param  - SDL_Renderer * renderer [Pointer to screen renderer]
               - const SDL_Color & background [Color of window background]
     * @return - None
     */
    void Render(SDL_Renderer * renderer, const SDL_Color & background);

    /** reset() - function that resets the Ball coordinates to its original state **/
    void reset();

    /** collisions - function that detects if the Ball's dimensions intersect with the
                     the game border or any of the paddles
     */
    int collision(const SDL_Rect & border_rect, const Paddle & left_paddle, const Paddle & right_paddle);

    /** set_color() - sets color of the ball **/
    void set_color(const SDL_Color & new_color);

    /** get_color() - returns color of the ball **/
    SDL_Color get_color() const;

    /** set_dimensions() - sets dimensions of the ball **/
    void set_dimensions(int x, int y, int w, int h);

    /** set_dimensions() - sets dimensions of the ball with a SDL_rect **/
    void set_dimensions(const SDL_Rect & new_rect);

    /** get_dimensions() - returns the dimensions of the ball **/
    SDL_Rect get_dimensions() const;

private:

    void move();

    Direction movement;
    SDL_Rect orig_rect;
    SDL_Rect rectangle;
    SDL_Color Color;
};

#endif // __OBJECTS_H__
