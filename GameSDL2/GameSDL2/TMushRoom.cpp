
#include "TMushRoom.h"

TMushroom::TMushroom()
{
    type_ = TH_MUSHROOM;
    idx_tile_x_ = -1;
    idx_tile_y_ = -1;
    is_fall_ = false;
}


TMushroom::~TMushroom()
{

}

void TMushroom::Update()
{
    if (is_fall_ == true)
    {
        DoPlayer();
    }
    else
    {
        y_pos_ -= y_val_;
        if (y_pos_ < (idx_tile_y_ - 1)*TILE_SIZE)
        {
            y_val_ = 0;
            is_fall_ = true;
            x_val_ = 8;
        }
    }
}

void TMushroom::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
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

void TMushroom::Show(SDL_Renderer* des)
{
    Update();
    ThreatsObject::Show(des);
}
