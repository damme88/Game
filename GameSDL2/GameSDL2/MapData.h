
#ifndef MAP_DATA_H_
#define MAP_DATA_H_

#include "TileObject.h"

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
    std::string getType() { return m_type; }
    int getXVal() { return xVal_; }
    int getYVal() { return yVal_; }
    int getXpMap() { return xp_map_; }
    int getYpMap() { return yp_map_; }

    void setTile(TileMat* pTile) { m_tile = pTile; }
    void setXIdx(int x) { x_index_ = x; }
    void setYIdx(int y) { y_index_ = y; }
    void setType(std::string type) { m_type = type; }
    void setXVal(int xv) { xVal_ = xv; }
    void setYVal(int yv) { yVal_ = yv; }
    void setXpMap(int xp) { xp_map_ = xp; }
    void setYpMap(int yp) { yp_map_ = yp; }
    void RemoveTile();
    void UpdateImage(SDL_Renderer* screen);

    bool GetHasMushroom() const { return has_mushroom_; }
    void SetHasMushroom(const bool& bMushroom) { has_mushroom_ = bMushroom; }
    bool GetOnMushroom() const { return on_mushroom_; }
    void SetOnMushroom(const bool& onMushroom) { on_mushroom_ = onMushroom; }
private:
    TileMat* m_tile;
    bool has_mushroom_;
    bool on_mushroom_;
    std::string m_type;
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
    VT(VT(BlockMap*)) GetTile() { return m_BlockList; }

    void SetStartX(int xs) { start_x_ = xs; }
    void SetStartY(int ys) { start_y_ = ys; }
    void SetMaxX(int mx) { max_x_ = mx; }
    void SetMaxY(int my) { max_y_ = my; }
    void UpdateMapInfo(int xp, int yp);
    void SetFileMap(std::string filemap) { file_name_ = filemap; }
    void AddList(VT(BlockMap*) list) { m_BlockList.push_back(list); }
    void RemoveList();
private:
    int start_x_;
    int start_y_;
    int max_x_;
    int max_y_;
    std::string file_name_;
    VT(VT(BlockMap*)) m_BlockList;
};

#endif