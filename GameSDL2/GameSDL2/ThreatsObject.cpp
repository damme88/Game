
#include "ThreatsObject.h"
#include "Geometric.h"


ThreatsObject::ThreatsObject() 
{
  rect_.x = SCREEN_WIDTH;
  rect_.y = 0;
  width_frame_ = 0;
  height_frame_ = 0;
  x_val_ = 0;
  y_val_ = 0;
  is_alive_ = false;
  is_stop_bullet_ = false;

  x_pos_ = 0;
  y_pos_ = 0;
  on_ground_ = 0;
  think_time_ = 0;

  frame_ = 0;
  type_move_ = STATIC_TH;
  input_type_.left_ = 1;
}

ThreatsObject::~ThreatsObject()
{
  if (bullet_list_.size() > 0)
  {
    for (int i = 0; i <bullet_list_.size(); i++)
    {
      BulletObject* p_bullet = bullet_list_.at(i);
      if (p_bullet != NULL)
      {
        delete p_bullet;
        p_bullet = NULL;
      }
    }
    bullet_list_.clear();
  }
}

SDL_Rect ThreatsObject::GetRectFrame()
{
  SDL_Rect rect;
  rect.x = rect_.x;
  rect.y = rect_.y;
  rect.w = rect_.w/NUM_FRAME;
  rect.h = rect_.h;

  return rect;
}



void ThreatsObject::Reset()
{
  is_stop_bullet_ = false;
  if (type_move_ == MOVING_CONTINOUS)
  {
       x_pos_ = map_x_ + SCREEN_WIDTH + 500;
       y_pos_ = 50;
  }
  else
  {
      x_pos_ = SCREEN_WIDTH - 100;
      y_pos_ = SCREEN_HEIGHT*0.5;
  }

  for (int i = 0; i < bullet_list_.size(); i++)
  {
    BulletObject* p_bullet = bullet_list_.at(i);
    if (p_bullet != NULL)
    {
      ResetBullet(p_bullet);
    }
  }
}

void ThreatsObject::ResetBullet(BulletObject* p_bullet)
{
    if (p_bullet)
    {
        if (type_move_ == MOVING_CONTINOUS)
        {
            p_bullet->SetRect(x_pos_+ 5, y_pos_ + height_frame_ - 10);
        }
        else
        {
            p_bullet->SetRect(x_pos_ + 20, y_pos_+ 10);
        }
    }
}

void ThreatsObject::InitBullet(BulletObject* p_bullet,  SDL_Renderer* screen)
{
  if (p_bullet)
  {
      p_bullet->set_is_move(true);
      
      if (type_move_ == MOVING_CONTINOUS)
      {
          p_bullet->LoadImg(g_plane_bullet, screen);
          p_bullet->set_x_val(5);
          p_bullet->set_y_val(5);
          p_bullet->set_dir_bullet(BulletObject::DIR_DOWN_LEFT);
          p_bullet->SetRect(x_pos_+ 5, y_pos_ + height_frame_ - 10);
      }
      else
      {
          p_bullet->LoadImg(g_threat_bullet, screen);
          p_bullet->set_x_val(15);
          p_bullet->set_dir_bullet(BulletObject::DIR_LEFT);
          p_bullet->SetRect(x_pos_ + 20, y_pos_+ 10);
      }

      bullet_list_.push_back(p_bullet);
  }
}


void ThreatsObject::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
  if (is_alive_)
  {
    for (int i = 0; i < bullet_list_.size(); i++)
    {
      BulletObject* p_bullet = bullet_list_.at(i);
      if (p_bullet != NULL)
      {
        if (is_stop_bullet_ == false)
        {
          if (p_bullet->get_is_move())
          {
              if (type_move_ == STATIC_TH)
              {
                  int distance_bullet = rect_.x + width_frame_ - p_bullet->GetRect().x;
                  if (distance_bullet > 0 && distance_bullet < 400)
                  {
                      p_bullet->HandelMove(x_limit, y_limit);
                      p_bullet->Render(des);
                  }
                  else
                  {
                      p_bullet->set_is_move(false);
                  }
              }
              else if (type_move_ == MOVING_CONTINOUS)
              {
                  p_bullet->HandelMove(x_limit, y_limit);
                  p_bullet->Render(des);
              }
          }
          else
          {
            p_bullet->set_is_move(true);

            if (type_move_ == MOVING_CONTINOUS)
            {
               p_bullet->SetRect(rect_.x + 5, rect_.y + height_frame_ - 10);
                
            }
            else
            {
               p_bullet->SetRect(this->rect_.x + 10, this->rect_.y + 10);
            }
          }
        }
      }
    }
  }
}


