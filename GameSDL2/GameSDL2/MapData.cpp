
#include "MapData.h"

BlockMap::BlockMap()
{
    x_index_ = 0;
    y_index_ = 0;
    xVal_ = 0;
    yVal_ = 0;
    m_tile = NULL;
    m_type = "";
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
    if (m_tile && m_type != "")
    {
        m_tile->Show(screen);
    }
}

void BlockMap::RemoveTile()
{
    m_type = "";
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

Map::Map()
{

}

Map::~Map()
{
    for (int i = 0; i < m_BlockList.size(); i++)
    {
        VT(BlockMap*) temp = m_BlockList[i];
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

void Map::RemoveList()
{
    if (m_BlockList.size() > 0)
    {
        for (int i = 0; i < m_BlockList.size(); i++)
        {
            if (m_BlockList.at(i).size() > 0)
            {
                m_BlockList.at(i).clear();
            }
        }
        m_BlockList.clear();
    }
}