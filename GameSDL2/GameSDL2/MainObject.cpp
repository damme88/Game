
#include "MainObject.h"
#include "Geometric.h"
#define  NUM_FRAME 4

MainObject::MainObject()
{
  frame_ = 0;
  x_pos_ = 128;
  y_pos_ = SCREEN_HEIGHT - 128;
  x_val_ = 0;
  y_val_ = 0;
  think_time_ = 0;
  width_frame_ = 0;
  height_frame_ = 0;
  status_ = WALK_NONE;
  money_count_ = 0;
  on_ground_ = false;
  is_falling_ = false;
  input_type_.left_ = 0;
  input_type_.right_ = 0;
  input_type_.up_ = 0;
  input_type_.down_ = 0;
  input_type_.jump_ = 0;
}

MainObject::~MainObject()
{
  Free();
}

void MainObject::InitExp(SDL_Renderer* des)
{
    exp_.Free();
    exp_.LoadImg("img//bl_map.png", des);
}

SDL_Rect MainObject::GetRectFrame()
{
  SDL_Rect rect;
  rect.x = rect_.x;
  rect.y = rect_.y;
  rect.w = rect_.w/NUM_FRAME;
  rect.h = rect_.h;
  return rect;
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound[3]) 
{
  if( events.type == SDL_KEYDOWN )
  {
    switch( events.key.keysym.sym )
    {
    case SDLK_RIGHT: 
      {
        status_  = WALK_RIGHT;
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
        }
        break;
    case SDLK_UP:
      {
        //input_type_.up_ = 1;
        //input_type_.down_ = 0;
        //UpdateImagePlayer(screen);
      }
      break;
    }
  }
  //If a key was released
  else if( events.type == SDL_KEYUP )
  {
    //Set the velocity
    switch( events.key.keysym.sym )
    {
    case SDLK_RIGHT: 
        input_type_.right_ = 0;
        break;
    case SDLK_LEFT: 
        input_type_.left_ = 0; 
        break;
    case SDLK_UP:
        {
            //input_type_.up_ = 0;
            // UpdateImagePlayer(screen);
            // y_pos_ += height_frame_;
        }
        break;
     case SDLK_DOWN:
         {
              input_type_.down_ = 0;
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
      p_bullet->SetMapXY(map_x_, map_y_);
#ifdef USE_AUDIO 
      int ret = Mix_PlayChannel(-1, bullet_sound[0], 0 );
#endif
      if (status_ == WALK_LEFT)
      {
        if (input_type_.up_ == 1)
        {
            if (input_type_.left_ == 0)
            {
                p_bullet->set_dir_bullet(BulletObject::DIR_UP);
                p_bullet->set_xy_pos(x_pos_ + width_frame_*0.35, y_pos_ + 15);
            }
            else
            {
                p_bullet->set_dir_bullet(BulletObject::DIR_UP_LEFT);
                p_bullet->set_xy_pos(x_pos_, y_pos_ + 5);
            }
            
        }
        else
        {
            p_bullet->set_dir_bullet(BulletObject::DIR_LEFT);
            p_bullet->set_xy_pos(x_pos_, y_pos_ + height_frame_*0.22);
        }
      }
      else
      {
          if (input_type_.up_ == 1)
          {
              if (input_type_.right_ == 1)
              {
                  p_bullet->set_dir_bullet(BulletObject::DIR_UP_RIGHT);
                  p_bullet->set_xy_pos(x_pos_ + width_frame_, y_pos_ + 5);
              }
              else
              {
                  p_bullet->set_dir_bullet(BulletObject::DIR_UP);
                  p_bullet->set_xy_pos(x_pos_ + width_frame_*0.45, y_pos_ + 15);
              }
              
          }
          else
          {
              p_bullet->set_dir_bullet(BulletObject::DIR_RIGHT);
              p_bullet->set_xy_pos(x_pos_ + width_frame_ - 20, y_pos_ + height_frame_*0.22);
          }
      }

      p_bullet->set_x_val(20);
      p_bullet->set_y_val(20);
      p_bullet->set_is_move(true);
      p_bullet_list_.push_back(p_bullet);
    }
    else if (events.button.button == SDL_BUTTON_RIGHT)
    {
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
        if (p_bullet != NULL)
        {
          p_bullet_list_.erase(p_bullet_list_.begin() + i);
          delete p_bullet;
          p_bullet = NULL;
        }
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

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
  bool ret = BaseObject::LoadImg(path, screen);

  if (ret == true)
  {
    width_frame_ = rect_.w/NUM_FRAME;
    height_frame_ = rect_.h;

    set_clips();
  }

  return ret;
}

void MainObject::set_clips()
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

    if ((input_type_.left_ == 1 ||
        input_type_.right_ == 1))
    {
        frame_++;
    }
    else
    {
        frame_ = 0;
    }

    if (frame_ >= NUM_FRAME)
    {
        frame_ = 0;
    }

    if (think_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;

        SDL_Rect* currentClip = &frame_clip_[frame_];
        BaseObject::Render(des, currentClip);
    }
}

void MainObject::DoPlayer()
{
  map_x_ = GameMap::GetInstance()->GetMap()->getStartX();
  map_y_ = GameMap::GetInstance()->GetMap()->getStartY();

  if (think_time_ == 0)
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
    }
    else if (input_type_.right_ == 1)
    {
      x_val_= PLAYER_SPEED;
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

    CheckToMap();

    CenterEntityOnMap();
  }

  if (think_time_ > 0)
  {
    think_time_--;

    if (think_time_ == 0)
    {
        if (x_pos_ > 256)
        {
            x_pos_ -= 256;
        }
        else
            x_pos_ = 0;
      y_pos_ = 0;
      x_val_ = 0;
      y_val_ = 0;
      on_ground_ = false;
    }
  }
}

void MainObject::CenterEntityOnMap()
{
  Map* data_map = GameMap::GetInstance()->GetMap();
  data_map->CenterEntityOnMap(x_pos_, y_pos_);
}

void MainObject::CheckToMap()
{
  int x1 = 0;
  int x2 = 0;
  int y1 = 0;
  int y2 = 0;

  Map* data_map = GameMap::GetInstance()->GetMap();
  std::vector<std::vector<BlockMap*>> tile_list = data_map->GetTile();
  //Check Horizontal

  int height_min = 0;
  if (input_type_.up_ == 1)
      height_min = height_frame_;
  else
  {
      height_min = SDLCommonFunc::GetMin(height_frame_, TILE_SIZE);
  }

  /*
        x1,y1******(y1,x2)
           *       *
           *       *
           *       *
        x1,y2******(x2,y2)

  */
  x1 = (x_pos_ + x_val_) / TILE_SIZE;
  x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

  y1 = (y_pos_) / TILE_SIZE;
  y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

  // Check x1, x2 with full width of map
  // Check y1, y2 with full height of map
  bool IsInside  = SDLCommonFunc::CheckInsideMapX(x1, x2);
       IsInside  &= SDLCommonFunc::CheckInsideMapY(y1, y2);
  if (IsInside)
  {
    if (x_val_ > 0) // when object is moving by right  ===>
    {
      
      int val1 = tile_list[y1][x2]->getType();
      int val2 = tile_list[y2][x2]->getType();

      bool IsMoney  = GameMap::GetInstance()->ChecTileMoney(val1);
           IsMoney |= GameMap::GetInstance()->ChecTileMoney(val2);
      if (IsMoney)
      {
          tile_list[y1][x2]->setType(0);
          tile_list[y2][x2]->setType(0);
          IncreaseMoney();
      }
      else
      {
          bool IsBlank1 = GameMap::GetInstance()->CheckBlank(val1);
          bool IsBlank2 = GameMap::GetInstance()->CheckBlank(val2);
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
    else if (x_val_ < 0) // When moving by left    <====
    {
      int val1 = tile_list[y1][x1]->getType();
      int val2 = tile_list[y2][x1]->getType();

      bool IsMoney = GameMap::GetInstance()->ChecTileMoney(val1);
           IsMoney |= GameMap::GetInstance()->ChecTileMoney(val2);
      if (IsMoney)
      {
          tile_list[y1][x1]->setType(0);
          tile_list[y2][x1]->setType(0);
          IncreaseMoney();
      }
      else
      {
          bool IsBlank1 = GameMap::GetInstance()->CheckBlank(val1);
          bool IsBlank2 = GameMap::GetInstance()->CheckBlank(val2);
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
      int val1 = tile_list[y2][x1]->getType();
      int val2 = tile_list[y2][x2]->getType();

      bool IsMoney = GameMap::GetInstance()->ChecTileMoney(val1);
           IsMoney |= GameMap::GetInstance()->ChecTileMoney(val2);
      if (IsMoney)
      {
          tile_list[y2][x1]->setType(0);
          tile_list[y2][x2]->setType(0);
          IncreaseMoney();
      }
      else
      {
          bool IsBlank1 = GameMap::GetInstance()->CheckBlank(val1);
          bool IsBlank2 = GameMap::GetInstance()->CheckBlank(val2);

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
      int val1 = tile_list[y1][x1]->getType();
      int val2 = tile_list[y1][x2]->getType();

      bool IsMoney = GameMap::GetInstance()->ChecTileMoney(val1);
           IsMoney |= GameMap::GetInstance()->ChecTileMoney(val2);
      if (IsMoney)
      {
          tile_list[y1][x2]->setType(0);
          tile_list[y1][x2]->setType(0);
          IncreaseMoney();
      }
      else
      {
          bool IsBlank1 = GameMap::GetInstance()->CheckBlank(val1);
          bool IsBlank2 = GameMap::GetInstance()->CheckBlank(val2);

          if (!IsBlank1 || !IsBlank2)
          {
              y_pos_ = (y1 + 1) * TILE_SIZE;
              y_val_ = 0;

              if (!IsBlank1)
              {
                  tile_list[y1][x1]->setYVal(16);
              }
              else
              {
                  if (!IsBlank2)
                  {
                      tile_list[y1][x2]->setYVal(16);
                  }
              }
              
          }
      }
    }
  }

  GameMap::GetInstance()->SetMap(data_map);
  x_pos_ += x_val_;
  y_pos_ += y_val_;

  if (x_pos_ < 0)
  {
    x_pos_ = 0;
  }
  else if (x_pos_ + width_frame_ >= data_map->getMaxX())
  {
    x_pos_ = data_map->getMaxX() - width_frame_ - 1;
  }

  if (y_pos_ > data_map->getMaxY())
  {
    think_time_ = 60;
    is_falling_ = true;
  }
}

void MainObject::IncreaseMoney()
{
    money_count_++;
    Mix_Chunk* beep_sound = Mix_LoadWAV(kSoundBeep);
    if (beep_sound != NULL)
        Mix_PlayChannel(-1, beep_sound, 0 );
}


void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
    if (on_ground_ == true)  // jump = 0;
    {
        if (status_ == WALK_LEFT )
        {
            if (input_type_.down_ == 0)
            {
                LoadImg(g_name_main_left, des);
            }
            else if (input_type_.down_ == 1)
            {
                LoadImg("img//player_down_left.png", des);
            }
        }
        else
        {
            if (input_type_.down_ == 0)
            {
                LoadImg(g_name_main_right, des);
            }
            else if (input_type_.down_ == 1)
            {
                LoadImg("img//player_down_right.png", des);
            }
        }
    }
    else // Jump always is  1
    {
        if (status_ == WALK_LEFT)
        {
            LoadImg(g_main_jump_left, des);
        }
        else
        {
            LoadImg(g_main_jump_right, des);
        }
    }
}