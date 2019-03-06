
#ifndef AMO_H_
#define AMO_H_


//hello
#include "Common.h"
  const int kAmoWidth = 40;
  const int kAmoHeight = 8;
class Amo {
public:
	enum AmoType {
		NONE,
	  LASER,
		SPHERE,
		LIGHTNING
	};
	
	Amo();
	Amo(int x, int y);
	~Amo();
	void Move(const int x_boder, const int y_boder);
	bool CheckCollision(SDL_Rect* other_obj);
	void Show(SDL_Surface* src, SDL_Surface* des);
	void HandleAction(SDL_Event events, SDL_Rect rect_obj, Mix_Chunk* gMusicAmo[3]);
	bool IsMove()const {return is_move_;}
	SDL_Rect GetBounding() {return bounding_;}
	unsigned int GetAmoType() const{ return amo_type_;}
private:
	SDL_Rect bounding_;
	bool is_move_;
	unsigned int amo_type_;
};

#endif 