#pragma once
#include "CommonFunc.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"


static INT gbMonsterList[] = { 10, 20, 26, 48, 53,
                               62, 80, 92, 110, 120, 131, 148, 173 };

static INT gbTortoiseList[] = { 15, 25, 51, 57,
                                68, 75, 88, 99, 108,
                                115, 124, 128, 135, 152, 170, 184 };

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
    void DestroyInstance();

    bool CheckCollision(const SDL_Rect& rect_obj, const bool& isdel = true);
    bool CheckCollisionSecond(SDL_Renderer* screen, const SDL_Rect& rect_object, const bool& isdel = true);
    bool CheckCollisionLocal(SDL_Renderer* screen);
    bool GetBoolCol() const { return is_boom_cool_; }

    void BuildMonster(SDL_Renderer* screen);
    void BuildMonster1(SDL_Renderer* screen);
    void BuildMonster2(SDL_Renderer* screen);

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

