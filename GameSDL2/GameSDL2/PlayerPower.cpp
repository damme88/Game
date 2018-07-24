#include "PlayerPower.h"


PlayerPower::PlayerPower(void)
{
}


PlayerPower::~PlayerPower(void)
{
}


void PlayerPower::AddPos(const int& xPos)
{
  position_list_.push_back(xPos);
}

void PlayerPower::Show(SDL_Renderer* screen)
{
  for (int i = 0; i < position_list_.size(); i++)
  {
    rect_.x = position_list_.at(i);
    rect_.y = 10;
    Render(screen);
  }
}

void PlayerPower::Init(SDL_Renderer* screen)
{
  LoadImg("img//player_pw.png", screen);
  number_ = 3;
  if (position_list_.size() > 0)
  {
    position_list_.clear();
  }

  AddPos(20);
  AddPos(60);
  AddPos(100);
}

void PlayerPower::Decrease()
{
  number_--;
  position_list_.pop_back();
}