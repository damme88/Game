
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
	bounding_.w = kThreatsWidth;
	bounding_.h = kThreatsHeight;
	is_collision_ = false;
}

Threats::~Threats() {
  
}

void Threats::HandleMove(const int x_boder, const int y_border, SDL_Rect other_object) {
  bounding_.x -= 2;
	if (bounding_.x < 0)
	{
		bounding_.x = x_boder + 10;
	}
	if (other_object.w < 640 && other_object.h < 480) {
	  CheckCollision(other_object);
	}
}

void Threats::SetPosAgain(const int x_boder, const int y_boder) {
	bounding_.x = x_boder + 10;
	bounding_.y += rand();

	if (bounding_.y >= y_boder) {
		bounding_.y = y_boder /2;
	}
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

	if (bottom_a <= top_b) {
		return false;
	}
	if (top_a >= bottom_b) {
		return false;
	}
	if (right_a <= left_b) {
		return false;
	}
	if (left_a >= right_b) {
		return false;
	}

	is_collision_ = true;
  return true;
}

void Threats::ShowThreats(SDL_Surface* src, SDL_Surface* des) {
	SDL_BlitSurface(src, NULL, des, &bounding_);
}