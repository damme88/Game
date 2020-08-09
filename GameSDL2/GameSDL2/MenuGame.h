
#ifndef MENU_GAME_H_
#define MENU_GAME_H_
#include "CommonFunc.h"

class MenuGame
{
public:
    MenuGame();
    ~MenuGame();

    static MenuGame* GetInstance();
    int StartMenu(SDL_Renderer* g_screen, TTF_Font* font);
    int PauseMenu(SDL_Renderer* g_screen, TTF_Font* font);
    int GetMenuType() const { return state_menu_; }
    enum MenuType
    {
        MENU_NONE = 0,
        MENU_START_GAME = 1,
        MENU_PAUSE = 2,
        MENU_ENDGAME = 3
    };
private:
    static MenuGame* instance_;
    int state_menu_;
};

#endif