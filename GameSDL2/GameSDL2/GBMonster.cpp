

#include "GBMonster.h"

GBMonster::GBMonster()
{
    gb_type_ = GB_BASE;
    type_ = TH_GB_MONSTER;
}


GBMonster::~GBMonster()
{

}

void GBMonster::Init(int type, bool bClip, int xTile, int yTile,
                     SDL_Renderer* screen, 
                     const INT& xOffset /*= 0*/,
                     const INT& yOffset /*= 0*/)
{
    this->set_is_clip(bClip);
    this->set_xpos(xTile * TILE_SIZE + xOffset);
    this->set_ypos(yTile * TILE_SIZE + yOffset);
    this->gb_type_ = type;

    if (gb_type_ == GB_BASE)
    {
        this->LoadImg(sGoombassBase, screen);
    }
    else if (gb_type_ == GB_TORTOISE)
    {
        this->LoadImg(sGBTortoise, screen);
    }
}

void GBMonster::Update()
{
    if (on_ground_ == 1)
    {
        int dMoving = 0;
        if (gb_type_ == GB_BASE)
        {
            dMoving = 3;
        }
        else if (gb_type_ == GB_TORTOISE)
        {
            dMoving = 2;
            if (x_left_count_ == 60 ||
                x_right_count_ == 60)
            {
                v_dir_ = -v_dir_;
                m_Flip = !m_Flip;
            }
        }

        if (v_dir_ == 1)
        {
            x_val_ = -dMoving;
        }
        else if (v_dir_ == -1)
        {
            x_val_ = dMoving;
        }

        if (x_pos_ + width_frame_ < 0 ||
            x_pos_ > pMap_->getMaxX())
        {
            is_alive_ = false;
        }
    }
}

void GBMonster::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_g:
        {
            break;
        }
        case SDLK_h:
        {
            break;
        }
        }
    }
}

void GBMonster::UpdateImg(SDL_Renderer* des)
{
    switch (gb_type_)
    {
    default:
    {
        LoadImg(sGoombassBase, des);
        break;
    }
    }
}

void GBMonster::Show(SDL_Renderer* des)
{
    Update();
    ThreatsObject::Show(des);
}