#include "FlyMonster.h"



FlyMonster::FlyMonster()
{
    type_ = TH_FLY_MONSTER;
    fly_type_ = FL_CROW;
}


FlyMonster::~FlyMonster()
{
}

void FlyMonster::Init(int type, bool bClip, 
                      int xTile, int yTile, SDL_Renderer* screen,
                      const INT& xOffset /*= 0*/, const INT& yOffset /*= 0*/)
{
    this->set_is_clip(bClip);
    this->set_xpos(xTile * TILE_SIZE + xOffset);
    this->set_ypos(yTile * TILE_SIZE + yOffset);
    this->fly_type_ = type;

    if (fly_type_ == FL_CROW)
    {
        this->LoadImg(sCrowName, screen);
    }
}