

#include "Goombas.h"

Goombas::Goombas()
{
    is_move_ = true;
    is_change_ = false;
    goom_type_ = GOOM_BASE;
}


Goombas::~Goombas()
{

}

void Goombas::Update()
{
    if (on_ground_ == 1)
    {
        if (v_dir_ == 1)
        {
            x_val_ = -5;
        }
        else if (v_dir_ == -1)
        {
            x_val_ = 5;
        }

        if (x_pos_ + width_frame_ < 0 ||
            x_pos_ > pMap_->getMaxX())
        {
            is_alive_ = false;
        }
    }
}

void Goombas::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_g:
        {
            is_change_ = true;
            goom_type_ = GOOM_HORN;
            break;
        }
        case SDLK_h:
        {
            is_change_ = true;
            goom_type_ = GOOM_HAHA;
            break;
        }
        }
    }
}

void Goombas::UpdateImg(SDL_Renderer* des)
{
    if (goom_type_ == GOOM_BASE)
    {
        LoadImg(sGoombassBase, des);
    }
    else if (goom_type_ == GOOM_HORN)
    {
        LoadImg(sGoombasGreen, des);
        y_pos_ = GROUND_POS - height_frame_ - 20;
    }
    else if (goom_type_ == GOOM_HAHA)
    {
        LoadImg(sGoombassHaha, des);
        y_pos_ = GROUND_POS - height_frame_;
        Music::GetInstance()->PlaySoundGame(Music::GOOM_BASS_HAHA);
    }
    else
    {
        LoadImg(sGoombassBase, des);
    }
}

void Goombas::Show(SDL_Renderer* des)
{
    if (is_change_ == true)
    {
        UpdateImg(des);
        is_change_ = false;
    }

    Update();
    ThreatsObject::Show(des);
}