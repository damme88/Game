
#ifndef GOOMBAS_H_
#define GOOMBAS_H_

#include "CommonFunc.h"
#include "ThreatsObject.h"
#include "Music.h"

static char sGoombassBase[] = { "img//sman_gb_monster.png" };
static char sGBTortoise[] = { "img//sman_gb_tortoise.png" };
class GBMonster : public ThreatsObject
{
public:
    GBMonster();
    ~GBMonster();
    void Init(int type, bool bClip, int xTile, int yTile, SDL_Renderer* screen, const INT& xOffset = 0, const INT& yOffset = 0);
    void Update();
    void Show(SDL_Renderer* des);
    void UpdateImg(SDL_Renderer* des);
    void SetIsType(int bType) { gb_type_ = bType; }
    int GetIsType() const { return gb_type_; }
    void DoAction();
    void CheckToMap();
    void DoLeft();
    void DoRight();
    void DoUp();
    void DoDown();
    enum GoomType
    {
        GB_BASE = 0,
        GB_TORTOISE = 1,
    };
private:
    int gb_type_;
};

#endif
