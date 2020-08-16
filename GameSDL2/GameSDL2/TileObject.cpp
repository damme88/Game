#include "TileObject.h"

BlockMap::BlockMap()
{
    x_index_ = 0;
    y_index_ = 0;
    xVal_   = 0;
    yVal_   = 0;
    m_tile  = NULL;
    m_type  = 0;
    xp_map_ = 0;
    yp_map_ = 0;
    has_mushroom_ = false;
    on_mushroom_ = false;
}

BlockMap::~BlockMap()
{
    if (m_tile != NULL)
    {
        delete m_tile;
        m_tile = NULL;
    }
}

void BlockMap::Update()
{
    SDL_Rect rect = m_tile->GetRect();
    if (yVal_ > 0)
    {
        rect.y -= yVal_;
        if (rect.y < yp_map_ - 64)
        {
            yVal_ = -yVal_;
        }
        m_tile->SetRect(xp_map_, rect.y);
    }
    else if (yVal_ < 0)
    {
        if (rect.y < yp_map_)
        {
            rect.y += abs(yVal_);
        }
        else
        {
            rect.y = yp_map_;
            yVal_ = 0;
        }
        m_tile->SetRect(xp_map_, rect.y);
    }
    else
    {
        m_tile->SetRect(xp_map_, yp_map_);
    }
}

void BlockMap::Render(SDL_Renderer* screen)
{
    if (m_tile && m_type != 0)
    {
        m_tile->Show(screen);
    }
}

void BlockMap::RemoveTile()
{
    m_type = BLANK_TILE;
    if (m_tile != NULL)
    {
        m_tile->Free();
        m_tile = NULL;
    }
}

void BlockMap::UpdateImage(SDL_Renderer* screen)
{
    char filename[40];
    sprintf_s(filename, "map//%d.png", m_type);
    m_tile->LoadImg(filename, screen);
}

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

bool TileMat::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
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


Map::Map()
{

}

Map::~Map()
{
    for (int i = 0; i < m_tile.size(); i++)
    {
        VT(BlockMap*) temp = m_tile[i];
        VT(BlockMap*)::iterator it;
        for (it = temp.begin(); it != temp.end(); it++)
        {
            delete (*it);
        }
    }
}

void Map::UpdateMapInfo(int xp, int yp)
{
    this->start_x_ = xp - (SCREEN_WIDTH / 2);

    if (this->start_x_ < 0)
    {
        this->start_x_ = 0;
    }
    else if (this->start_x_ + SCREEN_WIDTH >= this->max_x_)
    {
        this->start_x_ = this->max_x_ - SCREEN_WIDTH;
    }

    this->start_y_ = yp - (SCREEN_HEIGHT / 2);
    if (this->start_y_ < 0)
    {
        this->start_y_ = 0;
    }
    else if (this->start_y_ + SCREEN_HEIGHT >= this->max_y_)
    {
        this->start_y_ = this->max_y_ - SCREEN_HEIGHT;
    }
}