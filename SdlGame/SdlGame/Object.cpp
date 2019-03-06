
#include "Object.h"

ObjectGame::ObjectGame(){
  bounding_.x = 10;
	bounding_.y = 200;
	bounding_.w = kObjectWidth;
	bounding_.h = kObjectHeight;
	x_vel_ = 0;
	y_vel_ = 0;
}

ObjectGame::~ObjectGame(){

};

void ObjectGame::HandleAction(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		// Change position for object
		switch(event.key.keysym.sym) {
		case SDLK_UP: y_vel_ -= kObjectHeight/2; break;
		case SDLK_DOWN: y_vel_ += kObjectHeight/2; break;
		case SDLK_LEFT: x_vel_ -= kObjectWidth/2; break;
		case SDLK_RIGHT: x_vel_ += kObjectWidth/2; break;
		}
	}

	else if( event.type == SDL_KEYUP )
	{
		//Adjust the velocity
		switch(event.key.keysym.sym )
		{
		case SDLK_UP: y_vel_ += kObjectHeight/2; break;
		case SDLK_DOWN: y_vel_ -= kObjectHeight/2; break;
		case SDLK_LEFT: x_vel_ += kObjectWidth/2; break;
		case SDLK_RIGHT: x_vel_ -= kObjectWidth/2; break;
		}
	}
}


void ObjectGame::HandleMove(const int x_border, const int y_border)
{
	bounding_.x += x_vel_;
	bounding_.y += y_vel_;
	if (this->bounding_.x < 0 || this->bounding_.x + kObjectWidth > x_border)
		this->bounding_.x -= x_vel_; // keep position x

	if (this->bounding_.y < 0 || this->bounding_.y + kObjectHeight > 430) {
		this->bounding_.y -= y_vel_; // keep position y
	}
}

bool ObjectGame::CheckCollision(SDL_Rect other_object) {
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

	return true;
}


void ObjectGame::ShowObject(SDL_Surface* src, SDL_Surface* des) {
  SDL_BlitSurface(src, NULL, des, &bounding_);
}

void ObjectGame::HasGameObject()
{
	int a = 5;
	int a1 = 7;
	int b = 9;
	int d = 10;
}

//Define timer class
Timer::Timer() {
	start_tick_ = 0;
	pause_tick_ = 0;
	is_started_ = true;
	is_paused_ = false;
}

Timer::~Timer() {
	
}

void Timer::Start() {
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks()/1000;
}

void Timer::Stop() {
	is_paused_ = false;
	is_started_ = false;
}

void Timer::Pause() {
	if (is_started_ && !is_paused_) {
		is_paused_ = true;
		pause_tick_ = (SDL_GetTicks()/1000) - start_tick_;
	}
}

void Timer::UnPause() {
	if (is_paused_) {
		is_paused_ = false;
		start_tick_ = (SDL_GetTicks()/1000) - pause_tick_;
		//pause_tick_ = 0;
	}
}

int Timer::GetTick() {
	if (start_tick_) {
		if (is_paused_)
		{
			return pause_tick_;
		} else {
			return (SDL_GetTicks()/1000) - start_tick_;
		}
	} 
	return 0;
}