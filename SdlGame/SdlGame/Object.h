
#ifndef OBJECT_H_
#define OBJECT_H_
#include "Common.h"

const int kObjectWidth = 50;
const int kObjectHeight = 20;

class ObjectGame {
public:
	ObjectGame();
	~ObjectGame();
	void HandleAction(SDL_Event event);
	void HandleMove(const int x_boder, const int y_border, SDL_Rect other_object);
	void ShowObject(SDL_Surface* src, SDL_Surface* des);
	bool CheckCollision(SDL_Rect other_object);
  SDL_Rect GetBounding() {return bounding_;}
private:
	SDL_Rect bounding_;
	int x_vel_;
	int y_vel_;
};

#endif