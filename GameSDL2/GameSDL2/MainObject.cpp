
#include "MainObject.h"
#include "Geometric.h"
#include "TMushRoom.h"
#include "ThreatsAds.h"
#include "BlockDebris.h"

MainObject::MainObject()
{
    on_ground_ = false;
    is_falling_ = false;
    is_death_ = false;
    fast_run_ = false;
    m_bSlopeMoving = false;

    frame_ = 0;
    x_pos_ = 128;
    y_pos_ = GROUND_POS - TILE_SIZE;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = WALK_NONE;
    m_CoinCount = 0;
    level_mushroom_ = 0;
    alive_time_ = 0;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.up_ = 0;
    input_type_.down_ = 0;
    input_type_.jump_ = 0;
    m_bAttack = false;
    //is_dead_boom_ = false;

    for (int i = 0; i < PLAYER_FRAMES; i++)
    {
        iDelay[i] = 100;
    }
    passed_time_ = 0;

    m_WorldData.wld_status_ = WorldData::W_ACTIVE;
    m_WorldData.wld_number_ = 1;
}

MainObject::~MainObject()
{
    Free();
}

void MainObject::InitExp(SDL_Renderer* des)
{
    //exp_.Free();
    //exp_.LoadImg(sPlayerExp, des);
}

SDL_Rect MainObject::GetRectFrame()
{
  SDL_Rect rect;
  rect.x = rect_.x;
  rect.y = rect_.y;
  rect.w = rect_.w/ PLAYER_FRAMES;
  rect.h = rect_.h;
  return rect;
}

void MainObject::SetInfoWorlData(int number, int status)
{ 
    m_WorldData.wld_number_ = number;
    m_WorldData.wld_status_ = status; 
}

bool MainObject::CheckInputCondition()
{
    int status = m_WorldData.wld_status_;
    if (is_falling_ || is_death_ ||
        status == WorldData::W_FINISHED)
    {
        return false;
    }
    return true;
}

void MainObject::HandleInputAction(SDL_Event events,
    SDL_Renderer* screen)
{
    bool bInput = CheckInputCondition();
    if (bInput == false)
        return;

    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            status_ = WALK_RIGHT;
            input_type_.right_ = 1;
            input_type_.left_ = 0;
            UpdateImagePlayer(screen);
            break;
        }
        case SDLK_LEFT:
        {
            status_ = WALK_LEFT;
            input_type_.left_ = 1;
            input_type_.right_ = 0;
            UpdateImagePlayer(screen);
            break;
        }
        case SDLK_DOWN:
        {
            /* input_type_.up_ = 0;
             input_type_.down_ = 1;
             UpdateImagePlayer(screen);*/
            break;
        }
        case SDLK_RSHIFT:
        case SDLK_LSHIFT:
        {
            fast_run_ = true;
        }
        break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            input_type_.right_ = 0;
            break;
        case SDLK_LEFT:
            input_type_.left_ = 0;
            break;
        case SDLK_DOWN:
        {
            ;// input_type_.down_ = 0;
        }
        break;
        case SDLK_RSHIFT:
        case SDLK_LSHIFT:
        {
            fast_run_ = false;
        }
        break;
        }
    }
    else if (events.type == SDL_MOUSEBUTTONDOWN)
    {
        if (events.button.button == SDL_BUTTON_LEFT)
        {
            if (m_bAttack == false)
            {
                m_bAttack = true;
                BulletObject* p_bullet = new BulletObject();
                p_bullet->LoadImg(kImgBullet, screen);

                Music::GetInstance()->PlaySoundGame(Music::FIRE_SOUND);

                if (status_ == WALK_LEFT)
                {
                    p_bullet->set_dir_bullet(BulletObject::DIR_LEFT);
                    INT xBul = x_pos_;
                    INT yBul = y_pos_ + height_frame_*0.25;
                    p_bullet->set_xy_pos(xBul, yBul);
                }
                else
                {
                    INT xBul = x_pos_ + width_frame_;
                    INT yBul = y_pos_ + height_frame_*0.25;
                    p_bullet->set_dir_bullet(BulletObject::DIR_RIGHT);
                    p_bullet->set_xy_pos(xBul, yBul);
                }
                p_bullet->set_x_val(10);
                p_bullet->set_x_Scope(45);
                p_bullet->set_is_move(true);
                p_bullet_list_.push_back(p_bullet);
            }
        }
        else if (events.button.button == SDL_BUTTON_RIGHT)
        {
            Music::GetInstance()->PlaySoundGame(Music::JUMP_SOUND);
            input_type_.jump_ = 1;
            input_type_.down_ = 0;
        }
    }
    else if (events.type == SDL_MOUSEBUTTONUP)
    {
        if (events.button.button == SDL_BUTTON_LEFT)
        {
        }
        else if (events.button.button == SDL_BUTTON_RIGHT)
        {
            input_type_.jump_ = 0;
        }
    }
}

