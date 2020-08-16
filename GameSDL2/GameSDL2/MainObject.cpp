
#include "MainObject.h"
#include "Geometric.h"
#include "TMushRoom.h"
#include "ThreatsAds.h"

MainObject::MainObject()
{
  frame_ = 0;
  x_pos_ = 128;
  y_pos_ = GROUND_POS - TILE_SIZE;
  x_val_ = 0;
  y_val_ = 0;
  width_frame_ = 0;
  height_frame_ = 0;
  status_ = WALK_NONE;
  money_count_ = 0;
  on_ground_ = false;
  is_falling_ = false;
  is_death_ = false;
  alive_time_ = 0;
  fast_run_ = false;

  input_type_.left_ = 0;
  input_type_.right_ = 0;
  input_type_.up_ = 0;
  input_type_.down_ = 0;
  input_type_.jump_ = 0;
  //is_dead_boom_ = false;
}

MainObject::~MainObject()
{
  Free();
}

void MainObject::InitExp(SDL_Renderer* des)
{
    exp_.Free();
    exp_.LoadImg(sPlayerExp, des);
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

void MainObject::HandleInputAction(SDL_Event events,
    SDL_Renderer* screen)
{
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
            input_type_.up_ = 0;
            input_type_.down_ = 1;
            UpdateImagePlayer(screen);
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
            input_type_.down_ = 0;
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
            BulletObject* p_bullet = new BulletObject();
            p_bullet->LoadImg(kImgBullet, screen);

            Music::GetInstance()->PlaySoundGame(Music::FIRE_SOUND);

            if (status_ == WALK_LEFT)
            {
                p_bullet->set_dir_bullet(BulletObject::DIR_LEFT);
                p_bullet->set_xy_pos(x_pos_, y_pos_ + height_frame_*0.22);
            }
            else
            {
                p_bullet->set_dir_bullet(BulletObject::DIR_RIGHT);
                p_bullet->set_xy_pos(x_pos_ + width_frame_ - 20, y_pos_ + height_frame_*0.22);
            }
            p_bullet->set_x_val(20);
            p_bullet->set_is_move(true);
            p_bullet_list_.push_back(p_bullet);
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
                    exp_.ImpRender(des, rect_pos);
                    continue;
                }
                else
                {
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
    //DrawBound(des);
    UpdateImagePlayer(des);

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

    if (is_falling_ == false)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;

        SDL_Rect* currentClip = &frame_clip_[frame_];
        BaseObject::Render(des, currentClip);
    }
}

