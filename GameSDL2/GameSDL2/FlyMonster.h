
#ifndef FLY_MONSTER_H_
#define FLY_MONSTER_H_

#include "CommonFunc.h"
#include "ThreatsObject.h"

static char sCrowName[] = { "img//sman_crow.png" };

class FlyMonster : public ThreatsObject
{
public:
    FlyMonster();
    ~FlyMonster();
    enum FlyType
    {
        FL_CROW = 0,
    };
    void Init(int type, bool bClip, int xTile, int yTile, 
              SDL_Renderer* screen, const INT& xOffset = 0,
              const INT& yOffset = 0);
private:
    UINT fly_type_;
};

#endif

