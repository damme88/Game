#pragma once
#include "CommonFunc.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"


static INT gbMonsterList[] = { 10, 20, 30, 40, 50,
                               60, 70, 80, 90, 100,
                               110, 120, 130, 140, 150 };

static INT gbTortoiseList[] = { 15, 25, 35, 45, 55,
                                65, 75, 85, 95, 105,
                                115, 125, 135, 155, 185 };

static INT gbCrowListX[] = { 25, 100, 155};
static INT gbCrowListY[] = { 2, 3, 5 };

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

    bool CheckCollision(SDL_Renderer* screen, const SDL_Rect& rect_obj, const bool& isdel = true);
    bool CheckCollisionSecond(SDL_Renderer* screen, const SDL_Rect& rect_object, const bool& isdel = true);
    bool CheckCollisionLocal(SDL_Renderer* screen);
    bool GetBoolCol() const { return is_boom_cool_; }

    void BuildThreats(SDL_Renderer* screen);
    void Render(SDL_Renderer* screen);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void Free();
    void AddSecondObject(ThreatsObject* pObj);
    void DrawSecondObject(SDL_Renderer* des);
    void MakeGBMonster(SDL_Renderer* screen);
    void MakeGBTortoise(SDL_Renderer* screen);
    void MakeCrowMonster(SDL_Renderer* screen);
private:
    static ThreatsAds* instance_;
    std::vector <ThreatsObject*> pThreatsNormal_;
    std::vector <ThreatsObject*> pSecondObject_;
    //ExplosionObject* pEx_;
    bool is_boom_cool_;
};

