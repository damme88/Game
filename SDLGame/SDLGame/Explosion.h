#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "BaseObject.h"
#include "common_function.h"

const int EXPLOSION_WIDTH = 165;
const int EXPLOSION_HEIGHT = 165;

class ExplosionObject : public BaseObject
{
private:
  int frame_;

  SDL_Rect clips_[4];
public:
  ExplosionObject();

  void set_clips();
  void set_frame(int fr) {frame_ = fr;}
  void Show(SDL_Surface* des);
};

#endif