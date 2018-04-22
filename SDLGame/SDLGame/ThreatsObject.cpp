
#include "ThreatsObject.h"

ThreatsObject::ThreatsObject() 
{
  rect_.x = SCREEN_WIDTH;
  rect_.y = 0;
  rect_.w = WIDHT_THREAT;
  rect_.h = HEIGHT_THREAT;
  x_val_ = 0;
  y_val_ = 0;
  is_alive_ = false;
  is_stop_bullet_ = false;
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

void ThreatsObject::HandleMove(const int x_boder, const int y_border)
{
  rect_.x -= x_val_;

  if (rect_.x < 200)
  {
    is_stop_bullet_ = true;
  }

  if (rect_.x < 0) 
  {
    Reset(x_boder, y_border);
  }
}

void ThreatsObject::Reset(const int x_boder, const int y_border)
{
  is_stop_bullet_ = false;
  rect_.x = x_boder;
  //int ran_y = SDLCommonFunc::MakeRandomPostY();
  rect_.y = POS_Y_TART_THREAT_OBJECT;
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
  p_bullet->SetRect(this->rect_.x , this->rect_.y + this->rect_.h*0.5);
  p_bullet->set_x_pos(SPEED_BULLET_THREATS_OBJECT);
}

void ThreatsObject::InitBullet(BulletObject* p_bullet)
{
  if (p_bullet)
  {
    bool ret = p_bullet->LoadImg(g_name_bullet_threats);
    if (ret)
    {
      p_bullet->set_is_move(true);
      p_bullet->SetWidthHeight(WIDTH_BULLET_SPHERE, HEIGHT_BULLET_SPHERE);
      p_bullet->set_type(BulletObject::SPHERE);
      p_bullet->SetRect(this->rect_.x, this->rect_.y + this->rect_.h*0.5);
      p_bullet->set_x_pos(SPEED_BULLET_THREATS_OBJECT);
      bullet_list_.push_back(p_bullet);
    }
  }
}


void ThreatsObject::MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit)
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
            if (this->rect_.x < x_limit)
            {
              p_bullet->HandleMoveRightToLeft();
              p_bullet->Show(des);
            }
          }
          else
          {
            p_bullet->set_is_move(true);
            p_bullet->SetRect(this->rect_.x - SPEED_BULLET_THREATS_OBJECT, this->rect_.y + this->rect_.h*0.5);
          }
        }
      }
    }
  }
}

void ThreatsObject::HandleInputAction(SDL_Event events, SDL_Rect rect_obj) 
{

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