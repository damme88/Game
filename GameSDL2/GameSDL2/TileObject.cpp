#include "TileObject.h"

BlockMap::BlockMap()
{
    x_index_ = 0;
    y_index_ = 0;
    xVal_ = 0;
    yVal_ = 0;
    m_tile = NULL;
    m_type = 0;
    xp_map_ = 0;
    yp_map_ = 0;
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
    if (m_tile)
    {
        m_tile->Render(screen);
    }
}

TileMat::TileMat()
{

}

TileMat::~TileMat()
{
}

Map::Map()
{

}

Map::~Map()
{
    for (int i = 0; i < m_tile.size(); i++)
    {
        std::vector<BlockMap*> temp = m_tile[i];
        for (std::vector<BlockMap*>::iterator it = temp.begin(); it != temp.end(); it++)
        {
            delete (*it);
        }
    }
}

void Map::CenterEntityOnMap(int xp, int yp)
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