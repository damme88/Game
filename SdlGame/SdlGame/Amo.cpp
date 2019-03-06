
#include "Amo.h"

Amo::Amo() {
  bounding_.w = kAmoWidth;
	bounding_.h = kAmoHeight;
	bounding_.x = 0;
	bounding_.y = 0;
	is_move_ = false;
	amo_type_ = NONE;
}

Amo::Amo(int x, int y) {
  bounding_.x = x;
	bounding_.y = y;
	is_move_ = false;
}

Amo::~Amo() {

}

void Amo::Move(const int x_boder, const int y_border) {
  bounding_.x += 30;
	if (bounding_.x > x_boder + 10) {
		is_move_ = false;
	}
}

bool Amo::CheckCollision(SDL_Rect* other_obj) {
	return true;
}

void Amo::Show(SDL_Surface* src, SDL_Surface* des) {
	SDL_BlitSurface(src, NULL, des, &bounding_);
}

void Amo::HandleAction(SDL_Event events, SDL_Rect rect_obj, Mix_Chunk* gMusicAmo[3]) {


}
void function1()
{
  int a = 6;
}

void function2()
{
   int a =5;
}