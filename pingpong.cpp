#include "pingpong.h"

PingPong::PingPong()
{
    rally_counter = 0;
    playerL_points = 0;
    playerR_points = 0;

    l_cpu_difficulty = 0;
    r_cpu_difficulty = 0;

    main_Window = NULL;
    main_Surface = NULL;
    main_Renderer = NULL;

    window_width = 1280;
    window_height = 720;

    R = 2;

    resolutions[0] = "800 x 600";
    resolutions[1] = "1024 x 576";
    resolutions[2] = "1280 x 720";
    resolutions[3] = "1360 x 768";
    resolutions[4] = "1920 x 1080";

    C1 = 0;
    C2 = 1;

    colors[0] = Red;
    colors[1] = Blue;
    colors[2] = Green;
    colors[3] = Orange;
    colors[4] = Yellow;
    colors[5] = Purple;
    colors[6] = Pink;
    colors[7] = White;

    Left_paddle = Paddle(window_width * 3/80, window_height * 19/40, window_width * 1/80, window_height * 8/40, colors[C1]);
    Right_paddle = Paddle(window_width * 38/40, window_height * 19/40, window_width * 1/80, window_height * 8/40, colors[C2]);
    ball = Ball(window_width * 19/40, window_height * 21/40, window_width * 1/80, window_width * 1/80, White);
}

bool PingPong::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { return false; }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) { return false; }

    SDL_Surface * test_image = IMG_Load("controls.png");

    if (test_image == NULL) { return false; }

    SDL_FreeSurface(test_image);
    test_image = NULL;

    main_Window = SDL_CreateWindow("Ping Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);

    if (main_Window == NULL) { return false; }

    main_Surface = SDL_GetWindowSurface(main_Window);

    if (main_Surface == NULL) { return false; }

    main_Renderer = SDL_CreateRenderer(main_Window, -1, SDL_RENDERER_SOFTWARE);

    if (main_Renderer == NULL) { return false; }
    if (TTF_Init() < 0) { return false; }

    TTF_Font * font = TTF_OpenFont("COMPUTERAMOK.ttf", 64);

    if (font == NULL) { return false; }

    font = TTF_OpenFont("Pixel Countdown.ttf", 64);

    if (font == NULL) { return false; }

    TTF_CloseFont(font);
    font = NULL;

    return true;
}

