

#include "BossObject.h"


BossObject::BossObject()
{
    frame_ = 0;
    x_val_ = 0.0;
    y_val_ = 0.0;
    x_pos_ = 0;
    y_pos_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    think_time_ = 0;
    map_x_ = 0;
    map_y_ = 0;
}

BossObject::~BossObject()
{

}

bool BossObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret == true)
    {
        width_frame_ = rect_.w/FRAME_NUM_32;
        height_frame_ = rect_.h;
    }

    return ret;
}

void BossObject::set_clips()
{
    //Clip the sprites
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        frame_clip_[ 0 ].x = 0;
        frame_clip_[ 0 ].y = 0;
        frame_clip_[ 0 ].w = width_frame_;
        frame_clip_[ 0 ].h = height_frame_;

        frame_clip_[ 1 ].x = width_frame_;
        frame_clip_[ 1 ].y = 0;
        frame_clip_[ 1 ].w = width_frame_;
        frame_clip_[ 1 ].h = height_frame_;

        frame_clip_[ 2 ].x = width_frame_ * 2;
        frame_clip_[ 2 ].y = 0;
        frame_clip_[ 2 ].w = width_frame_;
        frame_clip_[ 2 ].h = height_frame_;

        frame_clip_[ 3 ].x = width_frame_ * 3;
        frame_clip_[ 3 ].y = 0;
        frame_clip_[ 3 ].w = width_frame_;
        frame_clip_[ 3 ].h = height_frame_;

        frame_clip_[ 4 ].x = width_frame_ * 4;
        frame_clip_[ 4 ].y = 0;
        frame_clip_[ 4 ].w = width_frame_;
        frame_clip_[ 4 ].h = height_frame_;

        frame_clip_[ 5 ].x = width_frame_ * 5;
        frame_clip_[ 5 ].y = 0;
        frame_clip_[ 5 ].w = width_frame_;
        frame_clip_[ 5 ].h = height_frame_;

        frame_clip_[ 6 ].x = width_frame_ * 6;
        frame_clip_[ 6 ].y = 0;
        frame_clip_[ 6 ].w = width_frame_;
        frame_clip_[ 6 ].h = height_frame_;

        frame_clip_[ 7 ].x = width_frame_ * 7;
        frame_clip_[ 7 ].y = 0;
        frame_clip_[ 7 ].w = width_frame_;
        frame_clip_[ 7 ].h = height_frame_;

        frame_clip_[ 8 ].x = width_frame_ * 8;
        frame_clip_[ 8 ].y = 0;
        frame_clip_[ 8 ].w = width_frame_;
        frame_clip_[ 8 ].h = height_frame_;

        frame_clip_[ 9 ].x = width_frame_ * 9;
        frame_clip_[ 9 ].y = 0;
        frame_clip_[ 9 ].w = width_frame_;
        frame_clip_[ 9 ].h = height_frame_;


        frame_clip_[ 10 ].x = width_frame_ * 10;
        frame_clip_[ 10 ].y = 0;
        frame_clip_[ 10 ].w = width_frame_;
        frame_clip_[ 10 ].h = height_frame_;

        frame_clip_[ 11 ].x = width_frame_ * 11;
        frame_clip_[ 11 ].y = 0;
        frame_clip_[ 11 ].w = width_frame_;
        frame_clip_[ 11 ].h = height_frame_;

        frame_clip_[ 12 ].x = width_frame_ * 12;
        frame_clip_[ 12 ].y = 0;
        frame_clip_[ 12 ].w = width_frame_;
        frame_clip_[ 12 ].h = height_frame_;

        frame_clip_[ 13 ].x = width_frame_ * 13;
        frame_clip_[ 13 ].y = 0;
        frame_clip_[ 13 ].w = width_frame_;
        frame_clip_[ 13 ].h = height_frame_;

        frame_clip_[ 14 ].x = width_frame_ * 14;
        frame_clip_[ 14 ].y = 0;
        frame_clip_[ 14 ].w = width_frame_;
        frame_clip_[ 14 ].h = height_frame_;


        frame_clip_[ 15 ].x = width_frame_ * 15;
        frame_clip_[ 15 ].y = 0;
        frame_clip_[ 15 ].w = width_frame_;
        frame_clip_[ 15 ].h = height_frame_;

        frame_clip_[ 16 ].x = width_frame_ * 16;
        frame_clip_[ 16 ].y = 0;
        frame_clip_[ 16 ].w = width_frame_;
        frame_clip_[ 16 ].h = height_frame_;

        frame_clip_[ 17 ].x = width_frame_ * 17;
        frame_clip_[ 17 ].y = 0;
        frame_clip_[ 17 ].w = width_frame_;
        frame_clip_[ 17 ].h = height_frame_;

        frame_clip_[ 18 ].x = width_frame_ * 18;
        frame_clip_[ 18 ].y = 0;
        frame_clip_[ 18 ].w = width_frame_;
        frame_clip_[ 18 ].h = height_frame_;

        frame_clip_[ 19 ].x = width_frame_ * 19;
        frame_clip_[ 19 ].y = 0;
        frame_clip_[ 19 ].w = width_frame_;
        frame_clip_[ 19 ].h = height_frame_;

        frame_clip_[ 20 ].x = width_frame_ * 20;
        frame_clip_[ 20 ].y = 0;
        frame_clip_[ 20 ].w = width_frame_;
        frame_clip_[ 20 ].h = height_frame_;

        frame_clip_[ 21 ].x = width_frame_ * 21;
        frame_clip_[ 21 ].y = 0;
        frame_clip_[ 21 ].w = width_frame_;
        frame_clip_[ 21 ].h = height_frame_;

        frame_clip_[ 22 ].x = width_frame_ * 22;
        frame_clip_[ 22 ].y = 0;
        frame_clip_[ 22 ].w = width_frame_;
        frame_clip_[ 22 ].h = height_frame_;

        frame_clip_[ 23 ].x = width_frame_ * 23;
        frame_clip_[ 23 ].y = 0;
        frame_clip_[ 23 ].w = width_frame_;
        frame_clip_[ 23 ].h = height_frame_;

        frame_clip_[ 24 ].x = width_frame_ * 24;
        frame_clip_[ 24 ].y = 0;
        frame_clip_[ 24 ].w = width_frame_;
        frame_clip_[ 24 ].h = height_frame_;

        frame_clip_[ 25 ].x = width_frame_ * 25;
        frame_clip_[ 25 ].y = 0;
        frame_clip_[ 25 ].w = width_frame_;
        frame_clip_[ 25 ].h = height_frame_;

        frame_clip_[ 26 ].x = width_frame_ * 26;
        frame_clip_[ 26 ].y = 0;
        frame_clip_[ 26 ].w = width_frame_;
        frame_clip_[ 26 ].h = height_frame_;

        frame_clip_[ 27 ].x = width_frame_ * 27;
        frame_clip_[ 27 ].y = 0;
        frame_clip_[ 27 ].w = width_frame_;
        frame_clip_[ 27 ].h = height_frame_;

        frame_clip_[ 28 ].x = width_frame_ * 28;
        frame_clip_[ 28 ].y = 0;
        frame_clip_[ 28 ].w = width_frame_;
        frame_clip_[ 28 ].h = height_frame_;

        frame_clip_[ 29 ].x = width_frame_ * 29;
        frame_clip_[ 29 ].y = 0;
        frame_clip_[ 29 ].w = width_frame_;
        frame_clip_[ 29 ].h = height_frame_;

        frame_clip_[ 30 ].x = width_frame_ * 30;
        frame_clip_[ 30 ].y = 0;
        frame_clip_[ 30 ].w = width_frame_;
        frame_clip_[ 30 ].h = height_frame_;

        frame_clip_[ 31 ].x = width_frame_ * 31;
        frame_clip_[ 31 ].y = 0;
        frame_clip_[ 31 ].w = width_frame_;
        frame_clip_[ 31 ].h = height_frame_;
    }
}


