#include "MenuGame.h"
#include "Geometric.h"
#include "Music.h"

MenuGame* MenuGame::instance_ = NULL;

TTF_Font* g_font_end_world = NULL;
TTF_Font* g_font_start = NULL;
TTF_Font* g_font_pause = NULL;

MenuGame::MenuGame()
{
    state_menu_ = MENU_NONE;
    g_font_start = TTF_OpenFont("font//ARCADE.ttf", 100);
    g_font_end_world = TTF_OpenFont("font//ARCADE.ttf", 60);
    g_font_pause = TTF_OpenFont("font//ARCADE.ttf", 30);
}


MenuGame::~MenuGame()
{
}

MenuGame* MenuGame::GetInstance()
{
    if (instance_ == NULL)
    {
        instance_ = new MenuGame();
    }

    return instance_;
}

int MenuGame::StartMenu(SDL_Renderer* g_screen)
{
    if (g_font_start == NULL)
        return 0;

    int time = 0;
    int x = 0;
    int y = 0;
    state_menu_ = MENU_START_GAME;
    const int kMenuNum = 2;
    const char* labels[kMenuNum] = { "Start Game", "Exit" };
    SDL_Texture* menu[kMenuNum];
    bool selected[kMenuNum] = { 0, 0 };
    SDL_Color color[2] = { { 255, 255, 255 },{ 255, 0, 0 } };

    TextObject text_object[kMenuNum];
    text_object[0].SetText(labels[0]);
    text_object[0].setColor(color[0].r, color[0].g, color[0].b);

    text_object[0].loadFromRenderedText(g_font_start, g_screen);

    text_object[1].SetText(labels[1]);
    text_object[1].setColor(color[0].r, color[0].g, color[0].b);
    text_object[1].loadFromRenderedText(g_font_start, g_screen);


    SDL_Rect pos[kMenuNum];
    pos[0].x = SCREEN_WIDTH*0.3 - 150;
    pos[0].y = SCREEN_HEIGHT*0.8 - 40;
    pos[1].x = SCREEN_WIDTH*0.3 - 150;
    pos[1].y = SCREEN_HEIGHT*0.8 + 40;

    //BaseObject gBackground;
    //bool ret = gBackground.LoadImg("img//bkgn_menu.png", g_screen);

    SDL_Event event;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                text_object[0].Free();
                text_object[0].Free();
                //gBackground.Free();
                state_menu_ = MENU_NONE;
                return 1;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < kMenuNum; ++i)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[1].r, color[1].g, color[1].b);
                            text_object[i].loadFromRenderedText(g_font_start, g_screen);
                        }
                    }
                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_object[i].Free();
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[0].r, color[0].g, color[0].b);
                            text_object[i].loadFromRenderedText(g_font_start, g_screen);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        text_object[0].Free();
                        text_object[1].Free();
                        //gBackground.Free();
                        state_menu_ = MENU_NONE;
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    text_object[0].Free();
                    text_object[1].Free();
                    //gBackground.Free();
                    state_menu_ = MENU_NONE;
                    return 1;
                }
            }
        }

        //gBackground.Render(g_screen, NULL);

        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(g_screen, pos[i].x, pos[i].y);
            pos[i].w = text_object[i].getWidth();
            pos[i].h = text_object[i].getHeight();
        }


        SDL_RenderPresent(g_screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }

    return 0;
}

