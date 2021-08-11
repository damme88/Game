
#ifndef _END_OBJECT_H_
#define _END_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"

#define FRAME_NUMS 6

class EndObject : BaseObject
{
public:
    EndObject();
    ~EndObject();

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void set_clips();
    void Show(SDL_Renderer* des);

    UINT GetXPos() const { return x_pos_; }
    void SetPos(int xp, int yp) { x_pos_ = xp; y_pos_ = yp; }
    void SetPosTile(int xTile, int yTile);
    void SetStatus(UINT st) { m_status = st; }
    UINT GetStatus() const { return m_status; }

    enum StatusDoor
    {
        DOOR_CLOSED = 0,
        DOOR_OPENING = 1,
        DOOR_OPENED = 2,
    };
private:
    SDL_Rect frame_clip_[FRAME_NUMS];
    UINT m_DelayTime[FRAME_NUMS];
    UINT frame_;
    UINT passed_time_;
    UINT width_frame_;
    UINT height_frame_;
    UINT m_status;
    int x_pos_;
    int y_pos_;
};


#endif

