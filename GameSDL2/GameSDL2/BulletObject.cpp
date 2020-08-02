
#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    move_type_ = LINE_TYPE;
}

BulletObject::~BulletObject()
{
}

BulletObject* BulletObject::Clone()
{
    BulletObject* p_object_clone = new BulletObject();
    p_object_clone->bullet_dir_ = this->bullet_dir_;
    p_object_clone->is_move_ = this->is_move_;
    p_object_clone->move_type_ = this->move_type_;
    p_object_clone->x_val_ = this->x_val_;
    p_object_clone->y_val_ = this->y_val_;

    return p_object_clone;
}


void BulletObject::HandelMove(const int& x_border, const int& y_border)
{
    Map* map_data = GameMap::GetInstance()->GetMap();
    if (bullet_dir_ == DIR_RIGHT)
    {
        x_pos_ += x_val_;
        if (x_pos_ - map_data->getStartX() > x_border)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_LEFT)
    {
        x_pos_ -= x_val_;
        if (x_pos_ - map_data->getStartX() < 0)
        {
            is_move_ = false;
        }
    }
}

bool BulletObject::CheckToMap()
{
    Map* map_data = GameMap::GetInstance()->GetMap();

    int x = (x_pos_) / TILE_SIZE;
    int y = (y_pos_) / TILE_SIZE;

    bool IsInside = true;
    IsInside  = SDLCommonFunc::CheckInsideMapX(x, x);
    IsInside &= SDLCommonFunc::CheckInsideMapY(y, y);

    if (IsInside)
    {
        BlockMap* pBlock = map_data->GetTile()[y][x];
        int val = pBlock->getType();
        if ((val != BLANK_TILE))
        {
            is_move_ = false;
            x_pos_ = x * 64;
            int width_tile = pBlock->GetTile()->getWidthFrame();
            if (bullet_dir_ == DIR_LEFT)
            {
                rect_.x = x_pos_ - map_data->getStartX() + width_tile;
            }
            else
            {
                rect_.x = x_pos_ - map_data->getStartX();
            }
            return true;
        }
    }

    return false;
}

void BulletObject::Show(SDL_Renderer* des)
{
    Map* map_data = GameMap::GetInstance()->GetMap();

    rect_.x = x_pos_ - map_data->getStartX();
    rect_.y = y_pos_ - map_data->getStartY();
    BaseObject::Render(des);
}