void MainObject::UpdateCtrlState(int ctrl_type, SDL_Renderer* screen)
{
    if (ctrl_type == 1) // RIGHT
    {
        status_ = WALK_RIGHT;
        input_type_.right_ = 1;
        input_type_.left_ = 0;
        UpdateImagePlayer(screen);
    }
    else if(ctrl_type == 2) //LEFT:
    {
        status_ = WALK_LEFT;
        input_type_.left_ = 1;
        input_type_.right_ = 0;
        UpdateImagePlayer(screen);
    }
    else if (ctrl_type == 3) //DOWN:
    {
        input_type_.up_ = 0;
        input_type_.down_ = 1;
        UpdateImagePlayer(screen);
    }
    else if (ctrl_type == 0)
    {
        input_type_.right_ = 0;
        input_type_.left_ = 0;
        input_type_.up_ = 0;
        input_type_.down_ = 0;
    }
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
    for (int i = 0; i < p_bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = p_bullet_list_.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move())
            {
                p_bullet->HandelMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                bool ret = p_bullet->CheckToMap();
                if (ret == true)
                {
                    SDL_Rect rect_pos = p_bullet->GetRect();
                    //exp_.ImpRender(des, rect_pos);
                    continue;
                }
                else
                {
                    p_bullet->SetFlip(m_Flip);
                    p_bullet->Show(des);
                }
            }
            else
            {
                RemoveBullet(i);
            }
        }
    }
}

