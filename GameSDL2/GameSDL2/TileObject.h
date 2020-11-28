
#ifndef TILE_OBJ_H_
#define TILE_OBJ_H_
#include "BaseObject.h"

#define TILE_FRAME 4

class TileMat : public BaseObject
{
public:
    TileMat();
    ~TileMat();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);

    void SetClip();
    void SetIsClip(const bool& is_clip) { is_clip_ = is_clip; }
    int getWidthFrame() const { return width_frame_; }
    int getHeightFrame() const { return height_frame_; }
    bool GetIsClip() const { return is_clip_; }
private:
    SDL_Rect frame_clip_[4];
    bool is_clip_;

    int width_frame_;
    int height_frame_;
    int frame_;
    unsigned int iDelay[TILE_FRAME];
    unsigned long passed_time_;
};

#endif

