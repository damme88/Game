#ifndef TMUSHROOM_H_
#define TMUSHROOM_H_

#include "ThreatsObject.h"

class TMushroom : public ThreatsObject
{
public:
    TMushroom();
    ~TMushroom();

    void SetIdxTile(int x, int y) { idx_tile_x_ = x; idx_tile_y_ = y; }
    void Update();
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
private:
    INT idx_tile_x_;
    INT idx_tile_y_;
    bool is_fall_;
};


#endif

