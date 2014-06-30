
#ifndef AMO_H_
#define AMO_H_

#include "Common.h"
  const int kAmoWidth = 40;
  const int kAmoHeight = 8;
class Amo {
public:
	Amo();
	Amo(int x, int y);
	~Amo();
	void Move(const int x_boder, const int y_boder, SDL_Rect other_object);
	bool CheckCollision(SDL_Rect* other_obj);
	void Show(SDL_Surface* src, SDL_Surface* des);
	void HandleAction(SDL_Event events, SDL_Rect rect_obj, Mix_Chunk* gMusicAmo);
	bool IsMove()const {return is_move_;}
private:
	SDL_Rect bouding_;
	bool is_move_;
};

#endif AMO_H_