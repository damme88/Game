#include "BlockDebris.h"

BrickMini::BrickMini()
{
    x_val_ = 0.0;
    y_val_ = 0.0;
    speed_ = 1.0;
    destroy_ = false;
    falling_type_ = BM_LEFT_TOP;
    is_fall_ = false;
}

BrickMini::~BrickMini()
{

}

void BrickMini::UpdatePos()
{
    if (falling_type_ == BM_LEFT_TOP || falling_type_ == BM_LEFT_BOT)
    {
        float scal_x = 1.0;
        float scal_y = 1.0;
        float val = 0.0;
        float valx = 0.0;
        if (falling_type_ == BM_LEFT_TOP)
        {
            scal_x = 1.055;
            scal_y = 1.075;
            val = 4.0;
            valx = 1.0;
        }
        else
        {
            scal_x = 1.025;
            scal_y = 1.055;
            val = 2.0;
            valx = 1.0;
        }

        if (is_fall_ == false)
        {
            x_val_ += valx;
            x_val_ *= scal_x;
            y_val_ += val;
            y_val_ *= scal_y;

            rect_.x -= x_val_;
            rect_.y -= y_val_;
        }
        
        if (rect_.y < origin_yp_ - TILE_SIZE)
        {
            is_fall_ = true;
        }

        if (is_fall_ == true)
        {
            x_val_ += valx*0.5;
            x_val_ *= scal_x;
            y_val_ += val;
            y_val_ *= scal_y;

            rect_.x -= x_val_;
            rect_.y += y_val_;
        }
    }
    else if (falling_type_ == BM_RIGHT_TOP || falling_type_ == BM_RIGHT_BOT)
    {
        float scal_x = 1.0;
        float scal_y = 1.0;
        float val = 0.0;
        float valx = 0.0;
        if (falling_type_ == BM_RIGHT_TOP)
        {
            scal_x = 1.055;
            scal_y = 1.075;
            val = 4.0;
            valx = 1.0;
        }
        else
        {
            scal_x = 1.025;
            scal_y = 1.055;
            val = 2.0;
            valx = 1.0;
        }

        if (is_fall_ == false)
        {
            x_val_ += valx;
            x_val_ *= scal_x;
            y_val_ += val;
            y_val_ *= scal_y;

            rect_.x += x_val_;
            rect_.y -= y_val_;
        }

        if (rect_.y < origin_yp_ - TILE_SIZE)
        {
            is_fall_ = true;
        }

        if (is_fall_ == true)
        {
            x_val_ += valx*0.5;
            x_val_ *= scal_x;
            y_val_ += val;
            y_val_ *= scal_y;

            rect_.x += x_val_;
            rect_.y += y_val_;
        }
    }
    angle_ += 0.7;
    if (angle_ > 2*M_PI)
    {
        angle_ = 0.0;
    }
    if (rect_.y > SCREEN_HEIGHT + 100)
    {
        destroy_ = true;
        x_val_ = 0;
        y_val_ = 0;
    }
}

void BrickMini::doShow(SDL_Renderer* des)
{
    if (destroy_ == false)
    {
        UpdatePos();
        this->Show(des);
    }
}

BlockDebris::BlockDebris()
{
    x_pos_ = 0;
    y_pos_ = 0;
    m_Destroy = false;
}


BlockDebris::~BlockDebris()
{

}

void BlockDebris::Init(SDL_Renderer* des)
{
    m_BrickMini[0].LoadImg("img//block_debris.png", des);
    m_BrickMini[0].SetFallingType(BrickMini::BM_LEFT_TOP);
    m_BrickMini[0].SetRect(x_pos_, y_pos_);
    m_BrickMini[0].SetIsAngle();
    m_BrickMini[0].SetOrigin(x_pos_, y_pos_);

    m_BrickMini[1].LoadImg("img//block_debris.png", des);
    m_BrickMini[1].SetFallingType(BrickMini::BM_LEFT_BOT);
    m_BrickMini[1].SetRect(x_pos_, y_pos_);
    m_BrickMini[1].SetIsAngle();
    m_BrickMini[1].SetOrigin(x_pos_, y_pos_);

    m_BrickMini[2].LoadImg("img//block_debris.png", des);
    m_BrickMini[2].SetFallingType(BrickMini::BM_RIGHT_TOP);
    m_BrickMini[2].SetRect(x_pos_, y_pos_);
    m_BrickMini[2].SetIsAngle();
    m_BrickMini[2].SetOrigin(x_pos_, y_pos_);

    m_BrickMini[3].LoadImg("img//block_debris.png", des);;
    m_BrickMini[3].SetFallingType(BrickMini::BM_RIGHT_BOT);
    m_BrickMini[3].SetRect(x_pos_, y_pos_);
    m_BrickMini[3].SetIsAngle();
    m_BrickMini[3].SetOrigin(x_pos_, y_pos_);

}

void BlockDebris::Render(SDL_Renderer* des)
{
    m_BrickMini[0].doShow(des);
    m_BrickMini[1].doShow(des);
    m_BrickMini[2].doShow(des);
    m_BrickMini[3].doShow(des);

    if (m_BrickMini[0].GetDestroy() == true &&
        m_BrickMini[1].GetDestroy() == true &&
        m_BrickMini[2].GetDestroy() == true &&
        m_BrickMini[3].GetDestroy() == true)
    {
        m_Destroy = true;
    }
}