void MainObject::DoPlayer(SDL_Renderer* des)
{
    Map* data_map = GameMap::GetInstance()->GetMap();
    map_x_ = data_map->getStartX();
    map_y_ = data_map->getStartY();

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

void MainObject::CheckToMap(SDL_Renderer* des)
{
    GameMap* pMap = GameMap::GetInstance();
    if (pMap == NULL) return;

    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    bool IsMoney = false;

    Map* data_map = pMap->GetMap();
    VT(VT(BlockMap*)) tile_list = data_map->GetTile();

    if (is_death_ == false)
    {
        x1 = (x_pos_ + x_val_) / TILE_SIZE;
        x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

        y1 = (y_pos_) / TILE_SIZE;
        y2 = (y_pos_ + height_frame_ - 1) / TILE_SIZE;

        // Check x1, x2 with full width of map
        // Check y1, y2 with full height of map
        bool IsInside = SDLCommonFunc::CheckInsideMapX(x1, x2);
        IsInside &= SDLCommonFunc::CheckInsideMapY(y1, y2);
        if (IsInside)
        {
            if (x_val_ > 0) //moving right
            {
                int tp1 = tile_list[y1][x2]->getType();
                int tp2 = tile_list[y2][x2]->getType();

                IsMoney = pMap->ChecTileMoney(tp1);
                IsMoney |= pMap->ChecTileMoney(tp2);

                if (IsMoney)
                {
                    tile_list[y1][x2]->RemoveTile();
                    tile_list[y2][x2]->RemoveTile();
                    IncreaseMoney();
                }
                else
                {
                    bool IsBlank1 = pMap->CheckBlank(tp1);
                    bool IsBlank2 = pMap->CheckBlank(tp2);
                    if (!IsBlank1 || !IsBlank2)
                    {
                        // Fixed post of object at current post of map.
                        // => Cannot moving when press button
                        x_pos_ = x2 * TILE_SIZE;
                        x_pos_ -= width_frame_ + 1;
                        x_val_ = 0; // cannot moving
                    }
                }

            }
            else if (x_val_ < 0) //moving left 
            {
                int tp1 = tile_list[y1][x1]->getType();
                int tp2 = tile_list[y2][x1]->getType();

                IsMoney = pMap->ChecTileMoney(tp1);
                IsMoney |= pMap->ChecTileMoney(tp2);
                if (IsMoney)
                {
                    tile_list[y1][x1]->RemoveTile();
                    tile_list[y2][x1]->RemoveTile();
                    IncreaseMoney();
                }
                else
                {
                    bool IsBlank1 = pMap->CheckBlank(tp1);
                    bool IsBlank2 = pMap->CheckBlank(tp2);
                    if (!IsBlank1 || !IsBlank2)
                    {
                        x_pos_ = (x1 + 1) * TILE_SIZE;
                        x_val_ = 0;
                    }
                }
            }
        }

        // Check vertical
        int width_min = SDLCommonFunc::GetMin(width_frame_, TILE_SIZE);

        x1 = (x_pos_) / TILE_SIZE;
        x2 = (x_pos_ + width_min) / TILE_SIZE;

        y1 = (y_pos_ + y_val_) / TILE_SIZE;
        y2 = (y_pos_ + y_val_ + height_frame_) / TILE_SIZE;

        IsInside = SDLCommonFunc::CheckInsideMapX(x1, x2);
        IsInside &= SDLCommonFunc::CheckInsideMapY(y1, y2);
        if (IsInside)
        {
            if (y_val_ > 0)
            {
                //Similar for vertical
                int tp1 = tile_list[y2][x1]->getType();
                int tp2 = tile_list[y2][x2]->getType();

                IsMoney = pMap->ChecTileMoney(tp1);
                IsMoney |= pMap->ChecTileMoney(tp2);
                if (IsMoney)
                {
                    tile_list[y2][x1]->RemoveTile();
                    tile_list[y2][x2]->RemoveTile();
                    IncreaseMoney();
                }
                else
                {
                    bool IsBlank1 = pMap->CheckBlank(tp1);
                    bool IsBlank2 = pMap->CheckBlank(tp2);

                    if (!IsBlank1 || !IsBlank2)
                    {
                        y_pos_ = y2 * TILE_SIZE;
                        y_pos_ -= height_frame_;
                        y_val_ = 0;

                        on_ground_ = true;
                        if (status_ == WALK_NONE)
                        {
                            //input_type_.right_ = 1;
                            status_ = WALK_RIGHT;
                        }
                    }
                }
            }
            else if (y_val_ < 0)
            {
                int tp1 = tile_list[y1][x1]->getType();
                int tp2 = tile_list[y1][x2]->getType();

                IsMoney = pMap->ChecTileMoney(tp1);
                IsMoney |= pMap->ChecTileMoney(tp2);
                if (IsMoney)
                {
                    tile_list[y1][x2]->RemoveTile();
                    tile_list[y1][x2]->RemoveTile();
                    IncreaseMoney();
                }
                else
                {
                    bool IsBlank1 = pMap->CheckBlank(tp1);
                    bool IsBlank2 = pMap->CheckBlank(tp2);

                    if (!IsBlank1 || !IsBlank2)
                    {
                        y_pos_ = (y1 + 1) * TILE_SIZE;
                        y_val_ = 0;

                        int xd;
                        int yd;
                        if (!IsBlank1)
                        {
                            xd = x1;
                            yd = y1;
                        }
                        else
                        {
                            xd = x2;
                            yd = y1;
                        }

                        bool checkMushroom = tile_list[yd][xd]->GetHasMushroom();
                        if (checkMushroom == true)
                        {
                            BlockMap* pBlock = tile_list[yd][xd];
                            pBlock->setType(BLOCK_USED);
                            pBlock->UpdateImage(des);
                            pBlock->SetHasMushroom(false);
                            TMushroom* pMushRoom = new TMushroom();
                            bool ret = pMushRoom->LoadImg("img//mushroom.png", des);
                            if (ret)
                            {
                                SDL_Rect Rect = pBlock->GetTile()->GetRect();
                                int x_pos = Rect.x + data_map->getStartX();
                                int y_pos = Rect.y + data_map->getStartY();
                                pMushRoom->set_clips();
                                pMushRoom->set_xpos(x_pos);
                                pMushRoom->set_ypos(y_pos);
                                pMushRoom->set_y_val(4);
                                pMushRoom->SetIdxTile(xd, yd);
                                ThreatsAds::GetInstance()->AddSecondObject(pMushRoom);
                            }
                        }
                        else
                        {
                            if (!IsBlank1)
                            {
                                if (tile_list[y1][x1]->getType() != BLOCK_USED)
                                {
                                    tile_list[y1][x1]->setYVal(16);
                                }
                                
                            }
                            else
                            {
                                if (!IsBlank2)
                                {
                                    if (tile_list[y1][x2]->getType() != BLOCK_USED)
                                    {
                                        tile_list[y1][x2]->setYVal(16);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        x_pos_ += x_val_;
        y_pos_ += y_val_;
    }
    else
    {
        /*if (is_dead_boom_ == true)
        {
            y_pos_ -= y_val_;
        }
        else
        {*/
            x_pos_ += 0.3*x_val_;
            y_pos_ += 0.3*y_val_;
        //}
    }

    if (x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ >= data_map->getMaxX())
    {
        x_pos_ = data_map->getMaxX() - width_frame_ - 1;
    }

    if (y_pos_ > data_map->getMaxY() + 100)
    {
        is_falling_ = true;
    }

    //if (y_pos_ < 0)
    //{
    //    is_falling_ = true;
    //}
}

void MainObject::IncreaseMoney()
{
    money_count_++;
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
            if (input_type_.down_ == 0)
            {
                LoadImg(sPlayerMove, des);
            }
            else if (input_type_.down_ == 1)
            {
                LoadImg(sPlayerDown, des);
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

void MainObject::ResetAlive()
{
    GameMap* pMap = GameMap::GetInstance();
    if (pMap == NULL) return;

    int current_xp = x_pos_;
    int current_yp = GROUND_POS - 64;

    current_xp -= TILE_SIZE * 5;
    SDL_Rect rect;
    rect.x = x_pos_ - map_x_;
    rect.y = current_yp - map_y_;
    SetRect(rect.x, rect.y);

    x_pos_ = current_xp;
    y_pos_ = current_yp;
}