void BossObject::Show(SDL_Renderer* des)
{
    if (think_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_- map_y_;
        frame_++;
        if( frame_ >= 32 )
        {
            frame_ = 0;
        }

        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
        if (currentClip != NULL)
        {
            renderQuad.w = currentClip->w;
            renderQuad.h = currentClip->h;
        }

        SDL_RenderCopy(des, p_object_, currentClip, &renderQuad );
    }
}

void BossObject::DoPlayer(Map& g_map)
{
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

void BossObject::InitPlayer()
{
    x_val_ = 0;
    y_val_ = 0;

    if (x_pos_ > 256)
    {
        x_pos_ -= 256;
    }
    else
        x_pos_ = 0;
    y_pos_ = 0;
    think_time_ = 0;
    input_type_.left_ = 1;
}

void BossObject::CenterEntityOnMap(Map& g_map)
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

void BossObject::CheckToMap(Map& g_map)
{
  int x1 = 0;
  int x2 = 0;
  int y1 = 0;
  int y2 = 0;

  on_ground_ = 0;

  //Check Horizontal
  int height_min =   height_frame_ ;//SDLCommonFunc::GetMin(height_frame_, TILE_SIZE);

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
      if ((g_map.tile[y1][x2] != BLANK_TILE) || (g_map.tile[y2][x2] != BLANK_TILE))
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
      if ((g_map.tile[y1][x1] != BLANK_TILE) || (g_map.tile[y2][x1] != BLANK_TILE))
      {
        x_pos_ = (x1 + 1) * TILE_SIZE;
        x_val_ = 0;
      }
    }
  }


  // Check vertical
  int width_min = width_frame_;// SDLCommonFunc::GetMin(width_frame_, TILE_SIZE);

  x1 = (x_pos_) / TILE_SIZE;
  x2 = (x_pos_ + width_min) / TILE_SIZE;

  y1 = (y_pos_ + y_val_) / TILE_SIZE;
  y2 = (y_pos_ + y_val_ + height_frame_) / TILE_SIZE;

  if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
  {
    if (y_val_ > 0)
    {
      //Similar for vertical
      if ((g_map.tile[y2][x1] != BLANK_TILE) || (g_map.tile[y2][x2] != BLANK_TILE))
      {
        y_pos_ = y2 * TILE_SIZE;
        y_pos_ -= height_frame_;

        y_val_ = 0;

        on_ground_ = 1;
      }
    }
    else if (y_val_ < 0)
    {
      if ((g_map.tile[y1][x1] != BLANK_TILE) || (g_map.tile[y1][x2] != BLANK_TILE))
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