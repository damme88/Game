
#include "Threats.h"

Threats::Threats() {
	bounding_.x = 650;
	bounding_.y = 240;
	bounding_.w = kThreatsWidth;
	bounding_.h = kThreatsHeight;
}


Threats::Threats(int x, int y) {
  bounding_.x = x;
	bounding_.y = y;
	bounding_.w = kThreatsWidth;
	bounding_.h = kThreatsHeight;
}

Threats::~Threats() {
  
}

void Threats::HandleMove(const int x_boder, const int y_border, SDL_Rect other_object) {
  bounding_.x -= 2;
	if (bounding_.x < 0)
	{
		bounding_.x = x_boder + 10;
	}
}

bool Threats::CheckCollision(SDL_Rect other_object) {
  return true;
}

void Threats::ShowThreats(SDL_Surface* src, SDL_Surface* des) {
	SDL_BlitSurface(src, NULL, des, &bounding_);
}