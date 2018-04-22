
#include "MainObject.h"
#include "ImpTimer.h"

const int FOO_WIDTH = 61;
const int FOO_HEIGHT = 49;

//The direction status of the stick figure
const int WALK_RIGHT = 0;
const int WALK_LEFT = 1;
const int gravity = 2.0;
static int g_time = 1;

MainObject::MainObject() 
{
  rect_.x = 0;
  rect_.y = 0;
  rect_.w = FOO_WIDTH;
  rect_.h = FOO_HEIGHT;
  x_val_ = 0;
  y_val_ = 0;

  velocity_ = 0;
  velocity2_ = 0;

  //Initialize animation variables
  frame_ = 0;
  status_ = WALK_RIGHT;
  is_move_ = true;
  is_jump_ = false;
  bullet_dir_ = DIR_RIGHT;
}


MainObject::~MainObject()
{

}

void MainObject::set_clips()
{
  //Clip the sprites
  right_clip_[ 0 ].x = 0;
  right_clip_[ 0 ].y = 0;
  right_clip_[ 0 ].w = FOO_WIDTH;
  right_clip_[ 0 ].h = FOO_HEIGHT;

  right_clip_[ 1 ].x = FOO_WIDTH;
  right_clip_[ 1 ].y = 0;
  right_clip_[ 1 ].w = FOO_WIDTH;
  right_clip_[ 1 ].h = FOO_HEIGHT;

  right_clip_[ 2 ].x = FOO_WIDTH * 2;
  right_clip_[ 2 ].y = 0;
  right_clip_[ 2 ].w = FOO_WIDTH;
  right_clip_[ 2 ].h = FOO_HEIGHT;

  right_clip_[ 3 ].x = FOO_WIDTH * 3;
  right_clip_[ 3 ].y = 0;
  right_clip_[ 3 ].w = FOO_WIDTH;
  right_clip_[ 3 ].h = FOO_HEIGHT;

  left_clip[ 0 ].x = 0;
  left_clip[ 0 ].y = FOO_HEIGHT;
  left_clip[ 0 ].w = FOO_WIDTH;
  left_clip[ 0 ].h = FOO_HEIGHT;

  left_clip[ 1 ].x = FOO_WIDTH;
  left_clip[ 1 ].y = FOO_HEIGHT;
  left_clip[ 1 ].w = FOO_WIDTH;
  left_clip[ 1 ].h = FOO_HEIGHT;

  left_clip[ 2 ].x = FOO_WIDTH * 2;
  left_clip[ 2 ].y = FOO_HEIGHT;
  left_clip[ 2 ].w = FOO_WIDTH;
  left_clip[ 2 ].h = FOO_HEIGHT;

  left_clip[ 3 ].x = FOO_WIDTH * 3;
  left_clip[ 3 ].y = FOO_HEIGHT;
  left_clip[ 3 ].w = FOO_WIDTH;
  left_clip[ 3 ].h = FOO_HEIGHT;
}

void MainObject::HandleMove()
{
  //Move
  if (is_move_ == true)
  {
    rect_.x += velocity_;
    if((rect_.x < 0) || (rect_.x + FOO_WIDTH > SCREEN_WIDTH))
    {
      rect_.x -= velocity_;
    }
  }
}

void MainObject::ImplementJump()
{

  if (is_jump_)
  {
     rect_.y += velocity2_;
     if (rect_.y < POS_Y_TART_MAIN_OBJECT - 200)
     {
       is_jump_ = false;
     }
  }

  if (is_jump_ == false)
  {
    if (rect_.y < POS_Y_TART_MAIN_OBJECT)
    {
      g_time++;
      double time_second = (g_time*g_time)*1.0/(100*100);
      double val =  0.5*10*time_second;  //m
      val = val*100;  //1 cm = 1 pixel
      if (rect_.y + val > POS_Y_TART_MAIN_OBJECT)
      {
         rect_.y = POS_Y_TART_MAIN_OBJECT;
         g_time = 1;
      }
      else
      {
        rect_.y += val;
      }
    }
  }
}

