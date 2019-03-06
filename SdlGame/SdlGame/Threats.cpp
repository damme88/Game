
#include "Threats.h"

Threats::Threats() {
	bounding_.x = 650;
	bounding_.y = 240;
	bounding_.w = kThreatsWidth;
	bounding_.h = kThreatsHeight;
	is_collision_ = false;
}


Threats::Threats(int x, int y) {
  bounding_.x = x;
	bounding_.y = y;
}

Threats::~Threats() {
  
}

void Threats::HandleMove(const int x_boder, const int y_border, SDL_Rect amo, SDL_Rect object, bool& colobj) {
  bounding_.x -= 5;
	if (bounding_.x < 0)
	{
		bounding_.x = x_boder + 10;
		bounding_.y = rand()%400;
	}
}

void Threats::SetPosAgain(const int x_boder, const int y_boder) {
	bounding_.x = x_boder + 10;
	bounding_.y = rand()%400;
}

bool Threats::CheckCollision(SDL_Rect other_object) {
	int left_a = 0;
	int left_b = 0;
	int right_a = 0;
	int right_b = 0;
	int top_a = 0;
	int top_b = 0;
	int bottom_a = 0;
	int bottom_b = 0;

	left_a = this->bounding_.x;
	right_a = this->bounding_.x + this->bounding_.w;
	top_a = this->bounding_.y;
	bottom_a = this->bounding_.y + this->bounding_.h;

	left_b = other_object.x;
	right_b = other_object.x + other_object.w; //right is left border to right edge
	top_b = other_object.y;
	bottom_b = other_object.y + other_object.h; // bottom is above border to under edge

	if (bottom_a <= top_b-5) {
		return false;
	}
	if (top_a >= bottom_b-5) {
		return false;
	}
	if (right_a <= left_b-5) {
		return false;
	}
	if (left_a >= right_b-5) {
		return false;
	}

	is_collision_ = true;
  return true;
}

void Threats::ShowThreats(SDL_Surface* src, SDL_Surface* des) {
	SDL_BlitSurface(src, NULL, des, &bounding_);
}