void PingPong::change_resolution(string new_resolution)
{
    if (new_resolution == resolutions[0])
    {
        window_width = 800;
        window_height = 600;
    }

    else if (new_resolution == resolutions[1])
    {
        window_width = 1024;
        window_height = 576;
    }

    else if (new_resolution == resolutions[2])
    {
        window_width = 1280;
        window_height = 720;
    }

    else if (new_resolution == resolutions[3])
    {
        window_width = 1360;
        window_height = 768;
    }

    else if (new_resolution == resolutions[4])
    {
        window_width = 1920;
        window_height = 1080;
    }

    SDL_DestroyWindow(main_Window);
    main_Window = SDL_CreateWindow("Ping Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);

    main_Surface = SDL_GetWindowSurface(main_Window);
    main_Renderer = SDL_CreateRenderer(main_Window, -1, SDL_RENDERER_SOFTWARE);

    Left_paddle = Paddle(window_width * 3/80, window_height * 19/40, window_width * 1/80, window_height * 8/40, colors[C1]);
    Right_paddle = Paddle(window_width * 38/40, window_height * 19/40, window_width * 1/80, window_height * 8/40, colors[C2]);
    ball = Ball(window_width * 19/40, window_height * 21/40, window_width * 1/80, window_width * 1/80, White);

    clear_screen(Gray);
}

void PingPong::clear_screen(const SDL_Color & color)
{
    SDL_Rect temp;
    temp.x = 0, temp.y = 0, temp.w = window_width, temp.h = window_height;
    SDL_SetRenderDrawColor(main_Renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(main_Renderer, &temp);
}

void PingPong::fps_cap(Uint32 start, Uint32 end, int frames)
{
    int delay = 1000/frames - (end - start);
    if (delay > 0) { SDL_Delay(delay); }
}

string PingPong::int_to_string(int num = 0)
{
    stringstream ss;
    ss << num;
    return ss.str();
}

void PingPong::quit()
{
    if (main_Window != NULL) { SDL_DestroyWindow(main_Window); }
    if (main_Renderer != NULL) { SDL_DestroyRenderer(main_Renderer); }

    main_Window = NULL;
    main_Surface = NULL;
    main_Renderer = NULL;

    SDL_Quit();
}

int PingPong::game_loop()
{
    MenuCodes menu = main_menu();

    while (menu != GAME)
    {
        if (menu == MAIN) { menu = main_menu(); }
        if (menu == OPTIONS) { menu = option_menu(); }
        if (menu == HTP) { menu = howtoplay_menu(); }
        if (menu == QUIT) { return 0; }
    }

    if (game_menu() < 0) { return 0; }
    if (color_menu() < 0) { return 0; }

    clear_screen(Gray);

    SDL_Event event;

    string font[2] = { "COMPUTERAMOK.ttf" , "Pixel Countdown.ttf"};

    TextBox title("Ping Pong", window_width * 4/10, window_height * 1/20, window_width * 2/10, window_height * 1/10, font[0], White, White);
    TextBox left_point(int_to_string(playerL_points), window_width * 2/10, window_height * 1/10, window_width * 1/20, window_height * 1/10, font[1], White, White);
    TextBox right_point(int_to_string(playerR_points), window_width * 8/10, window_height * 1/10, window_width * 1/20, window_height * 1/10, font[1], White, White);
    TextBox rally_text("Rally: " + int_to_string(rally_counter), window_width * 17/40, window_height * 7/40, window_width * 3/20, window_height * 1/20, font[1], White, White);
    TextBox left_game_point("", window_width * 3/20, window_height * 1/20, window_width * 3/20, window_height * 1/20, font[1], White, White);
    TextBox right_game_point("", window_width * 15/20, window_height * 1/20, window_width * 3/20, window_height * 1/20, font[1], White, White);

    TextBox border("", window_width * 1/40, window_height * 5/20, window_width * 38/40, window_height * 29/40, font[1], White, White);
    border.set_border(White);
    SDL_Rect game_rect = border.get_dimensions();

    left_point.set_bold();
    right_point.set_bold();
    rally_text.set_bold();
    left_game_point.set_bold();
    right_game_point.set_bold();

    Direction left_move, right_move;

    while(1)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) { return 0; }
        }

        const Uint8 * keys = SDL_GetKeyboardState(NULL);

        if (l_cpu_difficulty == 0)
        {
            if (keys[SDL_SCANCODE_W]) { left_move = UP; }
            else if (keys[SDL_SCANCODE_S]) { left_move = DOWN; }
            else { left_move = NONE; }
        }
        else { srand(time(NULL)); l_cpu_difficulty = rand() % 3 + 1; left_move = determine_movement(ball, Left_paddle, l_cpu_difficulty); }

        if (r_cpu_difficulty == 0)
        {
            if (keys[SDL_SCANCODE_UP]) { right_move = UP; }
            else if (keys[SDL_SCANCODE_DOWN]) { right_move = DOWN; }
            else { right_move = NONE; }
        }
        else { right_move = determine_movement(ball, Right_paddle, r_cpu_difficulty); }

        int add = ball.collision(game_rect, Left_paddle, Right_paddle);

        if (add > 0) { rally_counter += add; rally_text.set_name("Rally: " + int_to_string(rally_counter)); }
        else if (add < 0)
        {
            if (add == -2) { playerL_points++; left_point.set_name(int_to_string(playerL_points)); }
            else if (add == -1) { playerR_points++; right_point.set_name(int_to_string(playerR_points)); }

            if ( playerL_points == 9) { left_game_point.set_name("Game Point"); }
            if ( playerR_points == 9) { right_game_point.set_name("Game Point"); }

            SDL_Delay(1000);
            clear_screen(Gray);
            ball.reset();
            Left_paddle.reset();
            Right_paddle.reset();

            rally_counter = 0;
            rally_text.set_name("Rally: " + int_to_string(rally_counter));

            if (l_cpu_difficulty != 0) { srand(time(NULL)); l_cpu_difficulty = rand() % 3 + 1; }
            if (r_cpu_difficulty != 0) { srand(time(NULL)); r_cpu_difficulty = rand() % 3 + 1; }
        }

        Uint32 start = SDL_GetTicks();

        title.Render(main_Renderer, Gray);
        left_point.Render(main_Renderer, Gray);
        right_point.Render(main_Renderer, Gray);
        rally_text.Render(main_Renderer, Gray);
        left_game_point.Render(main_Renderer, Gray);
        right_game_point.Render(main_Renderer, Gray);
        border.Render(main_Renderer, Gray);

        Left_paddle.Render(main_Renderer, Gray, left_move, game_rect, window_height * 1/40);
        Right_paddle.Render(main_Renderer, Gray, right_move, game_rect, window_height * 1/40);
        ball.Render(main_Renderer, Gray);

        SDL_RenderPresent(main_Renderer);

        Uint32 end = SDL_GetTicks();
        fps_cap(start, end, 60);

        if (playerL_points == 10 || playerR_points == 10) { break; }
    }

    return play_again();
}

