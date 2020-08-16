#ifndef TBOOM_H_
#define TBOOM_H_

#include "CommonFunc.h"
#include "ThreatsObject.h"

class TBoom : public ThreatsObject
{
public:
    TBoom();
    ~TBoom();

    void Update();
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
private:
};

#endif

