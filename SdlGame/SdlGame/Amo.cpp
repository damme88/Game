
#include "Amo.h"

Amo::Amo() {
  bouding_.w = kAmoWidth;
	bouding_.h = kAmoHeight;
	bouding_.x = 0;
	bouding_.y = 0;
	is_move_ = false;
}

Amo::Amo(int x, int y) {
  bouding_.x = x;
	bouding_.y = y;
	is_move_ = false;
}

Amo::~Amo() {

}

void Amo::Move(const int x_boder, const int y_border, SDL_Rect other_object) {
  bouding_.x += 6;
	if (bouding_.x > x_boder + 10) {
		is_move_ = false;
	}
}

bool Amo::CheckCollision(SDL_Rect* other_obj) {
	return true;
}

void Amo::Show(SDL_Surface* src, SDL_Surface* des) {
	SDL_BlitSurface(src, NULL, des, &bouding_);
}

void Amo::HandleAction(SDL_Event events, SDL_Rect rect_obj, Mix_Chunk* gMusicAmo) {
	if (events.type == SDL_MOUSEBUTTONDOWN) {
		if( Mix_PlayChannel( -1, gMusicAmo, 0 ) == -1 )
			return ;
		is_move_ = true;
		bouding_.x = rect_obj.x + 40;
		bouding_.y = rect_obj.y + 10;
	}
}