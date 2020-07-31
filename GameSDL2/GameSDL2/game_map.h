
#ifndef GAME_MAP_H_
#define GAME_MAP_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "TileObject.h"

#define SCROLL_SPEED 4
#define MAX_TILES 20

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
  Map* GetMap() const {return game_map_;}
  void SetMap(Map* gMap) {game_map_ = gMap;}
  bool ChecTileMoney(const int& tile);
  bool CheckBlank(const int& tile);
public:
  Map* game_map_;
  Input input_type_;

private:
    static GameMap* instance_;
};

#endif