MenuCodes PingPong::main_menu()
{
    clear_screen(Gray);

    SDL_Event event;

    string font[2] = { "COMPUTERAMOK.ttf" , "Pixel Countdown.ttf"};

    TextBox title("Ping Pong", window_width * 8/10, window_height * 1/10, window_width * 6/10, window_height * 2/10, font[0], White, White);
    TextBox start_game("Start Game", window_width * 3/10, window_height * 4/10, window_width * 4/10, window_height * 1/10, font[1], White, Black);
    TextBox options("Options", window_width * 4/10, window_height * 11/20, window_width * 2/10, window_height * 1/10, font[1], White, Black);
    TextBox how_to_play("How To Play", window_width * 7/20, window_height * 7/10, window_width * 3/10, window_height * 1/10, font[1], White, Black);
    TextBox exit("Quit", window_width * 9/20, window_height * 17/20, window_width * 1/10, window_height * 1/10, font[1], White, Black);

    start_game.set_bold();
    options.set_bold();
    how_to_play.set_bold();
    exit.set_bold();

    bool adjust = true;

    while (1)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) { break; }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (start_game.Detection()) { return GAME; }
                    else if (options.Detection()) { return OPTIONS; }
                    else if (how_to_play.Detection()) { return HTP; }
                    else if (exit.Detection()) { break; }
                }
            }
        }

        if (adjust)
        {
            SDL_Rect temp = title.get_dimensions();
            temp.x -= window_width * 1/40;
            title.set_dimensions(temp);
            clear_screen(Gray);

            if (temp.x <= window_width * 2/10) { adjust = false; }
        }

        Uint32 start = SDL_GetTicks();

        title.Render(main_Renderer, Gray);
        start_game.Render(main_Renderer, Gray);
        options.Render(main_Renderer, Gray);
        how_to_play.Render(main_Renderer, Gray);
        exit.Render(main_Renderer, Gray);

        SDL_RenderPresent(main_Renderer);

        Uint32 end = SDL_GetTicks();
        fps_cap(start, end, 100);
    }

    return QUIT;
}