void MainObject::RemoveBullet(const int& idx)
{
    if (p_bullet_list_.size() > 0 && idx < p_bullet_list_.size())
    {
        BulletObject* p_bullet = p_bullet_list_.at(idx);
        p_bullet_list_.erase(p_bullet_list_.begin() + idx);

        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

std::vector<BulletObject*> MainObject::get_bullet_list() const 
{ 
    return p_bullet_list_; 
}

void MainObject::set_bullet_list(VT(BulletObject*) bullet_list)
{
    p_bullet_list_ = bullet_list;
}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
  bool ret = BaseObject::LoadImg(path, screen);
  if (ret == true)
  {
    width_frame_ = rect_.w/PLAYER_FRAMES;
    height_frame_ = rect_.h;
    set_clips();
  }
  return ret;
}

void MainObject::set_clips()
{
  if (width_frame_ > 0 && height_frame_ > 0)
  {
      for (int i = 0; i < PLAYER_FRAMES; i++)
      {
          frame_clip_[i].x = width_frame_*i;
          frame_clip_[i].y = 0;
          frame_clip_[i].w = width_frame_;
          frame_clip_[i].h = height_frame_;
      }
  }
}

void MainObject::DrawBound(SDL_Renderer* des)
{
    GeometricFormat outlie_size(rect_.x, rect_.y, width_frame_, height_frame_);
    ColorData color_data1(255, 255, 255);
    Gemometric::RenderOutline(outlie_size, color_data1, des);
}

void MainObject::Show(SDL_Renderer* des)
{
    if (m_WorldData.wld_status_ == WorldData::W_FINISHED ||
        is_falling_ == true)
    {
        return;
    }

    //DrawBound(des);
    UpdateImagePlayer(des);

    if (m_bAttack == true)
    {
        rect_.x = x_pos_ - start_map_x_;
        rect_.y = y_pos_ - start_map_y_;

        // Create delay times when next frame
        if (SDL_GetTicks() - iDelay[frame_] > passed_time_)
        {
            passed_time_ = SDL_GetTicks();
            ++frame_;
            if (frame_ > PLAYER_FRAMES - 1)
            {
                frame_ = 0;
                m_bAttack = false;
            }
        }

        SDL_Rect* currentClip = &frame_clip_[frame_];
        BaseObject::Render(des, currentClip);
    }
    else if (is_death_)
    {
        rect_.x = x_pos_ - start_map_x_;
        rect_.y = y_pos_ - start_map_y_;

        // Create delay times when next frame
        if (SDL_GetTicks() - iDelay[frame_] > passed_time_)
        {
            passed_time_ = SDL_GetTicks();
            ++frame_;
            if (frame_ > PLAYER_FRAMES - 1)
            {
                frame_ = 0;
                is_falling_ = true;
            }
        }

        if (is_falling_ == false)
        {
            SDL_Rect* currentClip = &frame_clip_[frame_];
            BaseObject::Render(des, currentClip);
        }
    }
    else
    {
        if (input_type_.left_ == 1 || input_type_.right_ == 1)
        {
            frame_++;
        }
        else
        {
            frame_ = 0;
        }

        if (frame_ >= PLAYER_FRAMES)
        {
            frame_ = 0;
        }


        rect_.x = x_pos_ - start_map_x_;
        rect_.y = y_pos_ - start_map_y_;

        SDL_Rect* currentClip = &frame_clip_[frame_];
        BaseObject::Render(des, currentClip);
    }
}

void MainObject::DoPlayer(SDL_Renderer* des)
{
    if (m_WorldData.wld_status_ == WorldData::W_FINISHED)
    {
        return;
    }

    Map* data_map = GameMap::GetInstance()->GetMap();
    start_map_x_ = data_map->getStartX();
    start_map_y_ = data_map->getStartY();

    if (is_falling_ == false)
    {
        x_val_ = 0;
        y_val_ += GRAVITY_SPEED;
        
        if (y_val_ >= MAX_FALL_SPEED)
        {
            y_val_ = MAX_FALL_SPEED;
        }

        if (input_type_.left_ == 1)
        {
            x_val_ = -PLAYER_SPEED;
            if (fast_run_ == true)
            {
                x_val_*= 1.5;
            }
        }
        else if (input_type_.right_ == 1)
        {
            x_val_ = PLAYER_SPEED;
            if (fast_run_ == true)
            {
                x_val_ *= 1.5;
            }
        }

        if (input_type_.jump_ == 1)
        {
            if (on_ground_ == true)
            {
                y_val_ = -PLAYER_HIGHT_VAL;
            }

            input_type_.jump_ = 0;
            on_ground_ = false;
        }

        CheckToMap(des);
        data_map->UpdateMapInfo(x_pos_, y_pos_);
    }
    else
    {
        if (alive_time_ > 0)
        {
            alive_time_ -= 1;
        }
        else
        {
            alive_time_ = 0;
            is_falling_ = false;
            is_death_ = false;
            Music::GetInstance()->PauseMusic();
        }
    }
}

BlockMap* MainObject::GetBlockMap(int y, int x)
{
    BlockMap* pBlock = NULL;
    GameMap* pMap = GameMap::GetInstance();
    if (pMap != NULL && pMap->GetMap())
    {
        Map* data_map = pMap->GetMap();
        VT(VT(BlockMap*)) tile_list = data_map->GetTile();
        if (tile_list.empty() == false)
        {
            UINT yNum = tile_list.size();
            if (y >= 0 && y < yNum)
            {
                UINT xNum = tile_list[y].size();
                if (x >= 0 && x < xNum)
                {
                    pBlock = tile_list[y][x];
                }
            }
        }
    }

    return pBlock;
}

void MainObject::CheckToMap(SDL_Renderer* des)
{
    if (is_death_ == true)
        return;

    GameMap* pMap = GameMap::GetInstance();
    if (pMap == NULL || pMap->GetMap() == NULL)
        return;
    Map* data_map = pMap->GetMap();

    if (x_val_ > 0) // MOVE RIGHT
    {
        DoRight();
    }
    else if (x_val_ < 0) // MOVE LEFT
    {
        DoLeft();
    }

    if (m_bSlopeMoving == true)
    {
        if (x_val_ > 0)
        {
            double angle = M_PI / 4;
            double x_a = sin(angle)*x_val_;
            double y_a = cos(angle)*x_val_;
            x_pos_ += x_a;
            y_pos_ -= y_a;
        }
    }
    else
    {
        x_pos_ += x_val_;
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

    if (x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ >= data_map->getMaxX())
    {
        x_pos_ = data_map->getMaxX() - width_frame_ - EPXILON;
    }

    if (y_pos_ > data_map->getMaxY() + 100)
    {
        is_falling_ = true;
    }
}

void MainObject::DoLeft()
{
    GameMap* pMap = GameMap::GetInstance();
    if (pMap == NULL || pMap->GetMap() == NULL)
        return;

    Map* data_map = pMap->GetMap();
    VT(VT(BlockMap*)) tile_list = data_map->GetTile();
    if (tile_list.empty() == true)
        return;

    int yPos = (y_pos_ + height_frame_ - EPXILON);
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
        BlockMap* pBlock = GetBlockMap(curTileY, prevTileX);
        if (pBlock != NULL)
        {
            if (pBlock->GetTile() != NULL)
            {
                std::string sLType = pBlock->getType();
                bool bSkip = pMap->CheckSkipMap(sLType);
                if (bSkip == false)
                {
                    bCoin = pMap->CheckCoinMap(sLType);
                    if (bCoin == true)
                    {
                        pBlock->RemoveTile();
                        this->DoUpCoin();
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

void MainObject::DoRight()
{
    GameMap* pMap = GameMap::GetInstance();
    if (pMap == NULL || pMap->GetMap() == NULL)
        return;

    Map* data_map = pMap->GetMap();
    VT(VT(BlockMap*)) tile_list = data_map->GetTile();
    if (tile_list.empty() == true)
        return;

    int xPosNext = (x_pos_ + width_frame_ + x_val_);
    int yPosEnd = (y_pos_ + height_frame_ - EPXILON);

    int nextTileX = xPosNext / TILE_SIZE;
    int curTileY = yPosEnd / TILE_SIZE;

    int pX = xPosNext - nextTileX*TILE_SIZE;
    int pY = yPosEnd - curTileY*TILE_SIZE;

    bool IsInside = SDLCommonFunc::CheckInsideMap(nextTileX, curTileY);
    if (IsInside)
    {
        bool bCol = false;
        int xPixelCol = 0;
        bool bCoin = false;
        int xTileCol = 0;
        BlockMap* pBlock = GetBlockMap(curTileY, nextTileX);
        if (pBlock != NULL)
        {
            if (pBlock->GetTile() != NULL)
            {
                std::string sLType = pBlock->getType();
                bool bSkip = pMap->CheckSkipMap(sLType);
                if (bSkip == false)
                {
                    bCoin = pMap->CheckCoinMap(sLType);
                    if (bCoin == true)
                    {
                        pBlock->RemoveTile();
                        this->DoUpCoin();
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
                                        xTileCol = nextTileX;
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

void MainObject::DoUp()
{
    GameMap* pMap = GameMap::GetInstance();
    if (pMap == NULL || pMap->GetMap() == NULL)
        return;

    Map* data_map = pMap->GetMap();
    VT(VT(BlockMap*)) tile_list = data_map->GetTile();
    if (tile_list.empty() == true)
        return;

    int curTileX1 = (x_pos_) / TILE_SIZE;
    int xPosCur = (x_pos_ + width_frame_ - EPXILON);
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
        BlockMap* pBlock1 = GetBlockMap(prevTileY, curTileX1);
        if (pBlock1 != NULL)
        {
            if (pBlock1->GetTile() != NULL)
            {
                std::string tp1 = pBlock1->getType();
                bool bSkip1 = pMap->CheckSkipMap(tp1);
                if (bSkip1 == false)
                {
                    bCoin1 = pMap->CheckCoinMap(tp1);
                    if (bCoin1 == true)
                    {
                        pBlock1->RemoveTile();
                        this->DoUpCoin();
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

        BlockMap* pBlock2 = GetBlockMap(prevTileY, curTileX2);
        if (pBlock2 != NULL)
        {
            if (pBlock2->GetTile() != NULL)
            {
                std::string tp2 = pBlock2->getType();
                bool bSkip2 = pMap->CheckSkipMap(tp2);
                if (bSkip2 == false)
                {
                    bCoin2 = pMap->CheckCoinMap(tp2);
                    if (bCoin2 == true)
                    {
                        pBlock2->RemoveTile();
                        this->DoUpCoin();
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

void MainObject::DoDown()
{
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

    int curTileX2 = (x_pos_ + width_frame_ - EPXILON) / TILE_SIZE;
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
        BlockMap* pBlock1 = GetBlockMap(nextTileY, curTileX1);
        if (pBlock1 != NULL)
        {
            if (pBlock1->GetTile() != NULL)
            {
                std::string tp1 = pBlock1->getType();
                bool bSkip1 = pMap->CheckSkipMap(tp1);
                if (bSkip1 == false)
                {
                    bCoin1 = pMap->CheckCoinMap(tp1);
                    if (bCoin1 == true)
                    {
                        pBlock1->RemoveTile();
                        this->DoUpCoin();
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

        BlockMap* pBlock2 = GetBlockMap(nextTileY, curTileX2);
        if (pBlock2 != NULL)
        {
            if (pBlock2->GetTile() != NULL)
            {
                std::string tp2 = pBlock2->getType();
                bool bSkip2 = pMap->CheckSkipMap(tp2);
                if (bSkip2 == false)
                {
                    bCoin1 = pMap->CheckCoinMap(tp2);
                    if (bCoin1 == true)
                    {
                        pBlock1->RemoveTile();
                        this->DoUpCoin();
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
            int curTileY = sTile - 1;
            sPos = curTileY*TILE_SIZE + yLimit;
            y_pos_ = sPos;
            y_val_ = 0;
            on_ground_ = true;
            if (status_ == WALK_NONE)
            {
                status_ = WALK_RIGHT;
            }
        }
    }
}

void MainObject::DoUpCoin()
{
    m_CoinCount++;
    Music::GetInstance()->PlaySoundGame(Music::COIN_INCREASING);
}


void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
    if (is_death_ == true)
    {
        LoadImg(sPlayerDeath, des);
    }
    else
    {
        if (on_ground_ == true)
        {
            if (m_bAttack)
            {
                LoadImg(sPlayerAttack, des);
            }
            else
            {
                if (input_type_.down_ == 0)
                {
                    LoadImg(sPlayerMove, des);
                }
                else if (input_type_.down_ == 1)
                {
                    LoadImg(sPlayerDown, des);
                }
            }
            if (status_ == WALK_LEFT)
            {
                m_Flip = true;
            }
            else
            {
                m_Flip = false;
            }
        }
        else
        {
            if (m_bAttack)
            {
                LoadImg(sPlayerAttack, des);
            }
            else
            {
                // when implement Jump.
                LoadImg(sPlayerJump, des);
                if (status_ == WALK_RIGHT)
                {
                    m_Flip = false;
                }
                else
                {
                    m_Flip = true;
                }
            }
        }
    }
}

void MainObject::ResetAlive()
{
    GameMap* pMap = GameMap::GetInstance();
    if (pMap == NULL) return;

    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.jump_ = 0;
    input_type_.down_ = 0;
    input_type_.up_ = 0;

    int current_xp = x_pos_;
    int current_yp = GROUND_POS - 64;

    current_xp -= TILE_SIZE * 5;
    SDL_Rect rect;
    rect.x = x_pos_ - start_map_x_;
    rect.y = current_yp - start_map_y_;
    SetRect(rect.x, rect.y);

    x_pos_ = current_xp;
    y_pos_ = current_yp;
}

void MainObject::ReStart()
{
    on_ground_ = false;
    is_falling_ = false;
    is_death_ = false;
    fast_run_ = false;
    m_bSlopeMoving = false;

    frame_ = 0;
    x_pos_ = 128;
    y_pos_ = GROUND_POS - TILE_SIZE;
    x_val_ = 0;
    y_val_ = 0;
    alive_time_ = 0;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.up_ = 0;
    input_type_.down_ = 0;
    input_type_.jump_ = 0;
    m_bAttack = false;
    m_WorldData.wld_status_ = WorldData::W_ACTIVE;
}