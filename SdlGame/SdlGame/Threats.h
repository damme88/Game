
#ifndef THREATS_H_
#define THREATS_H_
#include "Common.h"

const int kThreatsWidth = 40;
const int kThreatsHeight = 40;

class Threats {	
	public:
		Threats();
		Threats(int x, int y);
		~Threats();
		void HandleMove(const int x_boder, const int y_border, SDL_Rect other_object);
		void ShowThreats(SDL_Surface* src, SDL_Surface* des);
		bool CheckCollision(SDL_Rect other_object);
	private:
		SDL_Rect bounding_;
};

#endif // THREATES_H_