MenuCodes PingPong::option_menu()
{
    clear_screen(Gray);

    SDL_Event event;

    string font[2] = { "COMPUTERAMOK.ttf" , "Pixel Countdown.ttf"};

    TextBox title("Options", window_width * 2/10, window_height * 1/10, window_width * 6/10, window_height * 2/10, font[0], White, White);
    TextBox resOne(resolutions[0], window_width * 4/10, window_height * 7/20, window_width * 2/10, window_height * 1/10, font[1], White, Black);
    TextBox resTwo(resolutions[1], window_width * 4/10, window_height * 9/20, window_width * 2/10, window_height * 1/10, font[1], White, Black);
    TextBox resThree(resolutions[2], window_width * 4/10, window_height * 11/20, window_width * 2/10, window_height * 1/10, font[1], White, Black);
    TextBox resFour(resolutions[3], window_width * 4/10, window_height * 13/20, window_width * 2/10, window_height * 1/10, font[1], White, Black);
    TextBox resFive(resolutions[4], window_width * 4/10, window_height * 15/20, window_width * 2/10, window_height * 1/10, font[1], White, Black);
    TextBox apply("Apply", window_width * 5/20, window_height * 17/20, window_width * 1/10, window_height * 1/10, font[1], White, Black);
    TextBox back("Back", window_width * 13/20, window_height * 17/20, window_width * 1/10, window_height * 1/10, font[1], White, Black);

    resOne.set_bold();
    resTwo.set_bold();
    resThree.set_bold();
    resFour.set_bold();
    resFive.set_bold();
    apply.set_bold();
    back.set_bold();

    while (1)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) { break; }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (resOne.Detection()) { R = 0; }
                    else if (resTwo.Detection()) { R = 1; }
                    else if (resThree.Detection()) { R = 2; }
                    else if (resFour.Detection()) { R = 3; }
                    else if (resFive.Detection()) { R = 4; }

                    else if (apply.Detection())
                    {
                        change_resolution(resolutions[R]);
                        title.set_dimensions(window_width * 2/10, window_height * 1/10, window_width * 6/10, window_height * 2/10);
                        resOne.set_dimensions(window_width * 4/10, window_height * 7/20, window_width * 2/10, window_height * 1/10);
                        resTwo.set_dimensions(window_width * 4/10, window_height * 9/20, window_width * 2/10, window_height * 1/10);
                        resThree.set_dimensions(window_width * 4/10, window_height * 11/20, window_width * 2/10, window_height * 1/10);
                        resFour.set_dimensions(window_width * 4/10, window_height * 13/20, window_width * 2/10, window_height * 1/10);
                        resFive.set_dimensions(window_width * 4/10, window_height * 15/20, window_width * 2/10, window_height * 1/10);
                        apply.set_dimensions(window_width * 5/20, window_height * 17/20, window_width * 1/10, window_height * 1/10);
                        back.set_dimensions(window_width * 13/20, window_height * 17/20, window_width * 1/10, window_height * 1/10);
                    }

                    else if (back.Detection()) { return MAIN; }
                }
            }
        }

        if (R == 0) { resOne.set_regular(Black); }
        else { resOne.set_regular(White); }
        if (R == 1) { resTwo.set_regular(Black); }
        else { resTwo.set_regular(White); }
        if (R == 2) { resThree.set_regular(Black); }
        else { resThree.set_regular(White); }
        if (R == 3) { resFour.set_regular(Black); }
        else { resFour.set_regular(White); }
        if (R == 4) { resFive.set_regular(Black); }
        else { resFive.set_regular(White); }

        Uint32 start = SDL_GetTicks();

        title.Render(main_Renderer, Gray);
        resOne.Render(main_Renderer, Gray);
        resTwo.Render(main_Renderer, Gray);
        resThree.Render(main_Renderer, Gray);
        resFour.Render(main_Renderer, Gray);
        resFive.Render(main_Renderer, Gray);
        apply.Render(main_Renderer, Gray);
        back.Render(main_Renderer, Gray);

        SDL_RenderPresent(main_Renderer);

        Uint32 end = SDL_GetTicks();
        fps_cap(start, end, 100);
    }

    return QUIT;
}

