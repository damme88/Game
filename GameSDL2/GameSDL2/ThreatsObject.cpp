
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

    x_right_count_ = 0;
    x_left_count_ = 0;
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

void ThreatsObject::DoPlayer()
{
    if (is_alive_ == true)
    {
        y_val_ += GRAVITY_SPEED;

        if (y_val_ >= MAX_FALL_SPEED)
        {
            y_val_ = MAX_FALL_SPEED;
        }

        CheckToMap();
    }
}

void ThreatsObject::DrawBound(SDL_Renderer* des)
{
    GeometricFormat outlie_size(rect_.x, rect_.y, width_frame_, height_frame_);
    ColorData color_data1(255, 0, 255);
    Gemometric::RenderOutline(outlie_size, color_data1, des);
}

void ThreatsObject::CheckToMap()
{
    if (type_ == TH_FLY_MONSTER)
    {
        x_pos_ += x_val_;
        if (x_pos_ - pMap_->getStartX() < 0)
        {
            is_alive_ = false;
        }
    }
    else
    {
        if (on_ground_ == true)
        {
            if (x_val_ > 0)
            {
                DoRight();
            }
            else if (x_val_ < 0)
            {
                DoLeft();
            }
            x_pos_ += x_val_;

            if (x_val_ > 0)
            {
                x_right_count_++;
                x_left_count_ = 0;
            }
            else if (x_val_ < 0)
            {
                x_right_count_ = 0;
                x_left_count_++;
            }
        }

        if (y_val_ > 0)
        {
            DoDown();
        }
        else if (y_val_ < 0)
        {
            DoUp();
        }
        y_pos_ += y_val_;

        if (y_pos_ > pMap_->getMaxY())
        {
            is_alive_ = false;
        }
    }
}

