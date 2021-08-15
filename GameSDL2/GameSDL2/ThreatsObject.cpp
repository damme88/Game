
#include "ThreatsObject.h"
#include "Geometric.h"


ThreatsObject::ThreatsObject()
{
    is_clip_ = true;
    is_alive_ = true;

    on_ground_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    frame_ = 0;
    v_dir_ = 1;

    x_val_ = 0;
    y_val_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;

    passed_time_ = 0;
    for (int i = 0; i < 8; i++)
    {
        m_DelayTime[i] = 100;
    }

    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.up_ = 0;
    input_type_.down_ = 0;
    type_ = TH_UNDEF;
    pMap_ = GameMap::GetInstance()->GetMap();
}

ThreatsObject::~ThreatsObject()
{

}

SDL_Rect ThreatsObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (is_clip_ == true)
    {
        if (ret == true)
        {
            width_frame_ = rect_.w / NUM_FRAME;
            height_frame_ = rect_.h;
        }

        set_clips();
    }
    else
    {
        width_frame_ = rect_.w;
        height_frame_ = rect_.h;
    }

    return ret;
}


void ThreatsObject::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < NUM_FRAME; i++)
        {
            frame_clip_[i].x = width_frame_*i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void ThreatsObject::DoAction()
{

}

void ThreatsObject::DrawBound(SDL_Renderer* des)
{
    GeometricFormat outlie_size(rect_.x, rect_.y, width_frame_, height_frame_);
    ColorData color_data1(255, 0, 255);
    Gemometric::RenderOutline(outlie_size, color_data1, des);
}

void ThreatsObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    ;
}

void ThreatsObject::Show(SDL_Renderer* des)
{
    if (is_alive_ == true)
    {
        rect_.x = x_pos_ - pMap_->getStartX();
        rect_.y = y_pos_ - pMap_->getStartY();

        if (is_clip_ == true)
        {
            if (SDL_GetTicks() - m_DelayTime[frame_] > passed_time_)
            {
                passed_time_ = SDL_GetTicks();
                frame_++;
                if (frame_ > NUM_FRAME - 1)
                {
                    frame_ = 0;
                }
            }

            SDL_Rect* currentClip = &frame_clip_[frame_];
            BaseObject::Render(des, currentClip);
        }
        else
        {
            BaseObject::Render(des);
        }
    }
}