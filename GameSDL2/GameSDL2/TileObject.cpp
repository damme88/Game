#include "TileObject.h"

TileMat::TileMat()
{
    is_clip_ = false;
    frame_ = 0;
    passed_time_ = 0;
    iDelay[0] = 100;
    iDelay[1] = 100;
    iDelay[2] = 100;
    iDelay[3] = 100;
}

TileMat::~TileMat()
{

}

void TileMat::SetClip()
{
    for (int i = 0; i < TILE_FRAME; i++)
    {
        frame_clip_[i].x = width_frame_*i;
        frame_clip_[i].y = 0;
        frame_clip_[i].w = width_frame_;
        frame_clip_[i].h = height_frame_;
    }
}

bool TileMat::LoadImg(std::string path, SDL_Renderer* screen, const bool& bGetPixel)
{
    bool ret = BaseObject::LoadImg(path, screen, bGetPixel);
    if (is_clip_ == true)
    {
        if (ret == true)
        {
            width_frame_ = rect_.w / TILE_FRAME;
            height_frame_ = rect_.h;

            SetClip();
        }
    }
    else
    {
        width_frame_ = rect_.w;
        height_frame_ = rect_.h;
    }

    return ret;
}

void TileMat::Show(SDL_Renderer* des)
{
    if (is_clip_ == false)
    {
        BaseObject::Render(des);
    }
    else
    {
        // Create delay times when next frame
        if (SDL_GetTicks() - iDelay[frame_] > passed_time_)
        {
            passed_time_ = SDL_GetTicks();
            ++frame_;
            if (frame_ > TILE_FRAME - 1)
            {
                frame_ = 0;
            }
        }

        SDL_Rect* currentClip = &frame_clip_[frame_];
        BaseObject::Render(des, currentClip);
    }
}