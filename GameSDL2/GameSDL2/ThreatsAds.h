#pragma once
#include "CommonFunc.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"

const INT NUM_SPACE = 20;
static char space_img_name[] = {"img//thread1_left.png"};

const INT NUM_STATIC = 15;
static char  static_img_name[] = {"img//goombas.png"};

static char plane_img_name[] = {"img//plane_threat.png"};

class ThreatsAds
{

public:
    ThreatsAds();
    ~ThreatsAds();

    static ThreatsAds* GetInstance()
    {
        if (instance_ == NULL)
            instance_ = new ThreatsAds();
        return instance_;
    }

    void BuildThreats(SDL_Renderer* screen);
    void Render(SDL_Renderer* screen);
    bool CheckCollision(SDL_Renderer* screen, const SDL_Rect& rect_obj, const bool& isdel = true);
    bool CheckCollisionSecond(SDL_Renderer* screen, const SDL_Rect& rect_object, const bool& isdel = true);
    bool CheckCollisionLocal(SDL_Renderer* screen);
    void Free();
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    bool GetBoolCol() const { return is_boom_cool_; }
    void AddSecondObject(ThreatsObject* pObj);
    void DrawSecondObject(SDL_Renderer* des);
private:
    static ThreatsAds* instance_;
    std::vector <ThreatsObject*> pThreatsNormal_;
    std::vector <ThreatsObject*> pSecondObject_;
    //ExplosionObject* pEx_;
    bool is_boom_cool_;
};