void ThreatsObject::RemoveBullet(const int& idx) 
{
  if (bullet_list_.size() > 0 && idx < bullet_list_.size())
  {
    BulletObject* p_bullet = bullet_list_.at(idx);
    bullet_list_.erase(bullet_list_.begin() + idx);

    if (p_bullet)
    {
      delete p_bullet;
      p_bullet = NULL;
    }
  }
}

void ThreatsObject::InitPlayer()
{
  //x_pos_ = SCREEN_WIDTH - 400;
  //y_pos_ = SCREEN_HEIGHT*0.5;
  x_val_ = 0;
  y_val_ = 0;

  if (x_pos_ > 256)
  {
      x_pos_ -= 256;
      animation_a_ -= 256;
      animation_b_ -= 256;
  }
  else
      x_pos_ = 0;
  y_pos_ = 0;
  think_time_ = 0;
  input_type_.left_ = 1;

}

bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
  bool ret = BaseObject::LoadImg(path, screen);

  if (ret == true)
  {
    width_frame_ = rect_.w/NUM_FRAME;
    height_frame_ = rect_.h;
  }

  set_clips();
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


void ThreatsObject::SetAnimationPos(const int& pos_x_a, const int& pos_x_b)
{
  animation_b_ = pos_x_b;
  animation_a_ = pos_x_a;
}


void ThreatsObject::ImpMoveType(SDL_Renderer* screen)
{
  if (type_move_ == STATIC_TH)
  {
    ;//
  }
  else if (type_move_ == MOVING_CONTINOUS)
  {
      x_pos_ -= x_val_;
      if (x_pos_ < map_x_)
      {
          x_pos_ = map_x_ + SCREEN_WIDTH + 500;
      }
  }
  else
  {
    if (on_ground_ == true)
    {
      if (x_pos_ > animation_b_)
      {
        input_type_.left_ = 1;
        input_type_.right_ = 0;
        LoadImg(g_name_threat_left, screen);
      }
      else if (x_pos_ < animation_a_)
      {
        input_type_.right_ = 1;
        input_type_.left_ = 0;
        LoadImg(g_name_threat_right, screen);
      } 
    }
    else
    {
        if (input_type_.left_ == 1)
            LoadImg(g_name_threat_left, screen);
    }
  }
}

void ThreatsObject::DoPlayer(Map& g_map)
{
  if (think_time_ == 0 && type_move_ != MOVING_CONTINOUS)
  {
    x_val_ = 0;
    y_val_ += GRAVITY_SPEED;

    if (y_val_ >= MAX_FALL_SPEED)
    {
      y_val_ = MAX_FALL_SPEED;
    }

    if (input_type_.left_ == 1)
    {
      x_val_ -= PLAYER_SPEED;
    }

    else if (input_type_.right_ == 1)
    {
      x_val_+= PLAYER_SPEED;
    }

    if (input_type_.jump_ == 1)
    {
      if (on_ground_ == 1)
      {
        y_val_ = -PLAYER_HIGHT_VAL;
      }

      input_type_.jump_ = 0;
    }

    CheckToMap(g_map);

    //CenterEntityOnMap(g_map);
  }

  if (think_time_ > 0)
  {
    think_time_--;

    if (think_time_ == 0)
    {
      InitPlayer();
    }
  }
}

void ThreatsObject::DrawBound(SDL_Renderer* des)
{
    GeometricFormat outlie_size(rect_.x, rect_.y, width_frame_, height_frame_);
    ColorData color_data1(255, 0, 255);
    Gemometric::RenderOutline(outlie_size, color_data1, des);
}

void ThreatsObject::CenterEntityOnMap(Map& g_map)
{
  g_map.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);

  if (g_map.start_x_ < 0)
  {
    g_map.start_x_ = 0;
  }

  else if (g_map.start_x_ + SCREEN_WIDTH >= g_map.max_x_)
  {
    g_map.start_x_= g_map.max_x_ - SCREEN_WIDTH;
  }

  g_map.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);

  if (g_map.start_y_ < 0)
  {
    g_map.start_y_ = 0;
  }

  else if (g_map.start_y_+ SCREEN_HEIGHT >= g_map.max_y_)
  {
    g_map.start_y_ = g_map.max_y_ - SCREEN_HEIGHT;
  }
}

