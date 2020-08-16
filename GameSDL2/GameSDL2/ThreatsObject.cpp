
#include "ThreatsObject.h"
#include "Geometric.h"


ThreatsObject::ThreatsObject()
{
    is_clip_ = true;
    is_alive_ = true;

    on_ground_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    frame_ = 0;
    v_dir_ = 0;

    x_val_ = 0;
    y_val_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;

    passed_time_ = 0;
    m_DelayTime[0] = 200;
    m_DelayTime[1] = 200;

    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.up_ = 0;
    input_type_.down_ = 0;
    type_ = TH_UNDEF;
    pMap_ = GameMap::GetInstance()->GetMap();
}

ThreatsObject::~ThreatsObject()
{

}

SDL_Rect ThreatsObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (is_clip_ == true)
    {
        if (ret == true)
        {
            width_frame_ = rect_.w / NUM_FRAME;
            height_frame_ = rect_.h;
        }

        set_clips();
    }
    else
    {
        width_frame_ = rect_.w;
        height_frame_ = rect_.h;
    }

    return ret;
}


void ThreatsObject::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < NUM_FRAME; i++)
        {
            frame_clip_[i].x = width_frame_*i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void ThreatsObject::DoPlayer()
{
    if (is_alive_ == true)
    {
        y_val_ += GRAVITY_SPEED;

        if (y_val_ >= MAX_FALL_SPEED)
        {
            y_val_ = MAX_FALL_SPEED;
        }

        CheckToMap();
    }
}

void ThreatsObject::DrawBound(SDL_Renderer* des)
{
    GeometricFormat outlie_size(rect_.x, rect_.y, width_frame_, height_frame_);
    ColorData color_data1(255, 0, 255);
    Gemometric::RenderOutline(outlie_size, color_data1, des);
}

void ThreatsObject::CheckToMap()
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    std::vector < std::vector<BlockMap*>> tile_list = pMap_->GetTile();
    on_ground_ = 0;

    //Check Horizontal
    int height_min = SDLCommonFunc::GetMin(height_frame_, TILE_SIZE);

    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = (y_pos_) / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    bool IsInside = SDLCommonFunc::CheckInsideMapX(x1, x2);
    IsInside &= SDLCommonFunc::CheckInsideMapY(y1, y2);

    if (IsInside)
    {
        if (x_val_ > 0) // when object is moving by right  ===>
        {
            BlockMap* pBlock1 = tile_list[y1][x2];
            BlockMap* pBlock2 = tile_list[y2][x2];
            int type1 = pBlock1->getType();
            int type2 = pBlock2->getType();

            if ((type1 != BLANK_TILE && type1 != STATE_MONEY) ||
                (type2 != BLANK_TILE && type2 != STATE_MONEY))
            {
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;
                v_dir_ = -v_dir_;
            }
        }
        else if (x_val_ < 0) // When moving by left    <====
        {
            BlockMap* pBlock1 = tile_list[y1][x1];
            BlockMap* pBlock2 = tile_list[y2][x1];
            int type1 = pBlock1->getType();
            int type2 = pBlock2->getType();

            if ((type1 != BLANK_TILE && type1 != STATE_MONEY) ||
                (type2 != BLANK_TILE && type2 != STATE_MONEY))
            {
                x_pos_ = (x1 + 1) * TILE_SIZE;
                x_val_ = 0;
                v_dir_ = -v_dir_;
            }
        }
    }

    // Check vertical
    int width_min = SDLCommonFunc::GetMin(width_frame_, TILE_SIZE);

    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_) / TILE_SIZE;

    IsInside = SDLCommonFunc::CheckInsideMapX(x1, x2);
    IsInside &= SDLCommonFunc::CheckInsideMapY(y1, y2);

    if (IsInside)
    {
        if (y_val_ > 0)
        {
            int type1 = tile_list[y2][x1]->getType();
            int type2 = tile_list[y2][x2]->getType();

            //Similar for vertical
            if ((type1 != BLANK_TILE && type1 != STATE_MONEY) ||
                (type2 != BLANK_TILE && type2 != STATE_MONEY))
            {
                y_pos_ = y2 * TILE_SIZE;
                y_pos_ -= height_frame_;
                y_val_ = 0;
                on_ground_ = 1;
                if (v_dir_ == 0)
                {
                    v_dir_ = 1;
                }
            }
        }
        else if (y_val_ < 0)
        {
            int type1 = tile_list[y1][x1]->getType();
            int type2 = tile_list[y1][x2]->getType();

            if ((type1 != BLANK_TILE && type1 != STATE_MONEY) ||
                (type2 != BLANK_TILE && type2 != STATE_MONEY))
            {
                y_pos_ = (y1 + 1) * TILE_SIZE;
                y_val_ = 0;
                on_ground_ = 1;
                if (v_dir_ == 0)
                {
                    v_dir_ = 1;
                }
            }
        }
    }

    //If there is not collision with map tile. 
    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (y_pos_ > pMap_->getMaxY())
    {
        is_alive_ = false;
    }
}

void ThreatsObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    ;
}

void ThreatsObject::Show(SDL_Renderer* des)
{
    if (is_alive_ == true)
    {
        rect_.x = x_pos_ - pMap_->getStartX();
        rect_.y = y_pos_ - pMap_->getStartY();

        if (is_clip_ == true)
        {
            if (SDL_GetTicks() - m_DelayTime[frame_] > passed_time_)
            {
                passed_time_ = SDL_GetTicks();
                ++frame_;
                if (frame_ > NUM_FRAME - 1)
                {
                    frame_ = 0;
                }
            }

            SDL_Rect* currentClip = &frame_clip_[frame_];
            BaseObject::Render(des, currentClip);
        }
        else
        {
            BaseObject::Render(des);
        }
    }
}