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
    g_font_start = TTF_OpenFont(g_NameFont, 50);
    g_font_end_world = TTF_OpenFont(g_NameFont, 60);
    g_font_pause = TTF_OpenFont(g_NameFont, 30);
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

int MenuGame::StartMenu(SDL_Renderer* screen)
{
    if (g_font_start == NULL)
        return 0;

    int time = 0;
    int x = 0;
    int y = 0;
    state_menu_ = MENU_START_GAME;
    const int kMenuNum = 4;
    const char* labels[] = {"Play Game","Guide","About","Quit" };
    SDL_Texture* menu[kMenuNum];
    bool selected[kMenuNum] = { 0, 0 };
    SDL_Color color[2] = { { 255, 255, 255 },{ 255, 0, 0 } };

    TextObject text_object[kMenuNum];

    SDL_Rect pos[kMenuNum];
    pos[0].x = 6*TILE_SIZE;
    pos[0].y = 4 * TILE_SIZE;
    pos[1].x = 6 * TILE_SIZE;
    pos[1].y = 5 * TILE_SIZE;
    pos[2].x = 6*TILE_SIZE;
    pos[2].y = 6 * TILE_SIZE;
    pos[3].x = 6 * TILE_SIZE;
    pos[3].y = 7 * TILE_SIZE;

    for (int i = 0; i < kMenuNum; i++)
    {
        text_object[i].SetText(labels[i]);
        text_object[i].setColor(color[0].r, color[0].g, color[0].b);
        text_object[i].loadFromRenderedText(g_font_start, screen);
        pos[i].w = text_object[i].getWidth();
        pos[i].h = text_object[i].getHeight();
    }

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
                    bool bRect = OnRect(x, y, pos[i]);
                    if (bRect)
                    {
                        selected[i] = true;
                        text_object[i].setColor(color[1].r, color[1].g, color[1].b);
                        text_object[i].loadFromRenderedText(g_font_start, screen);
                    }
                    else
                    {
                        selected[i] = false;
                        text_object[i].setColor(color[0].r, color[0].g, color[0].b);
                        text_object[i].loadFromRenderedText(g_font_start, screen);
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) 
                {
                    bool bRet = OnRect(x, y, pos[i]);
                    if (bRet)
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
            text_object[i].RenderText(screen, pos[i].x, pos[i].y);
        }

        SDL_RenderPresent(screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }

    return 0;
}

bool MenuGame::OnRect(int x, int y, SDL_Rect& rect)
{
    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}

int MenuGame::PauseMenu(SDL_Renderer* screen)
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
    SDL_Rect pos[kMenuNum];
    pos[0].x = 5 * TILE_SIZE;
    pos[0].y = 5 * TILE_SIZE;
    pos[1].x = 5 * TILE_SIZE;
    pos[1].y = 5 * TILE_SIZE + 30;

    for (int i = 0; i < kMenuNum; ++i)
    {
        text_object[i].SetText(labels[i]);
        text_object[i].setColor(color[0].r, color[0].g, color[0].b);
        text_object[i].loadFromRenderedText(g_font_pause, screen);
        pos[i].w = text_object[i].getWidth();
        pos[i].h = text_object[i].getHeight();
    }

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
                    bool bRet = OnRect(x, y, pos[i]);
                    if (bRet)
                    {
                        selected[i] = 1;
                        text_object[i].setColor(color[1].r, color[1].g, color[1].b);
                        text_object[i].loadFromRenderedText(g_font_pause, screen);
                    }
                    else
                    {
                        selected[i] = 0;
                        text_object[i].setColor(color[0].r, color[0].g, color[0].b);
                        text_object[i].loadFromRenderedText(g_font_pause, screen);
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) 
                {
                    bool bRet = OnRect(x, y, pos[i]);
                    if (bRet)
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
        Gemometric::RenderRectange(rectange_size, color_data, screen);

        GeometricFormat outlie_size(left + 1 , top + 1, width - 2, height - 2);
        ColorData color_outline(255, 255, 255);
        Gemometric::RenderOutline(outlie_size, color_outline, screen);

        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(screen, pos[i].x, pos[i].y);
        }

        SDL_RenderPresent(screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }

    return 0;
}

int MenuGame::EndWorldScreen(SDL_Renderer* screen)
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

    SDL_Rect pos[kMenuNum];
    pos[0].x = 6*TILE_SIZE;
    pos[0].y = 4*TILE_SIZE;
    pos[1].x = 6*TILE_SIZE;
    pos[1].y = 5*TILE_SIZE;

    for (int i = 0; i < kMenuNum; i++)
    {
        text_object[i].SetText(labels[i]);
        text_object[i].setColor(color[0].r, color[0].g, color[0].b);
        text_object[i].loadFromRenderedText(g_font_end_world, screen);
        pos[i].w = text_object[i].getWidth();
        pos[i].h = text_object[i].getHeight();
    }

    BaseObject gBackground;
    bool ret = gBackground.LoadImg("img//end_world.png", screen);

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
                    bool bRet = OnRect(x, y, pos[i]);
                    if (bRet)
                    {
                        selected[i] = 1;
                        text_object[i].setColor(color[1].r, color[1].g, color[1].b);
                        text_object[i].loadFromRenderedText(g_font_end_world, screen);
                    }
                    else
                    {
                        selected[i] = 0;
                        text_object[i].setColor(color[0].r, color[0].g, color[0].b);
                        text_object[i].loadFromRenderedText(g_font_end_world, screen);
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) 
                {
                    bool bRet = OnRect(x, y, pos[i]);
                    if (bRet)
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

        gBackground.Render(screen, NULL);

        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(screen, pos[i].x, pos[i].y);
        }

        SDL_RenderPresent(screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }

    return 0;
}
