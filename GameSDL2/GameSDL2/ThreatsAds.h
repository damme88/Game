#pragma once
#include "CommonFunc.h"
#include "ThreatsObject.h"

const INT NUM_SPACE = 20;
static char space_img_name[] = {"img//thread1_left.png"};

const INT NUM_STATIC = 15;
static char  static_img_name[] = {"img//threat_level.png"};

static char plane_img_name[] = {"img//plane_threat.png"};

class ThreatsAds
{

public:
    ThreatsAds();
    ~ThreatsAds();

    void BuildThreats(SDL_Renderer* screen);
    void Render(SDL_Renderer* screen);
    void SetMapInfo(Map mapInfo) { map_info_ = mapInfo; };
    bool CheckCollision(SDL_Renderer* screen, const SDL_Rect& rect_obj, const bool& checkBullet = false);
    void Free();
private:
    std::vector <ThreatsObject*> pThreatsNormal_;
    Map map_info_;
};

