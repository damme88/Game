
#ifndef GOOMBAS_H_
#define GOOMBAS_H_

#include "CommonFunc.h"
#include "ThreatsObject.h"
#include "Music.h"

static char sGoombas2[] = { "img//goombas2.png" };
static char sGoombassHaha[] = { "img//goombas22.png" };
static char sGoombassBase[] = { "img//zoombie.png" };
static char sGoombas5[] = { "img//goombas5.png" };

class Goombas : public ThreatsObject
{
public:
    Goombas();
    ~Goombas();
    void Update();
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void UpdateImg(SDL_Renderer* des);
    void SetIsBoom(bool boom) { is_boom_ = boom; }
    bool GetIsBoom() const { return is_boom_; }
    void SetIsChange(bool bChange) { is_change_ = bChange; }
    bool GetIsChange() const { return is_change_; }
    void SetIsType(int bType) { goom_type_ = bType; }
    int GetIsType() const { return goom_type_; }
    enum GoomType
    {
        GOOM_BASE = 0,
        GOOM_HORN = 1,
        GOOM_HAHA = 2,
        GOOM_X5 = 3,
    };
private:
    bool is_boom_;
    bool is_move_;
    bool is_change_;
    int goom_type_;
};

#endif
