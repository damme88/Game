
#ifndef MENU_GAME_H_
#define MENU_GAME_H_
#include "CommonFunc.h"

class MenuGame
{
public:
    MenuGame();
    ~MenuGame();

    static MenuGame* GetInstance();
    int StartMenu(SDL_Renderer* g_screen);
    int PauseMenu(SDL_Renderer* g_screen);
    int GetMenuType() const { return state_menu_; }
    int EndWorldScreen(SDL_Renderer* g_screen);
    bool OnRect(int x, int y, SDL_Rect& rect);
    enum MenuType
    {
        MENU_NONE = 0,
        MENU_START_GAME,
        MENU_PAUSE,
        MENU_ENDGAME,
        MENU_END_WORLD,
    };
private:
    static MenuGame* instance_;
    int state_menu_;
};

#endif