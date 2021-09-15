
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include <vector>
#include "MapData.h"
#include "BlockDebris.h"

#define BLOCK_BLANK         "0"
#define BLOCK_BRICK_GRN     "1"
#define BLOCK_BRICK_NOR     "2"
#define BLOCK_BIRCK_Q       "3"
#define BLOCK_BRICK_GRN2    "4"
#define BLOCK_COIN          "CO1"
#define BLOCK_USED          "10"

#define STATE_MONEY "M1"
#define  STATE_MONEY2 "24"

const std::string SkipMap[] = { "BR1", "BR2", "BR3", "TR11", "TR12", "TR13", 
                                "TR14","HR1","HR2","HR3","HR4","HR5","HR6",
                                "WB31", "WB32", "WB33", "WB34"};
const std::string CoinMap[] = { "CO1", "CO2", "DIA1", "DIA2" };

const std::string SptKni[] = { "KNI1", "VIAXE", "GUN" };
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

  void DestroyInst();

  std::string GetPathImgMap();
  std::string GetPathMapName();
  void LoadMap();
  void DrawMap(SDL_Renderer* des);
  void LoadMapTiles(SDL_Renderer* screen);
  void SetMap(Map* gMap) {game_map_ = gMap;}
  void ResetMap();
  bool CheckCoinMap(const std::string& tile);
  bool CheckSkipMap(const std::string& tile);
  int CheckSptKni(const std::string& tile);
  Map* GetMap() const { return game_map_; }
  void RenderBlockDe(SDL_Renderer* des);
  void DoNextWorldMap() { m_worldLesson++; }
  UINT GetWorldLesson() const { return m_worldLesson; }
public:
  Map* game_map_;
  Input input_type_;
  std::vector<BlockDebris*> m_BlockDeList;

private:
    std::string m_path;
    static GameMap* instance_;
    UINT m_worldLesson;
};

#endif