int MenuGame::PauseMenu(SDL_Renderer* g_screen)
{
    if (g_font_pause == NULL)
    {
        return 0;
    }

    int time = 0;
    int x = 0;
    int y = 0;
    state_menu_ = MENU_PAUSE;
    const int kMenuNum = 2;
    const char* labels[kMenuNum] = { "Resume", "Quit Game"};
    SDL_Texture* menu[kMenuNum];
    bool selected[kMenuNum] = { 0, 0};
    SDL_Color color[2] = { { 255, 255, 255 },{ 255, 0, 0 }};

    TextObject text_object[kMenuNum];

    for (int i = 0; i < kMenuNum; ++i)
    {
        text_object[i].SetText(labels[i]);
        text_object[i].setColor(color[0].r, color[0].g, color[0].b);
        text_object[i].loadFromRenderedText(g_font_pause, g_screen);
    }

    SDL_Rect pos[kMenuNum];
    pos[0].x = 5*TILE_SIZE;
    pos[0].y = 5*TILE_SIZE;
    pos[1].x = 5*TILE_SIZE;
    pos[1].y = 5*TILE_SIZE + 30;

    SDL_Event event;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < kMenuNum; ++i)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[1].r, color[1].g, color[1].b);
                            text_object[i].loadFromRenderedText(g_font_pause, g_screen);
                        }
                    }
                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_object[i].Free();
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[0].r, color[0].g, color[0].b);
                            text_object[i].loadFromRenderedText(g_font_pause, g_screen);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) 
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        text_object[0].Free();
                        text_object[1].Free();
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE ||
                    event.key.keysym.sym == SDLK_RETURN)
                {
                    text_object[0].Free();
                    text_object[1].Free();
                    state_menu_ = MENU_NONE;
                    Music::GetInstance()->PauseMusic();
                    return 0;
                }
            }
        }


        //Draw Geometric
        int left = 4 * TILE_SIZE + 20;
        int top = 5 * TILE_SIZE - 30;
        int width = 4 * TILE_SIZE - 20;
        int height = 1.5*TILE_SIZE;

        GeometricFormat rectange_size(left, top, width, height);
        ColorData color_data(36, 36, 36);
        Gemometric::RenderRectange(rectange_size, color_data, g_screen);

        GeometricFormat outlie_size(left + 1 , top + 1, width - 2, height - 2);
        ColorData color_data1(255, 255, 255);
        Gemometric::RenderOutline(outlie_size, color_data1, g_screen);

        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(g_screen, pos[i].x, pos[i].y);
            pos[i].w = text_object[i].getWidth();
            pos[i].h = text_object[i].getHeight();
        }


        SDL_RenderPresent(g_screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }

    return 0;
}

int MenuGame::EndWorldScreen(SDL_Renderer* g_screen)
{
    if (g_font_end_world == NULL)
        return 0;

    int time = 0;
    int x = 0;
    int y = 0;
    state_menu_ = MENU_START_GAME;
    const int kMenuNum = 2;
    const char* labels[kMenuNum] = { "Next World", "Exit" };
    SDL_Texture* menu[kMenuNum];
    bool selected[kMenuNum] = { 0, 0 };
    SDL_Color color[2] = { { 255, 255, 255 },{ 255, 0, 0 } };

    TextObject text_object[kMenuNum];
    text_object[0].SetText(labels[0]);
    text_object[0].setColor(color[0].r, color[0].g, color[0].b);
    text_object[0].loadFromRenderedText(g_font_end_world, g_screen);
    text_object[1].SetText(labels[1]);
    text_object[1].setColor(color[0].r, color[0].g, color[0].b);
    text_object[1].loadFromRenderedText(g_font_end_world, g_screen);

    SDL_Rect pos[kMenuNum];
    pos[0].x = SCREEN_WIDTH*0.5 - 150;
    pos[0].y = SCREEN_HEIGHT*0.8 - 20;
    pos[1].x = SCREEN_WIDTH*0.5 - 150;
    pos[1].y = SCREEN_HEIGHT*0.8 + 20;

    BaseObject gBackground;
    bool ret = gBackground.LoadImg("img//end_world.png", g_screen);

    SDL_Event event;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                text_object[0].Free();
                text_object[0].Free();
                gBackground.Free();
                state_menu_ = MENU_NONE;
                return 1;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < kMenuNum; ++i)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[1].r, color[1].g, color[1].b);
                            text_object[i].loadFromRenderedText(g_font_end_world, g_screen);
                        }
                    }
                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_object[i].Free();
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[0].r, color[0].g, color[0].b);
                            text_object[i].loadFromRenderedText(g_font_end_world, g_screen);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        text_object[0].Free();
                        text_object[1].Free();
                        gBackground.Free();
                        state_menu_ = MENU_NONE;
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    text_object[0].Free();
                    text_object[1].Free();
                    gBackground.Free();
                    state_menu_ = MENU_NONE;
                    return 1;
                }
            }
        }

        gBackground.Render(g_screen, NULL);

        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(g_screen, pos[i].x, pos[i].y);
            pos[i].w = text_object[i].getWidth();
            pos[i].h = text_object[i].getHeight();
        }

        SDL_RenderPresent(g_screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }

    return 0;
}
