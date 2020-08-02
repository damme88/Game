
#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

#define WIDHT_THREAT 44;
#define HEIGHT_THREAT 50;

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10

#define PLAYER_SPEED 2
#define PLAYER_HIGHT_VAL 18;

#define NUM_FRAME 2

class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void CheckToMap();
    void DoPlayer();
    void DrawBound(SDL_Renderer* des);

    void set_x_val(int xp) { x_val_ = xp; }
    void set_y_val(int yp) { y_val_ = yp; }
    void set_xpos(const int& xps) { x_pos_ = xps; }
    void set_ypos(const int& yps) { y_pos_ = yps; }
    void set_clips();
    void set_is_alive(bool is_alive) { is_alive_ = is_alive; }
    void set_is_clip(bool isclip) { is_clip_ = isclip; }

    int get_x_pos() { return x_pos_; }
    int get_y_pos() { return y_pos_; }
    int get_width_frame() const { return width_frame_; }
    int get_height_frame() const { return height_frame_; }
    bool get_is_alive() { return is_alive_; }
    SDL_Rect GetRectFrame();
    //Overridde
protected:
    virtual void Show(SDL_Renderer* des);

protected:
    Map* pMap_;
    Input input_type_;
    SDL_Rect frame_clip_[NUM_FRAME];

    bool is_clip_;
    bool is_alive_;

    int on_ground_;
    int width_frame_;
    int height_frame_;
    int frame_;
    int v_dir_;

    float x_val_;
    float y_val_;
    float x_pos_;
    float y_pos_;

    unsigned long passed_time_;
    unsigned int m_DelayTime[NUM_FRAME];

};

#endif //THREATS_OBJECT_H_