void ThreatsObject::CheckToMap(Map& g_map)
{
  int x1 = 0;
  int x2 = 0;
  int y1 = 0;
  int y2 = 0;

  on_ground_ = 0;

  //Check Horizontal
  int height_min =   SDLCommonFunc::GetMin(height_frame_, TILE_SIZE);

  /*
           x1,y1***x2
           *       *
           *       *
           *       *
           *y2******

  */
  x1 = (x_pos_ + x_val_) / TILE_SIZE;
  x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

  y1 = (y_pos_) / TILE_SIZE;
  y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

  // Check x1, x2 with full width of map
  // Check y1, y2 with full heigth of map
  if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
  {
    if (x_val_ > 0) // when object is moving by right  ===>
    {
      // Check current position of map. It is not blank_tile.
      if ((g_map.tile[y1][x2] != BLANK_TILE && g_map.tile[y1][x2] != STATE_MONEY) || (g_map.tile[y2][x2] != BLANK_TILE && g_map.tile[y2][x2] != STATE_MONEY))
      {
        // Fixed post of object at current post of map.
        // => Cannot moving when press button
        x_pos_ = x2 * TILE_SIZE;
        x_pos_ -= width_frame_ + 1;
        x_val_ = 0; // cannot moving
      }
    }
    else if (x_val_ < 0) // When moving by left    <====
    {
      if ((g_map.tile[y1][x1] != BLANK_TILE && g_map.tile[y1][x1] != STATE_MONEY) || (g_map.tile[y2][x1] != BLANK_TILE && g_map.tile[y2][x1] != STATE_MONEY))
      {
        x_pos_ = (x1 + 1) * TILE_SIZE;
        x_val_ = 0;
      }
    }
  }


  // Check vertical
  int width_min = SDLCommonFunc::GetMin(width_frame_, TILE_SIZE);

  x1 = (x_pos_) / TILE_SIZE;
  x2 = (x_pos_ + width_min) / TILE_SIZE;

  y1 = (y_pos_ + y_val_) / TILE_SIZE;
  y2 = (y_pos_ + y_val_ + height_frame_) / TILE_SIZE;

  if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
  {
    if (y_val_ > 0)
    {
      //Similar for vertical
      if ((g_map.tile[y2][x1] != BLANK_TILE && g_map.tile[y2][x1] != STATE_MONEY) || (g_map.tile[y2][x2] != BLANK_TILE && g_map.tile[y2][x2] != STATE_MONEY))
      {
        y_pos_ = y2 * TILE_SIZE;
        y_pos_ -= height_frame_;

        y_val_ = 0;

        on_ground_ = 1;
      }
    }
    else if (y_val_ < 0)
    {
      if ((g_map.tile[y1][x1] != BLANK_TILE && g_map.tile[y1][x1] != STATE_MONEY ) || (g_map.tile[y1][x2] != BLANK_TILE && g_map.tile[y1][x2] != STATE_MONEY))
      {
        y_pos_ = (y1 + 1) * TILE_SIZE;

        y_val_ = 0;
      }
    }
  }

  //If there is not collision with map tile. 
  x_pos_ += x_val_;
  y_pos_ += y_val_;

  if (x_pos_ < 0)
  {
    x_pos_ = 0;
  }
  else if (x_pos_ + width_frame_ >= g_map.max_x_)
  {
    x_pos_ = g_map.max_x_ - width_frame_ - 1;
  }

  if (y_pos_ > g_map.max_y_)
  {
    think_time_ = 60;
  }
}

void ThreatsObject::Show(SDL_Renderer* des)
{

  DrawBound(des);
  if (think_time_ == 0)
  {
      rect_.x = x_pos_ - map_x_;
      rect_.y = y_pos_- map_y_;
      frame_++;
      if( frame_ >= 8 )
      {
        frame_ = 0;
      }

      SDL_Rect* currentClip = &frame_clip_[frame_];
      BaseObject::Render(des, currentClip);
  }
}