
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

void BulletObject::HandelMove(const int& x_border, const int& y_border)
{
  if (bullet_dir_ == DIR_RIGHT)
  {
    rect_.x += x_val_;
    if (rect_.x > x_border) 
    {
      is_move_ = false;
    }
  }
  else
  {
    rect_.x -= x_val_;
    if (rect_.x < 0) 
    {
      is_move_ = false;
    }
  }
}


void BulletObject::HandleMoveRightToLeft(const int& origin_x)
{
  if (move_type_ == LINE_TYPE)
  {
    rect_.x -= x_val_;
  }
  else if (move_type_ == SIN_TYPE)
  {
    rect_.x -= x_val_;
    if (rect_.x < SCREEN_WIDTH*0.5)
    {
      rect_.y -= 100*cos(rect_.x);
    }
  }

  int distance_bullet = origin_x - rect_.x;
  if (distance_bullet > 400) 
  {
    is_move_ = false;
  }
}

void BulletObject::HandleInputAction(SDL_Event events)
{

}
