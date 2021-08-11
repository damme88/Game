#include "EndObject.h"



EndObject::EndObject()
{
    width_frame_ = 0;
    height_frame_ = 0;
    frame_ = 0;
    m_status = DOOR_CLOSED;

    passed_time_ = 0;
    for (int i = 0; i < FRAME_NUMS; i++)
    {
        m_DelayTime[i] = 200;
    }
}


EndObject::~EndObject()
{

}

bool EndObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret == true)
    {
        width_frame_ = rect_.w / FRAME_NUMS;
        height_frame_ = rect_.h;
        set_clips();
    }
    return ret;
}

void EndObject::set_clips()
{
    for (int i = 0; i < FRAME_NUMS; i++)
    {
        frame_clip_[i].x = width_frame_*i;
        frame_clip_[i].y = 0;
        frame_clip_[i].w = width_frame_;
        frame_clip_[i].h = height_frame_;
    }
}

void EndObject::SetPosTile(int xTile, int yTile)
{
    int xp = xTile*TILE_SIZE;
    int yp = yTile*TILE_SIZE - height_frame_;
    SetPos(xp, yp);
}

void EndObject::Show(SDL_Renderer* des)
{
    Map* pMap = GameMap::GetInstance()->GetMap();

    rect_.x = x_pos_ - pMap->getStartX();
    rect_.y = y_pos_ - pMap->getStartY();

    if (m_status == DOOR_CLOSED)
    {
        frame_ = 0;
    }
    else if (m_status == DOOR_OPENING)
    {
        if (SDL_GetTicks() - m_DelayTime[frame_] > passed_time_)
        {
            passed_time_ = SDL_GetTicks();
            frame_++;
            if (frame_ > FRAME_NUMS - 1)
            {
                frame_ = FRAME_NUMS - 1;
                m_status == DOOR_OPENED;
            }
        }
    }
    else
    {
        frame_ = FRAME_NUMS - 1;
    }

    SDL_Rect* currentClip = &frame_clip_[frame_];
    BaseObject::Render(des, currentClip);
}
