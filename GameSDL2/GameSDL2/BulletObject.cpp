
#include "BulletObject.h"

BulletObject::BulletObject()
{
  x_val_ = 0;
  y_val_ = 0;
  move_type_ = LINE_TYPE;
  map_x_ = 0;
  map_y_ = 0;
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
  if (bullet_dir_ == DIR_RIGHT)
  {
    x_pos_ += x_val_;
    if (x_pos_ - map_x_ > x_border) 
    {
       is_move_ = false;
    }
  }
  else if (bullet_dir_ == DIR_LEFT)
  {
      x_pos_ -= x_val_;
      if (x_pos_ - map_x_ < 0)
      {
          is_move_ = false;
      }
  }
  else if (bullet_dir_ == DIR_UP)
  {
      y_pos_ -= y_val_;
      if (y_pos_ - map_y_ < 0)
      {
          is_move_ = false;
      }
  }
  else if (bullet_dir_ == DIR_UP_RIGHT)
  {
      x_pos_ += x_val_;
      if (x_pos_ - map_x_ > x_border)
      {
          is_move_ = false;
      }

      y_pos_ -= y_val_;
      if (y_pos_ - map_y_ < 0)
      {
          is_move_ = false;
      }
  }
  else if (bullet_dir_ == DIR_UP_LEFT)
  {
      x_pos_ -= x_val_;
      if (x_pos_ - map_x_ < 0) 
      {
          is_move_ = false;
      }

      y_pos_ -= y_val_;
      if (y_pos_ - map_y_ < 0) 
      {
          is_move_ = false;
      }
  }
  else if (bullet_dir_ == DIR_DOWN_LEFT)
  {
      x_pos_ -= x_val_;

      if (x_pos_ - map_x_ < 0)
      {
          is_move_ = false;
      }

      y_pos_ += y_val_;
      if (y_pos_ - map_y_ > y_border)
      {
          is_move_ = false;
      }
  }
  else if (bullet_dir_ == DIR_DOWN_RIGHT)
  {
      x_pos_ += x_val_;
      if (x_pos_ - map_x_ > x_border)
      {
          is_move_ = false;

      }

      y_pos_ += y_val_;
      if (y_pos_ - map_y_ > y_border)
      {
          is_move_ = false;
      }
  }
}

bool BulletObject::CheckToMap()
{
    Map map_data = GameMap::GetInstance()->GetMap();
    int x = x_pos_ / TILE_SIZE;
    int y = y_pos_/ TILE_SIZE;
    if (x >= 0 && x < MAX_MAP_X && y >= 0 && y < MAX_MAP_Y)
    {
        int val1 = map_data.tile[y][x];
        if ((val1 != BLANK_TILE))
        {
            is_move_ = false;
            return true;
        }
    }
    return false;
}
void BulletObject::Show(SDL_Renderer* des)
{
    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;
    BaseObject::Render(des);
}