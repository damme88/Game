
#ifndef GOOMBAS_H_
#define GOOMBAS_H_

#include "CommonFunc.h"
#include "ThreatsObject.h"
#include "Music.h"

static char sGoombasGreen[] = { "img//goombas2.png" };
static char sGoombassHaha[] = { "img//goombas_haha.png" };
static char sGoombassBase[] = { "img//goombas.png" };

class Goombas : public ThreatsObject
{
public:
    Goombas();
    ~Goombas();
    void Update();
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void UpdateImg(SDL_Renderer* des);
    enum GoomType
    {
        GOOM_BASE = 0,
        GOOM_HORN = 1,
        GOOM_HAHA = 2,
    };
private:
    bool is_move_;
    bool is_change_;
    int goom_type_;
};

#endif
