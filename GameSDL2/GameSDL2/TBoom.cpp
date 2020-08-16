
#include "TBoom.h"

TBoom::TBoom()
{
    type_ = TH_BOOM;
}


TBoom::~TBoom()
{

}

void TBoom::Update()
{

}

void TBoom::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_g:
        {
            break;
        }
        case SDLK_h:
        {
            break;
        }
        }
    }
}

void TBoom::Show(SDL_Renderer* des)
{
    Update();
    ThreatsObject::Show(des);
}
