
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
		case SDLK_UP: y_vel_ -= kObjectHeight/10; break;
		case SDLK_DOWN: y_vel_ += kObjectHeight/10; break;
		case SDLK_LEFT: x_vel_ -= kObjectWidth/10; break;
		case SDLK_RIGHT: x_vel_ += kObjectWidth/10; break;
		}
	}

	else if( event.type == SDL_KEYUP )
	{
		//Adjust the velocity
		switch(event.key.keysym.sym )
		{
		case SDLK_UP: y_vel_ += kObjectHeight / 10; break;
		case SDLK_DOWN: y_vel_ -= kObjectHeight / 10; break;
		case SDLK_LEFT: x_vel_ += kObjectWidth / 10; break;
		case SDLK_RIGHT: x_vel_ -= kObjectWidth / 10; break;
		}
	}
}


void ObjectGame::HandleMove(const int x_border, const int y_border, SDL_Rect other_object)
{
	bounding_.x += x_vel_;
	bounding_.y += y_vel_;
	if (this->bounding_.x < 0 || this->bounding_.x + kObjectWidth > x_border || CheckCollision(other_object))
		this->bounding_.x -= x_vel_; // keep position x

	if (this->bounding_.y < 0 || this->bounding_.y + kObjectHeight > 400 || CheckCollision(other_object)) {
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
}


void ObjectGame::ShowObject(SDL_Surface* src, SDL_Surface* des) {
  SDL_BlitSurface(src, NULL, des, &bounding_);
}