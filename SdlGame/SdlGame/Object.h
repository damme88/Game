
#ifndef OBJECT_H_
#define OBJECT_H_
#include "Common.h"

const int kObjectWidth = 45;
const int kObjectHeight = 20;

class ObjectGame {
public:
	ObjectGame();
	~ObjectGame();
	void HandleAction(SDL_Event event);
	void HandleMove(const int x_boder, const int y_border);
	void ShowObject(SDL_Surface* src, SDL_Surface* des);
	bool CheckCollision(SDL_Rect other_object);
  SDL_Rect GetBounding() {return bounding_;}
  void FindMax();
private:
	SDL_Rect bounding_;
	int x_vel_;
	int y_vel_;
};

class Timer {
private:
	int start_tick_;
	int pause_tick_;
	bool is_paused_;
	bool is_started_;

public:
	Timer();
	~Timer();
	void Start();
	void Stop();
	void Pause();
	void UnPause();
	int GetTick();
	bool IsStarted()const {return is_started_;}
	bool IsPaused()const {return is_paused_;}
};
#endif