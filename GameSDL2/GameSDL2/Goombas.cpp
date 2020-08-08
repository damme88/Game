

#include "Goombas.h"

Goombas::Goombas()
{
    is_move_ = true;
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
        case SDLK_RIGHT:
        {
            break;
        }
        }
    }
}

void Goombas::Show(SDL_Renderer* des)
{
    Update();
    ThreatsObject::Show(des);
}