void ThreatsObject::DoLeft()
{
    GameMap* pMap = GameMap::GetInstance();
    if (pMap == NULL || pMap->GetMap() == NULL)
        return;
    Map* data_map = pMap->GetMap();
    VT(VT(BlockMap*)) tile_list = data_map->GetTile();
    if (tile_list.empty() == true)
        return;

    int yPos = (y_pos_ + height_frame_ - 2);
    int xPosPrev = (x_pos_ + x_val_);

    int curTileY = yPos / TILE_SIZE;
    int prevTileX = xPosPrev / TILE_SIZE;

    int pX = xPosPrev - prevTileX*TILE_SIZE;
    int pY = yPos - curTileY*TILE_SIZE;

    bool IsInside = SDLCommonFunc::CheckInsideMap(prevTileX, curTileY);
    if (IsInside)
    {
        bool bCol = false;
        INT xLimit = 0;
        bool bCoin = false;
        int xPrev = 0;
        BlockMap* pBlock = tile_list[curTileY][prevTileX];
        if (pBlock != NULL && pBlock->GetTile() != NULL)
        {
            std::string sLType = pBlock->getType();
            bool bBlank = pMap->CheckBlank(sLType);
            if (!bBlank)
            {
                bool bSkip = pMap->CheckSkipMap(sLType);
                if (bSkip == false)
                {
                    bCoin = pMap->CheckCoinMap(sLType);
                    if (bCoin == true)
                    {

                    }
                    else
                    {
                        if (pX >= 0 && pY >= 0)
                        {
                            for (int j = TILE_SIZE - 1; j > pX; j--)
                            {
                                DataImg* pData = pBlock->GetTile()->GetPixelPos(j, pY);
                                if (pData != NULL)
                                {
                                    if (pData->IsColorKey() == false)
                                    {
                                        bCol = true;
                                        xLimit = j + 1;
                                        xPrev = prevTileX;
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    if (bCol == true)
                    {
                        x_pos_ = xPrev*TILE_SIZE + xLimit;
                        x_val_ = 0;
                        v_dir_ = -v_dir_;
                        m_Flip = !m_Flip;
                    }
                }
            }
        }
    }
    else
    {
        x_val_ = 0;
    }
}

void ThreatsObject::DoRight()
{
    GameMap* pMap = GameMap::GetInstance();
    if (pMap == NULL || pMap->GetMap() == NULL)
        return;
    Map* data_map = pMap->GetMap();
    VT(VT(BlockMap*)) tile_list = data_map->GetTile();
    if (tile_list.empty() == true)
        return;

    int nextTX = (x_pos_ + x_val_ + width_frame_) / TILE_SIZE;
    int curTY = (y_pos_ + height_frame_ - 2)/TILE_SIZE;

    int pX = (x_pos_ + x_val_ + width_frame_) - nextTX*TILE_SIZE;
    int pY = (y_pos_ + height_frame_ - 2) - curTY*TILE_SIZE;

    bool bInside = SDLCommonFunc::CheckInsideMap(nextTX, curTY);
    if (bInside)
    {
        bool bCol = false;
        int xPixelCol = 0;
        bool bCoin = false;
        int xTileCol = 0;

        BlockMap* pBlock = tile_list[curTY][nextTX];
        if (pBlock != NULL && pBlock->GetTile() != NULL)
        {
            std::string sLType = pBlock->getType();
            bool bBlank = pMap->CheckBlank(sLType);
            if (!bBlank)
            {
                bool bSkip = pMap->CheckSkipMap(sLType);
                if (bSkip == false)
                {
                    bool bCoin = pMap->CheckCoinMap(sLType);
                    if (bCoin)
                    {

                    }
                    else
                    {
                        if (pX >= 0 && pY >= 0)
                        {
                            for (int j = 0; j < pX; j++)
                            {
                                DataImg* pData = pBlock->GetTile()->GetPixelPos(j, pY);
                                if (pData != NULL)
                                {
                                    if (pData->IsColorKey() == false)
                                    {
                                        bCol = true;
                                        xTileCol = nextTX;
                                        xPixelCol = j;
                                        break;
                                    }
                                }
                            }
                        }
                    }

                    if (bCol == true)
                    {
                        x_pos_ = xTileCol*TILE_SIZE + xPixelCol - width_frame_;
                        x_val_ = 0;
                        v_dir_ = -v_dir_;
                        m_Flip = !m_Flip;
                    }
                }
            }
        }
    }
    else
    {
        x_val_ = 0;
    }
}

void ThreatsObject::DoUp()
{
    GameMap* pMap = GameMap::GetInstance();
    if (pMap == NULL || pMap->GetMap() == NULL)
        return;

    Map* data_map = pMap->GetMap();
    VT(VT(BlockMap*)) tile_list = data_map->GetTile();
    if (tile_list.empty() == true)
        return;

    int curTileX1 = (x_pos_) / TILE_SIZE;
    int xPosCur = (x_pos_ + width_frame_ - 2);
    int curTileX2 = xPosCur / TILE_SIZE;
    int prevTileY = (y_pos_ + y_val_) / TILE_SIZE;

    int pX1 = x_pos_ - curTileX1*TILE_SIZE;
    int pX2 = xPosCur - curTileX2*TILE_SIZE;
    int pY = (y_pos_ + y_val_) - prevTileY*TILE_SIZE;

    bool bInside1 = SDLCommonFunc::CheckInsideMap(curTileX1, prevTileY);
    bool bInside2 = SDLCommonFunc::CheckInsideMap(curTileX2, prevTileY);
    if (bInside1 && bInside2)
    {
        bool bCol1 = false;
        bool bCol2 = false;
        INT yLimit1 = 0;
        INT yLimit2 = 0;
        INT yLimit = 0;
        INT yPre1 = 0;
        int yPre2 = 0;
        bool bCoin1 = false;
        bool bCoin2 = false;
        BlockMap* pBlock1 = tile_list[prevTileY][curTileX1];
        if (pBlock1 != NULL && pBlock1->GetTile() != NULL)
        {
            std::string tp1 = pBlock1->getType();
            bool bBlank1 = pMap->CheckBlank(tp1);
            if (!bBlank1)
            {
                bool bSkip1 = pMap->CheckSkipMap(tp1);
                if (bSkip1 == false)
                {
                    bCoin1 = pMap->CheckCoinMap(tp1);
                    if (bCoin1 == true)
                    {
                    }
                    else
                    {
                        if (pX1 >= 0 && pY >= 0)
                        {
                            // Tim ra diem va cham pixel tren tile gan nhat voi player
                            for (int p = TILE_SIZE - 1; p > pY; p--)
                            {
                                DataImg* pData = pBlock1->GetTile()->GetPixelPos(pX1, p);
                                if (pData != NULL && pData->IsColorKey() == false)
                                {
                                    yLimit1 = p;
                                    bCol1 = true;
                                    yPre1 = prevTileY;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        BlockMap* pBlock2 = tile_list[prevTileY][curTileX2];
        if (pBlock2 != NULL && pBlock2->GetTile() != NULL)
        {
            std::string tp2 = pBlock2->getType();
            bool bBlank2 = pMap->CheckBlank(tp2);
            if (!bBlank2)
            {
                bool bSkip2 = pMap->CheckSkipMap(tp2);
                if (bSkip2 == false)
                {
                    bCoin2 = pMap->CheckCoinMap(tp2);
                    if (bCoin2 == true)
                    {

                    }
                    else
                    {
                        if (pX2 >= 0 && pY >= 0)
                        {
                            for (int p = TILE_SIZE - 1; p > pY; p--)
                            {

                                DataImg* pData = pBlock2->GetTile()->GetPixelPos(pX2, p);
                                if (pData != NULL && pData->IsColorKey() == false)
                                {
                                    yLimit2 = p;
                                    bCol2 = true;
                                    yPre2 = prevTileY;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (bCol1 && !bCol2)
        {
            yLimit = yLimit1;
        }
        else if (!bCol1 && bCol2)
        {
            yLimit = yLimit2;
        }
        else if (bCol1 && bCol2)
        {
            yLimit = max(yLimit1, yLimit2);
        }

        if (bCol1 || bCol2)
        {
            if (yLimit == yLimit1)
            {
                INT sPos = yPre1*TILE_SIZE + yLimit;
                y_pos_ = sPos;
            }
            else
            {
                INT sPos = yPre2*TILE_SIZE + yLimit;
                y_pos_ = sPos;
            }

            y_val_ = 0;
        }
    }
}

void ThreatsObject::DoDown()
{
    on_ground_ = 0;
    GameMap* pMap = GameMap::GetInstance();
    if (pMap == NULL || pMap->GetMap() == NULL)
        return;
    Map* data_map = pMap->GetMap();
    VT(VT(BlockMap*)) tile_list = data_map->GetTile();
    if (tile_list.empty() == true)
        return;

    int pX1 = 0;
    int pX2 = 0;
    int pY = 0;

    int curTileX1 = x_pos_ / TILE_SIZE;
    pX1 = x_pos_ - curTileX1*TILE_SIZE;

    int curTileX2 = (x_pos_ + width_frame_ - 2) / TILE_SIZE;
    pX2 = (x_pos_ + width_frame_) - curTileX2*TILE_SIZE;

    int yPosNext = y_pos_ + height_frame_ + y_val_;
    int nextTileY = yPosNext / TILE_SIZE;
    pY = yPosNext - nextTileY*TILE_SIZE;

    bool bInside1 = SDLCommonFunc::CheckInsideMap(curTileX1, nextTileY);
    bool bInside2 = SDLCommonFunc::CheckInsideMap(curTileX2, nextTileY);
    if (bInside1 && bInside2)
    {
        int yLimit = 0;
        int yLimit1 = 0;
        int yLimit2 = 0;
        bool bCol1 = false;
        bool bCol2 = false;
        bool bCoin1 = false;
        bool bCoin2 = false;
        int sTileY1 = 0;
        int sTileY2 = 0;
        BlockMap* pBlock1 = tile_list[nextTileY][curTileX1];
        if (pBlock1 != NULL && pBlock1->GetTile() != NULL)
        {
            std::string tp1 = pBlock1->getType();
            bool bBlank1 = pMap->CheckBlank(tp1);
            if (!bBlank1)
            {
                bool bSkip1 = pMap->CheckSkipMap(tp1);
                if (bSkip1 == false)
                {
                    bCoin1 = pMap->CheckCoinMap(tp1);
                    if (bCoin1 == true)
                    {

                    }
                    else
                    {
                        if (pX1 >= 0 && pY >= 0)
                        {
                            for (int p = 0; p < pY; p++)
                            {
                                DataImg* pData = pBlock1->GetTile()->GetPixelPos(pX1, p);
                                if (pData != NULL)
                                {
                                    if (pData->IsColorKey() == false)
                                    {
                                        yLimit1 = p;
                                        bCol1 = true;
                                        sTileY1 = nextTileY;
                                        break;
                                    }
                                }
                            }
                        }
                    }

                }
            }
        }

        BlockMap* pBlock2 = tile_list[nextTileY][curTileX2];
        if (pBlock2 != NULL && pBlock2->GetTile() != NULL)
        {
            std::string tp2 = pBlock2->getType();
            bool bBlank2 = pMap->CheckBlank(tp2);
            if (!bBlank2)
            {
                bool bSkip2 = pMap->CheckSkipMap(tp2);
                if (bSkip2 == false)
                {
                    bCoin1 = pMap->CheckCoinMap(tp2);
                    if (bCoin1 == true)
                    {

                    }
                    else
                    {
                        if (pX2 >= 0 && pY >= 0)
                        {
                            for (int p = 0; p < pY; p++)
                            {
                                DataImg* pData = pBlock2->GetTile()->GetPixelPos(pX2, p);
                                if (pData != NULL)
                                {
                                    if (pData->IsColorKey() == false)
                                    {
                                        yLimit2 = p;
                                        bCol2 = true;
                                        sTileY2 = nextTileY;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        int sTile = 0;
        if (bCol1 == true && bCol2 == false)
        {
            yLimit = yLimit1;
            sTile = sTileY1;
        }
        else if (bCol1 == false && bCol2 == true)
        {
            yLimit = yLimit2;
            sTile = sTileY2;
        }
        else if (bCol1 == true && bCol2 == true)
        {
            yLimit = min(yLimit1, yLimit2);
            if (yLimit == yLimit1)
                sTile = sTileY1;
            else
                sTile = sTileY2;
        }

        if (bCol2 == true || bCol1 == true)
        {
            int sPos = 0;
            int curTileY = sTile;
            sPos = curTileY*TILE_SIZE + yLimit - height_frame_;
            y_pos_ = sPos;
            y_val_ = 0;
            on_ground_ = true;
        }
    }
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