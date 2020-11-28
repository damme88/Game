

#ifndef BLOCK_DEBRIS_H_
#define BLOCK_DEBRIS_H_

#include "TileObject.h"

class BrickMini : public TileMat
{
public:
    BrickMini();
    ~BrickMini();
    enum FallingType
    {
        BM_LEFT_TOP = 0,
        BM_LEFT_BOT = 1,
        BM_RIGHT_TOP = 2,
        BM_RIGHT_BOT = 3
    };
    void UpdatePos();
    void doShow(SDL_Renderer* des);
    void SetVal(const int& x, const int& y) { x_val_ = x; y_val_ = y; }
    int GetXval() const { return x_val_; }
    int GetYval() const { return y_val_; }
    bool GetDestroy() const { return destroy_; }
    void SetDestroy(bool bDestroy) { destroy_ = bDestroy; }
    void SetOrigin(int xo, int yo) { origin_xp_ = xo, origin_yp_ = yo; }
    void SetFallingType(int type) { falling_type_ = type; }
private:
    bool destroy_;
    int x_val_;
    int y_val_;
    int speed_;
    int falling_type_;
    int origin_xp_;
    int origin_yp_;
    bool is_fall_;
};

class BlockDebris
{
public:
    BlockDebris();
    ~BlockDebris();
    void Init(SDL_Renderer* des);
    void Render(SDL_Renderer* des);
    void SetPos(const int& xp, const int& yp) { x_pos_ = xp; y_pos_ = yp; }
    bool GetDestroy() const { return m_Destroy; }
private:
    BrickMini m_BrickMini[4];
    int x_pos_;
    int y_pos_;
    bool m_Destroy;
};

#endif

