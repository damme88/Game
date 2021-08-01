
#ifndef OPTION_OBJECT_H_
#define OPTION_OBJECT_H_
#include "BaseObject.h"

class OptionObject
{
public:
    enum MovingType
    {
        NONE_MOVING = 0,
        RIGHT_MOVING = 1,
        LEFT_MOVING = 2,
        UP_MOVING = 3,
        DOWN_MOVING = 4,
    };

    enum OptionType
    {
        NONE_OPTION = 0,
        RECT_OPTION = 1,
        TRIANGE_OPTION = 2,
        CIRCLE_OPTION = 3,
        X_OPTION = 4,
    };

    OptionObject();
    ~OptionObject();
    bool Init(SDL_Renderer* screen);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    int GetTypeCtrl() const { return type_ctrl_moving_; }
    void Show(SDL_Renderer* screen);
    bool CheckRect(SDL_Rect rect, int x, int y);
private:
    int type_ctrl_moving_;
    int type_ctrl_option_;

    BaseObject left_ctrl_;
    BaseObject right_ctrl_;
    BaseObject up_ctrl_;
    BaseObject down_ctrl_;

    BaseObject rect_key_;
    BaseObject triangle_key_;
    BaseObject circle_key_;
    BaseObject x_key_;
};


#endif

