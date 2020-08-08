
#ifndef GOOMBAS_H_
#define GOOMBAS_H_

#include "CommonFunc.h"
#include "ThreatsObject.h"

class Goombas : public ThreatsObject
{
public:
    Goombas();
    ~Goombas();
    void Update();
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
private:
    bool is_move_;
};

#endif