MenuCodes PingPong::howtoplay_menu()
{
    clear_screen(Gray);

    SDL_Event event;

    string font[2] = { "COMPUTERAMOK.ttf" , "Pixel Countdown.ttf"};

    TextBox title("How To Play", window_width * 2/10, window_height * 1/10, window_width * 6/10, window_height * 2/10, font[0], White, White);
    TextBox back("Back", window_width * 9/20, window_height * 8/10, window_width * 1/10, window_height * 1/10, font[1], White, Black);
    ImageBox controls("controls.png", window_width * 1/10, window_height * 2/10, window_width * 8/10, window_height * 15/20);
    controls.Render(main_Renderer, Gray);

    back.set_bold();

    while(1)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) { break; }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (back.Detection()) { return MAIN; }
                }
            }
        }

        Uint32 start = SDL_GetTicks();

        title.Render(main_Renderer, Gray);
        back.Render(main_Renderer, Gray);

        SDL_RenderPresent(main_Renderer);

        Uint32 end = SDL_GetTicks();
        fps_cap(start, end, 100);
    }

    return QUIT;
}

int PingPong::color_menu()
{
    clear_screen(Gray);

    SDL_Event event;

    string font[2] = { "COMPUTERAMOK.ttf" , "Pixel Countdown.ttf"};

    TextBox title("Ping Pong", window_width * 2/10, window_height * 1/10, window_width * 6/10, window_height * 2/10, font[0], White, White);
    TextBox left_paddle("Left Paddle Color", window_width * 1/10, window_height * 4/10, window_width * 3/10, window_height * 1/10, font[1], White, White);
    TextBox right_paddle("Right Paddle Color", window_width * 6/10, window_height * 4/10, window_width * 3/10, window_height * 1/10, font[1], White, White);
    TextBox confirm("Confirm", window_width * 4/10, window_height * 8/10, window_width * 2/10, window_height * 1/10, font[1], White, Black);
    TextBox left_color("", window_width * 3/20, window_height * 11/20, window_width * 2/10, window_height * 1/20, font[1], White, White);
    TextBox right_color("", window_width * 13/20, window_height * 11/20, window_width * 2/10, window_height * 1/20, font[1], White, White);

    left_paddle.set_bold();
    right_paddle.set_bold();
    confirm.set_bold();

    while(1)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) { break; }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (left_color.Detection())
                    {
                        if (C1 == 7) { C1 = 0; }
                        else { C1++; }
                        Left_paddle.set_color(colors[C1]);
                    }

                    else if (right_color.Detection())
                    {
                        if (C2 == 7) { C2 = 0; }
                        else { C2++; }
                        Right_paddle.set_color(colors[C2]);
                    }

                    else if (confirm.Detection())
                    {
                        if (C1 != C2) { return 0; }
                    }
                }
            }
        }

        Uint32 start = SDL_GetTicks();

        title.Render(main_Renderer, Gray);
        left_paddle.Render(main_Renderer, Gray);
        right_paddle.Render(main_Renderer, Gray);
        confirm.Render(main_Renderer, Gray);
        left_color.Render(main_Renderer, colors[C1]);
        right_color.Render(main_Renderer, colors[C2]);

        SDL_RenderPresent(main_Renderer);

        Uint32 end = SDL_GetTicks();
        fps_cap(start, end, 100);
    }

    return -1;
}

