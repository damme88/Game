#include "OptionObject.h"



OptionObject::OptionObject()
{
    type_ctrl_moving_ = 0;
}


OptionObject::~OptionObject()
{

}

bool OptionObject::Init(SDL_Renderer* screen)
{
    bool ret2 = left_ctrl_.LoadImg(sLeftControl, screen);
    left_ctrl_.SetRect(80, 595);

    bool ret1 = right_ctrl_.LoadImg(sRightControl, screen);
    right_ctrl_.SetRect(140, 595);

    bool ret3 = up_ctrl_.LoadImg(sUpControl, screen);
    up_ctrl_.SetRect(110, 575);

    bool ret4 = down_ctrl_.LoadImg(sDownControl, screen);
    down_ctrl_.SetRect(110, 615);

    //Option Key
    bool bb1 = rect_key_.LoadImg(sRectKey, screen);
    rect_key_.SetRect(SCREEN_WIDTH - 400, SCREEN_HEIGHT - 60);

    bool bb2 = triangle_key_.LoadImg(sTriangleKey, screen);
    triangle_key_.SetRect(SCREEN_WIDTH - 350, SCREEN_HEIGHT - 60);

    bool bb3 = circle_key_.LoadImg(sCircleKey, screen);
    circle_key_.SetRect(SCREEN_WIDTH - 400, SCREEN_HEIGHT - 30);

    bool bb4 = x_key_.LoadImg(sXKey, screen);
    x_key_.SetRect(SCREEN_WIDTH - 350, SCREEN_HEIGHT - 30);

    bool r1 = ret1&ret2&&ret3&&ret4;
    bool r2 = bb1&&bb2&&bb3&&bb4;

    return (r1&r2);
}

void OptionObject::Show(SDL_Renderer* screen)
{
    left_ctrl_.Render(screen);
    right_ctrl_.Render(screen);
    up_ctrl_.Render(screen);
    down_ctrl_.Render(screen);

    rect_key_.Render(screen);
    triangle_key_.Render(screen);
    circle_key_.Render(screen);
    x_key_.Render(screen);
}


void OptionObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    switch (events.type)
    {
    case SDL_MOUSEBUTTONDOWN:
    {
        int x = events.button.x;
        int y = events.button.y;
        SDL_Rect right_rect = right_ctrl_.GetRect();
        SDL_Rect left_rect = left_ctrl_.GetRect();
        SDL_Rect up_rect = up_ctrl_.GetRect();
        SDL_Rect down_rect_ = down_ctrl_.GetRect();

        if (CheckRect(right_rect, x, y))
        {
            type_ctrl_moving_ = RIGHT_MOVING;
        }
        else if (CheckRect(left_rect, x, y))
        {
            type_ctrl_moving_ = LEFT_MOVING;
        }
        else if (CheckRect(up_rect, x ,y))
        {
            type_ctrl_moving_ = UP_MOVING;
        }
        else if (CheckRect(down_rect_, x, y))
        {
            type_ctrl_moving_ = DOWN_MOVING;
        }
        else
        {
            type_ctrl_moving_ = NONE_MOVING;
        }

        SDL_Rect rectangle_rect = rect_key_.GetRect();
        SDL_Rect triangle_rect = triangle_key_.GetRect();
        SDL_Rect circle_rect = circle_key_.GetRect();
        SDL_Rect x_rect_ = x_key_.GetRect();

        if (CheckRect(rectangle_rect, x, y) == true)
        {
            type_ctrl_option_ = RECT_OPTION;
        }
        else if (CheckRect(triangle_rect, x, y) == true)
        {
            type_ctrl_option_ = TRIANGE_OPTION;
        }
        else if (CheckRect(circle_rect, x, y) == true)
        {
            type_ctrl_option_ = CIRCLE_OPTION;
        }
        else if (CheckRect(x_rect_, x, y) == true)
        {
            type_ctrl_option_ = X_OPTION;
        }
        else
        {
            type_ctrl_option_ = NONE_OPTION;
        }
        break;
    }
    case SDL_MOUSEBUTTONUP:
    {
        type_ctrl_moving_ = NONE_MOVING;
        break;
    }
    }
}

bool OptionObject::CheckRect(SDL_Rect rect, int x, int y)
{
    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}