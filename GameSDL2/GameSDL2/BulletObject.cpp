
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
    m_Rotate = false;
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

bool BulletObject::Init(SDL_Renderer* screen)
{
    bool bRet = false;
    if (m_blType == BL_CUT)
    {
        bRet = LoadImg(kImgCutting, screen);
    }
    else if (m_blType == BL_KNI_THROWING)
    {
        bRet = LoadImg(kImgKni, screen);
    }
    else if (m_blType == BL_VIKING_AXE)
    {
        bRet = LoadImg(kImgVikingAxe, screen);
        m_Rotate = true;
    }
    else if (m_blType == BL_GUN)
    {
        bRet = LoadImg(kImgGunBullet, screen);
    }
    is_move_ = true;
    return bRet;
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
    else if (m_blType == BulletType::BL_KNI_THROWING ||
             m_blType == BulletType::BL_VIKING_AXE ||
             m_blType == BulletType::BL_GUN)
    {
        if (bullet_dir_ == DIR_RIGHT)
        {
            x_pos_ += x_val_;
            if (m_Rotate == true)
            {
                angle_ += 60.0;
                if (angle_ >= 360.0)
                {
                    angle_ = 0.0;
                }
            }
            
            if (x_pos_ > map_data->getMaxX())
            {
                is_move_ = false;
            }
        }
        else if (bullet_dir_ == DIR_LEFT)
        {
            x_pos_ -= x_val_;
            if (m_Rotate == true)
            {
                angle_ += 60.0;
                if (angle_ >= 360)
                {
                    angle_ = 0.0;
                }
            }

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
    SDL_Rect blRect = GetRect();
    blRect.x = x_pos_ - map_data->getStartX();
    blRect.y = y_pos_ - map_data->getStartY();

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
                SDL_Rect rectBlock = pBlock->GetTile()->GetRect();
                bool bColision = false;
                TPoint pCol;
                bool bColRect = SDLCommonFunc::CheckCollisionEx(rectBlock, blRect, pCol);
                INT xLimit = 0;
                if (bColRect)
                {
                    int xPixel = pCol.x - rectBlock.x;
                    int yPixel = pCol.y - rectBlock.y;
                    yPixel += blRect.h;
                    if (xPixel >= 0 && yPixel >= 0)
                    {
                        if (bullet_dir_ == DIR_LEFT)
                        {
                            for (int i = rectBlock.w - 1; i >= xPixel; i--)
                            {
                                DataImg* dImg = pBlock->GetTile()->GetPixelPos(i, yPixel);
                                if (dImg && !dImg->IsColorKey() && !dImg->IsWhiteKey())
                                {
                                    xLimit = i;
                                    bColision = true;
                                    break;
                                }
                            }
                        }
                        else if (bullet_dir_ == DIR_RIGHT)
                        {
                            for (int i = 0; i < xPixel; i++)
                            {
                                DataImg* dImg = pBlock->GetTile()->GetPixelPos(i, yPixel);
                                if (dImg && !dImg->IsColorKey() && !dImg->IsWhiteKey())
                                {
                                    xLimit = i - blRect.w;;
                                    bColision = true;
                                    break;
                                }
                            }
                        }
                    }
                }

                if (bColision == true)
                {
                    is_move_ = false;
                    x_pos_ = x * TILE_SIZE + xLimit;
                    rect_.x = x_pos_ - map_data->getStartX();
                    return true;
                }
            }
        }
    }

    return false;
}

void BulletObject::Show(SDL_Renderer* des)
{
    if (bullet_dir_ == DIR_LEFT)
    {
        m_Flip = true;
    }

    Map* map_data = GameMap::GetInstance()->GetMap();
    rect_.x = x_pos_ - map_data->getStartX();
    rect_.y = y_pos_ - map_data->getStartY();
    BaseObject::Render(des);
}