int PingPong::game_menu()
{
    clear_screen(Gray);

    SDL_Event event;

    string font[2] = { "COMPUTERAMOK.ttf", "Pixel Countdown.ttf"};

    TextBox title ("Ping Pong", window_width * 2/10, window_height * 1/10, window_width * 6/10, window_height * 2/10, font[0], White, White);
    TextBox left_paddle("Left Paddle", window_width * 1/10, window_height * 4/10, window_width * 3/10, window_height * 1/10, font[1], White, White);
    TextBox right_paddle("Right Paddle", window_width * 6/10, window_height * 4/10, window_width * 3/10, window_height * 1/10, font[1], White,White);
    TextBox left_com("Computer", window_width * 3/20, window_height * 13/20, window_width * 2/10, window_height * 1/10, font[1], White, Black);
    TextBox left_player("Player", window_width * 3/20, window_height * 11/20, window_width * 2/10, window_height * 1/10, font[1], White, Black);
    TextBox right_com("Computer", window_width * 13/20, window_height * 13/20, window_width * 2/10, window_height * 1/10, font[1], White, Black);
    TextBox right_player("Player", window_width * 13/20, window_height * 11/20, window_width * 2/10, window_height * 1/10, font[1], White, Black);
    TextBox confirm("Confirm", window_width * 4/10, window_height * 8/10, window_width * 2/10, window_height * 1/10, font[1], White, Black);

    left_paddle.set_bold();
    right_paddle.set_bold();
    left_com.set_bold();
    right_com.set_bold();
    left_player.set_bold();
    right_player.set_bold();
    confirm.set_bold();

    while(1)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) { break; }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (left_com.Detection()) { l_cpu_difficulty = 1; }
                    else if (right_com.Detection()) { r_cpu_difficulty = 1; }
                    else if (left_player.Detection()) { l_cpu_difficulty = 0; }
                    else if (right_player.Detection()) { r_cpu_difficulty = 0; }
                    else if (confirm.Detection()) { return 0; }
                }
            }
        }

        if (l_cpu_difficulty == 0) { left_player.set_regular(Black); left_com.set_regular(White); }
        else { left_player.set_regular(White); left_com.set_regular(Black); }
        if (r_cpu_difficulty == 0) { right_player.set_regular(Black); right_com.set_regular(White); }
        else { right_player.set_regular(White); right_com.set_regular(Black); }

        Uint32 start = SDL_GetTicks();

        title.Render(main_Renderer, Gray);
        left_paddle.Render(main_Renderer, Gray);
        right_paddle.Render(main_Renderer, Gray);
        left_com.Render(main_Renderer, Gray);
        left_player.Render(main_Renderer, Gray);
        right_com.Render(main_Renderer, Gray);
        right_player.Render(main_Renderer, Gray);
        confirm.Render(main_Renderer, Gray);

        SDL_RenderPresent(main_Renderer);

        Uint32 end = SDL_GetTicks();
        fps_cap(start, end, 100);
    }

    return -1;
}

bool PingPong::play_again()
{
    clear_screen(Gray);

    SDL_Event event;

    string font[2] = {"COMPUTERAMOK.ttf", "Pixel Countdown.ttf"};

    TextBox title("Play Again", window_width * 2/10, window_height * 1/10, window_width * 6/10, window_height * 2/10, font[0], White, White);
    TextBox yes("Yes", window_width * 3/20, window_height * 11/20, window_width * 2/10, window_height * 1/10, font[1], White, Black);
    TextBox no("No", window_width * 13/20, window_height * 11/20, window_width * 2/10, window_height * 1/10, font[1], White, Black);

    yes.set_bold();
    no.set_bold();

    while(1)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) { break; }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (yes.Detection()) { return true; }
                    else if (no.Detection()) { return false; }
                }
            }
        }

        Uint32 start = SDL_GetTicks();

        title.Render(main_Renderer, Gray);
        yes.Render(main_Renderer, Gray);
        no.Render(main_Renderer, Gray);

        SDL_RenderPresent(main_Renderer);

        Uint32 end = SDL_GetTicks();
        fps_cap(start, end, 100);
    }

    return false;
}

Direction PingPong::determine_movement(const Ball & ball, const Paddle & paddle, const int & diff)
{
    SDL_Rect game_ball = ball.get_dimensions();
    SDL_Rect paddle_rect = paddle.get_dimensions();

    int range = diff * window_width * 3/20;

    if (game_ball.x < paddle_rect.x + paddle_rect.w + range && game_ball.x + game_ball.w > paddle_rect.x - range)
    {
        if (paddle_rect.y > game_ball.y + game_ball.h) { return UP; }
        else if (paddle_rect.y + paddle_rect.h < game_ball.y) { return DOWN; }
    }

    return NONE;
}

