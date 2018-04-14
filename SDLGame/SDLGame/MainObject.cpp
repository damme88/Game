
#include "MainObject.h"

MainObject::MainObject() 
{
  rect_.x = 0;
  rect_.y = 0;
  rect_.w = WIDHT_MAIN_OBJECT;
  rect_.h = HEIGHT_MAIN_OBJECT;
  x_val_ = 0;
  y_val_ = 0;
}


MainObject::~MainObject()
{

}

void MainObject::HandleMove()
{
  rect_.x += x_val_;
  if ((rect_.x < 0) || (rect_.x + WIDHT_MAIN_OBJECT > SCREEN_WIDTH)) 
  {
      rect_.x -= x_val_ ;
  }

  rect_.y += y_val_;
  if ((rect_.y < 0) || (rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 200))
  {
      rect_.y -= y_val_;
  }
}

void MainObject::HandleBullet(SDL_Surface* des)
{
  for (int i = 0; i < p_bullet_list.size(); i++)
  {
    BulletObject* p_amo = p_bullet_list.at(i);
    if (p_amo != NULL)
    {
      if (p_amo->get_is_move()) 
      {
        if (p_amo->GetRect().x > (this->rect_.x + this->rect_.w + 100))
        {
          LoadImg("pl0.png");
        }

        p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
        p_amo->Show(des);
      }
      else
      {
        if (p_amo != NULL)
        {
          p_bullet_list.erase(p_bullet_list.begin() + i);
          delete p_amo;
          p_amo = NULL;
        }
      }
    }
  }
}

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[3]) 
{
  if (events.type == SDL_KEYDOWN) 
  {
    // Change position for object
    switch(events.key.keysym.sym) 
    {
      case SDLK_UP: 
        y_val_ -= SPEED_MAIN_OBJECT; 
        break;
      case SDLK_DOWN: 
        y_val_ += SPEED_MAIN_OBJECT; 
        break;
      case SDLK_LEFT: 
        x_val_ -= SPEED_MAIN_OBJECT; 
        break;
      case SDLK_RIGHT: 
        x_val_ += SPEED_MAIN_OBJECT; 
        break;
    }
  }
  else if( events.type == SDL_KEYUP )
  {
    //Adjust the velocity
    switch(events.key.keysym.sym )
    {
      case SDLK_UP: y_val_ += SPEED_MAIN_OBJECT; break;
      case SDLK_DOWN: y_val_ -= SPEED_MAIN_OBJECT; break;
      case SDLK_LEFT: x_val_ += SPEED_MAIN_OBJECT; break;
      case SDLK_RIGHT: x_val_ -= SPEED_MAIN_OBJECT; break;
    }
  }
  else if (events.type == SDL_MOUSEBUTTONDOWN) 
  {
    LoadImg(g_name_main1);
    BulletObject* p_bullet = new BulletObject();
    if (events.button.button == SDL_BUTTON_LEFT) 
    {
      p_bullet->SetWidthHeight(WIDTH_BULLET_LASER, HEIGHT_BULLET_LASER);
      p_bullet->LoadImg(g_name_bullet_main_1);
      p_bullet->set_type(BulletObject::LASER);
      int ret = Mix_PlayChannel(-1, bullet_sound[0], 0 );
    }
    else if (events.button.button == SDL_BUTTON_RIGHT)
    {
      p_bullet->SetWidthHeight(WIDTH_BULLET_SPHERE, HEIGHT_BULLET_SPHERE);
      p_bullet->LoadImg(g_name_bullet_main_2);
      p_bullet->set_type(BulletObject::SPHERE);
      int ret = Mix_PlayChannel(-1, bullet_sound[1], 0 );
    }

    p_bullet->set_x_pos(SPEED_BULLET_MAIN_OBJECT);
    p_bullet->SetRect(this->rect_.x + this->rect_.w - SPEED_BULLET_MAIN_OBJECT - 20, this->rect_.y + this->rect_.h*0.75);
    p_bullet->set_is_move(true);
    p_bullet_list.push_back(p_bullet);
  }
}


void MainObject::RemoveBullet(const int& idx) 
{
  if (p_bullet_list.size() > 0 && idx < p_bullet_list.size())
  {
    BulletObject* p_bullet = p_bullet_list.at(idx);
    p_bullet_list.erase(p_bullet_list.begin() + idx);

    if (p_bullet)
    {
      delete p_bullet;
      p_bullet = NULL;
    }
  }
}
