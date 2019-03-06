
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
    rect_.x += x_val_;
    if (rect_.x > x_border) 
    {
      is_move_ = false;
    }
  }
  else if (bullet_dir_ == DIR_LEFT)
  {
      rect_.x -= x_val_;
      if (rect_.x < 0) 
      {
          is_move_ = false;
      }
  }
  else if (bullet_dir_ == DIR_UP)
  {
      rect_.y -= y_val_;
      if (rect_.y < 0) 
      {
          is_move_ = false;
      }
  }
  else if (bullet_dir_ == DIR_UP_RIGHT)
  {
      rect_.x += x_val_;
      if (rect_.x > x_border) 
      {
          is_move_ = false;
      }

      rect_.y -= y_val_;
      if (rect_.y < 0) 
      {
          is_move_ = false;
      }
  }
  else if (bullet_dir_ == DIR_UP_LEFT)
  {
      rect_.x -= x_val_;
      if (rect_.x < 0) 
      {
          is_move_ = false;
      }

      rect_.y -= y_val_;
      if (rect_.y < 0) 
      {
          is_move_ = false;
      }
  }
  else if (bullet_dir_ == DIR_DOWN_LEFT)
  {
      rect_.x -= x_val_;

      if (rect_.x < 0)
      {
          is_move_ = false;
      }

      rect_.y += y_val_;
      if (rect_.y > y_border)
      {
          is_move_ = false;
      }
  }
  else if (bullet_dir_ == DIR_DOWN_RIGHT)
  {
      rect_.x += x_val_;
      if (rect_.x > x_border)
      {
          is_move_ = false;

      }

      rect_.y += y_val_;
      if (rect_.y > y_border)
      {
          is_move_ = false;
      }
  }
}
