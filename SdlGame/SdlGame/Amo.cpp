
#include "Amo.h"

Amo::Amo() {
  bounding_.w = kAmoWidth;
	bounding_.h = kAmoHeight;
	bounding_.x = 0;
	bounding_.y = 0;
	is_move_ = false;
}

Amo::Amo(int x, int y) {
  bounding_.x = x;
	bounding_.y = y;
	is_move_ = false;
}

Amo::~Amo() {

}

void Amo::Move(const int x_boder, const int y_border, SDL_Rect other_object) {
  bounding_.x += 6;
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

void Amo::HandleAction(SDL_Event events, SDL_Rect rect_obj, Mix_Chunk* gMusicAmo) {
	if (events.type == SDL_MOUSEBUTTONDOWN) {
		if (events.button.button == SDL_BUTTON_LEFT) {
			if( Mix_PlayChannel( -1, gMusicAmo, 0 ) == -1 )
				return ;
			is_move_ = true;
			bounding_.x = rect_obj.x + 40;
			bounding_.y = rect_obj.y + 10;
		}
	}
}