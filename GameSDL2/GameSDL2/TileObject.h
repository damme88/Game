

#ifndef TILE_OBJ_H_
#define TILE_OBJ_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include <vector>

#define TILE_FRAME 4

class TileMat : public BaseObject
{
public:
    TileMat();
    ~TileMat();
    bool LoadImg(std::string path, SDL_Renderer* screen);

    void SetClip();
    void SetIsClip(const bool& is_clip) { is_clip_ = is_clip; }
    void Show(SDL_Renderer* des);
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

class BlockMap
{
public:
    BlockMap();
    ~BlockMap();
    void Update();
    void Render(SDL_Renderer* screen);
    TileMat* GetTile() const { return m_tile; }

    int getXIdx() { return x_index_; }
    int getYIdx() { return y_index_; }
    int getType() { return m_type; }
    int getXVal() { return xVal_; }
    int getYVal() { return yVal_; }
    int getXpMap() { return xp_map_; }
    int getYpMap() { return yp_map_; }

    void setTile(TileMat* pTile) { m_tile = pTile; }
    void setXIdx(int x) { x_index_ = x; }
    void setYIdx(int y) { y_index_ = y; }
    void setType(int type) { m_type = type; }
    void setXVal(int xv) { xVal_ = xv; }
    void setYVal(int yv) { yVal_ = yv; }
    void setXpMap(int xp) { xp_map_ = xp; }
    void setYpMap(int yp) { yp_map_ = yp; }
    void RemoveTile();
private:
    TileMat* m_tile;
    int m_type;
    int x_index_;
    int y_index_;
    int xp_map_;
    int yp_map_;
    int xVal_;
    int yVal_;
};

class Map
{
public:
    Map();
    ~Map();

    int getStartX() const { return start_x_; }
    int getStartY() const { return start_y_; }
    int getMaxX() const { return max_x_; }
    int getMaxY() const { return max_y_; }
    VT(VT(BlockMap*)) GetTile() { return m_tile; }

    void SetStartX(int xs) { start_x_ = xs; }
    void SetStartY(int ys) { start_y_ = ys; }
    void SetMaxX(int mx) { max_x_ = mx; }
    void SetMaxY(int my) { max_y_ = my; }
    void UpdateMapInfo(int xp, int yp);
    void SetFileMap(std::string filemap) { file_name_ = filemap; }
    void AddList(VT(BlockMap*) list) { m_tile.push_back(list); }
private:
    int start_x_;
    int start_y_;
    int max_x_;
    int max_y_;
    std::string file_name_;
    VT(VT(BlockMap*)) m_tile;
};

#endif

