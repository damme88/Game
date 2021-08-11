
#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"

#define  FRAME_EXP 4

class ExplosionObject : public BaseObject
{
public:
    ExplosionObject(void);
    ~ExplosionObject(void);

public:
    void set_clips();
    void set_frame(const int& fr) { frame_ = fr; }
    int get_frame() const { return frame_; }
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int get_frame_width() const { return frame_width_; }
    int get_frame_height() const { return frame_height_; }
    void ImpRender(SDL_Renderer* screen, SDL_Rect& rect_pos);
private:
    int frame_width_;
    int frame_height_;
    unsigned int frame_;
    SDL_Rect frame_clip_[FRAME_EXP];
    unsigned int iDelay[FRAME_EXP];
    unsigned long passed_time_;
};

