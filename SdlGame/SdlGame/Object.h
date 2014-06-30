
#ifndef OBJECT_H_
#define OBJECT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_events.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <Windows.h>
#include <string>

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
	int GetXVel()const {return x_vel_;}
	int GetYVel()const {return y_vel_;}
private:
	SDL_Rect bounding_;
	int x_vel_;
	int y_vel_;
};

#endif