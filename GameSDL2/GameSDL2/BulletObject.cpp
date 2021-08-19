
#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    x_scope_ = 0;
    x_up_ = 0;
    move_type_ = LINE_TYPE;
    m_blType = BL_NONE;
    m_Flip = false;
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
    p_object_clone->m_blType = this->m_blType;
    p_object_clone->x_val_ = this->x_val_;
    p_object_clone->y_val_ = this->y_val_;

    return p_object_clone;
}


void BulletObject::HandelMove(const int& x_border, const int& y_border)
{
    Map* map_data = GameMap::GetInstance()->GetMap();

    if (m_blType == BulletType::BL_CUT)
    {
        if (bullet_dir_ == DIR_RIGHT)
        {
            x_pos_ += x_val_;
            x_up_ += x_val_;
            if (x_up_ > x_scope_)
            {
                is_move_ = false;
                x_up_ = 0;
            }
        }
        else if (bullet_dir_ == DIR_LEFT)
        {
            x_pos_ -= x_val_;
            x_up_ -= x_val_;
            if (abs(x_up_) > x_scope_)
            {
                is_move_ = false;
                x_up_ = 0;
            }
        }
    }
    else if (m_blType == BulletType::BL_KNI_THROWING)
    {
        if (bullet_dir_ == DIR_RIGHT)
        {
            x_pos_ += x_val_;
            if (x_pos_ > map_data->getMaxX())
            {
                is_move_ = false;
            }
        }
        else if (bullet_dir_ == DIR_LEFT)
        {
            x_pos_ -= x_val_;
            if (x_pos_ < 0)
            {
                is_move_ = false;
            }
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
        BlockMap* pBlock = map_data->GetTile().at(y).at(x);
        if (pBlock->GetTile() != NULL)
        {
            std::string val = pBlock->getType();
            bool bSkip = GameMap::GetInstance()->CheckSkipMap(val);
            if (bSkip == false)
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
    }

    return false;
}

void BulletObject::Show(SDL_Renderer* des)
{
    Map* map_data = GameMap::GetInstance()->GetMap();
    rect_.x = x_pos_ - map_data->getStartX();
    rect_.y = y_pos_ - map_data->getStartY();

    m_Flip = is_flip;
    BaseObject::Render(des);
}