void MainObject::HandleBullet(SDL_Surface* des)
{
  for (int i = 0; i < p_bullet_list.size(); i++)
  {
    BulletObject* p_bullet = p_bullet_list.at(i);
    if (p_bullet != NULL)
    {
      if (p_bullet->get_is_move()) 
      {
        //if (bullet_dir_ == DIR_RIGHT)
          p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
        //else
        //  p_bullet->HandleMoveRightToLeft();
        p_bullet->Show(des);
      }
      else
      {
        if (p_bullet != NULL)
        {
          p_bullet_list.erase(p_bullet_list.begin() + i);
          delete p_bullet;
          p_bullet = NULL;
        }
      }
    }
  }
}

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[3]) 
{

  //If a key was pressed
  if( events.type == SDL_KEYDOWN )
  {
    //Set the velocity
    switch( events.key.keysym.sym )
    {
    case SDLK_RIGHT: 
      {
        velocity_ += SPEED_MAIN_OBJECT;
        break;
      }
    case SDLK_LEFT: 
      {
        is_move_ = true;
        velocity_ -= SPEED_MAIN_OBJECT;
        break;
      }
    case SDLK_UP:
      {
        
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
    case SDLK_RIGHT: velocity_ -= SPEED_MAIN_OBJECT; break;
    case SDLK_LEFT: velocity_ += SPEED_MAIN_OBJECT; break;
      break;
    }
  }
  else if (events.type == SDL_MOUSEBUTTONDOWN) 
  {
    if (events.button.button == SDL_BUTTON_LEFT) 
    {
      BulletObject* p_bullet = new BulletObject();


      p_bullet->SetWidthHeight(WIDTH_BULLET_LASER, HEIGHT_BULLET_LASER);
      p_bullet->LoadImg(g_name_bullet_main_1);
      p_bullet->set_type(BulletObject::LASER);
      int ret = Mix_PlayChannel(-1, bullet_sound[0], 0 );

    /*else if (events.button.button == SDL_BUTTON_LEFT)
    {
      p_bullet->SetWidthHeight(WIDTH_BULLET_SPHERE, HEIGHT_BULLET_SPHERE);
      p_bullet->LoadImg(g_name_bullet_main_2);
      p_bullet->set_type(BulletObject::SPHERE);
      int ret = Mix_PlayChannel(-1, bullet_sound[1], 0 );
    }*/

      if (status_ == WALK_LEFT)
      {
        p_bullet->set_dir_bullet(DIR_LEFT);
        p_bullet->SetRect(this->rect_.x, this->rect_.y + this->rect_.h*0.35);
      }
      else if (status_ == WALK_RIGHT)
      {
        p_bullet->set_dir_bullet(DIR_RIGHT);
         p_bullet->SetRect(this->rect_.x + this->rect_.w - SPEED_BULLET_MAIN_OBJECT, this->rect_.y + this->rect_.h*0.35);
      }

      p_bullet->set_x_pos(SPEED_BULLET_MAIN_OBJECT);
     
      p_bullet->set_is_move(true);
      p_bullet_list.push_back(p_bullet);
    }
    else if (events.button.button == SDL_BUTTON_RIGHT)
    {
      if (rect_.y >= POS_Y_TART_MAIN_OBJECT)
      {
        is_jump_ = true;
      }
      velocity2_ = -10.0;
    }
  }
  else if (events.type == SDL_MOUSEBUTTONUP)
  {
    if (events.button.button == SDL_BUTTON_LEFT) 
    {
      ;//
    }
    else
    {
      ;//
    }
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

void MainObject::Show(SDL_Surface* des)
{
  //If Foo is moving left
  if(velocity_ < 0)
  {
    status_ = WALK_LEFT;
    frame_++;
  }


  else if(velocity_ > 0)
  {
    status_ = WALK_RIGHT;
    frame_++;
  }

  else
  {
    frame_ = 0;
  }

  if( frame_ >= 4 )
  {
    frame_ = 0;
  }

  if( status_ == WALK_RIGHT )
  {
    SDLCommonFunc::ApplySurfaceClip(rect_.x, rect_.y, this->p_object_, des, &right_clip_[frame_]);
  }
  else if( status_ == WALK_LEFT )
  {
     SDLCommonFunc::ApplySurfaceClip(rect_.x, rect_.y, this->p_object_, des, &left_clip[frame_]);
  }
}
