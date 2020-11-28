
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include <vector>
#include "MapData.h"
#include "BlockDebris.h"

#define BLOCK_BLANK         0
#define BLOCK_BRICK_GRN     1
#define BLOCK_BRICK_NOR     2
#define BLOCK_BIRCK_Q       3
#define BLOCK_BRICK_GRN2    4
#define BLOCK_COIN          9
#define BLOCK_USED          10

class GameMap
{
public:
  GameMap();
  ~GameMap();

  static GameMap* GetInstance()
  {
      if (instance_ == NULL)
          instance_ = new GameMap();
      return instance_;
  }

  void LoadMap(char* name);
  void DrawMap(SDL_Renderer* des);
  void LoadMapTiles(SDL_Renderer* screen);
  void SetMap(Map* gMap) {game_map_ = gMap;}

  bool ChecTileMoney(const int& tile);
  bool CheckBlank(const int& tile);
  Map* GetMap() const { return game_map_; }

  void RenderBlockDe(SDL_Renderer* des);
public:
  Map* game_map_;
  Input input_type_;
  std::vector<BlockDebris*> m_BlockDeList;

private:
    static GameMap* instance_;
};

#endif