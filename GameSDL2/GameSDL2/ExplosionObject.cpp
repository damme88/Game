#include "ExplosionObject.h"
#include "Music.h"

ExplosionObject::ExplosionObject(void)
{
    iDelay[0] = 1000;
    iDelay[1] = 1000;
    iDelay[2] = 1000;
    iDelay[3] = 1000;
    passed_time_ = 0.0;
    m_isActive = true;
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

void ExplosionObject::SetXP(SDL_Rect rect_pos)
{
    int x_pos = rect_pos.x - frame_width_*0.5;
    int y_pos = rect_pos.y - frame_height_*0.5;

    SetRect(x_pos, y_pos);
}

void ExplosionObject::ImpRender(SDL_Renderer* screen)
{
#ifdef USE_DELAY_TIME
    // Create delay times when next frame
    if (SDL_GetTicks() - iDelay[frame_] > passed_time_)
    {
        passed_time_ = SDL_GetTicks();
        ++frame_;
        if (frame_ > FRAME_EXP - 1)
        {
            frame_ = 0;
        }
    }
#else

    frame_++;
    if (frame_ >= FRAME_EXP)
    {
        frame_ = 0;
        m_isActive = false;
    }
#endif 

    if (m_isActive)
    {
        Show(screen);
    }
}

///////////////////////////////////////////////////////////////////////////////
ExpAds* ExpAds::instance_ = NULL;
ExpAds::ExpAds()
{

}

ExpAds::~ExpAds()
{

}

void ExpAds::Render(SDL_Renderer* screen)
{
    for (int i = 0; i < m_ExpList.size(); i++)
    {
        ExplosionObject* pObj = m_ExpList.at(i);
        if (pObj != NULL)
        {
            pObj->ImpRender(screen);
        }
    }

    for (int i = 0; i < m_ExpList.size(); i++)
    {
        ExplosionObject* pObj = m_ExpList.at(i);
        if (pObj != NULL)
        {
            if (pObj->GetActive() == false)
            {
                pObj->Free();
                m_ExpList.erase(m_ExpList.begin() + i);
                i--;
            }
        }
    }
}

void ExpAds::Add(ExplosionObject* pObj)
{
    if (pObj != NULL)
    {
        m_ExpList.push_back(pObj);
    }
}