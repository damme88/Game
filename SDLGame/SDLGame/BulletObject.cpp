
#include "BulletObject.h"

BulletObject::BulletObject() 
{
  rect_.x = 0;
  rect_.y = 0;
  x_val_ = 0;
  y_val_ = 0;
  is_move_ = false;
  move_type_ = LINE_TYPE;
  bullet_dir_ = DIR_RIGHT;
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(const int x_boder, const int y_border)
{

  if (bullet_dir_ == DIR_RIGHT)
  {
    rect_.x += x_val_;
    if (rect_.x > x_boder) 
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

void BulletObject::HandleMoveRightToLeft()
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

  if (rect_.x < 0) 
  {
    is_move_ = false;
  }
}

void BulletObject::HandleInputAction(SDL_Event events, SDL_Rect rect_obj) 
{

}