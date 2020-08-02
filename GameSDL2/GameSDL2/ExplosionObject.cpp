#include "ExplosionObject.h"


ExplosionObject::ExplosionObject(void)
{
}


ExplosionObject::~ExplosionObject(void)
{
}


bool ExplosionObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret == true)
    {
        frame_width_ = rect_.w / FRAME_EXP;
        frame_height_ = rect_.h;
    }

    set_clips();
    return ret;
}

void ExplosionObject::set_clips()
{
    if (frame_width_ > 0 && frame_height_ > 0)
    {
        for (int i = 0; i < FRAME_EXP; i++)
        {
            frame_clip_[i].x = frame_width_*i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = frame_width_;
            frame_clip_[i].h = frame_height_;
        }
    }
}


void ExplosionObject::Show(SDL_Renderer* screen)
{
    SDL_Rect* currentClip = &frame_clip_[frame_];
    BaseObject::Render(screen, currentClip);
}


void ExplosionObject::ImpRender(SDL_Renderer* screen, SDL_Rect& rect_pos)
{
    int x_pos = rect_pos.x - frame_width_*0.5;
    int y_pos = rect_pos.y - frame_height_*0.2;

    SetRect(x_pos, y_pos);
    frame_++;
    if (frame_ > FRAME_EXP - 1)
    {
        frame_ = 0;
    }

    Show(screen);
    Mix_PlayChannel(-1, g_sound_ex_main, 0);
}