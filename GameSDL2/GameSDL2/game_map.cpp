
#include "game_map.h"

GameMap* GameMap::instance_ = NULL;

GameMap::GameMap()
{
    game_map_ = new Map();
}

GameMap::~GameMap()
{
    delete game_map_;
}

void GameMap::LoadMap(char* name)
{
  FILE* fp = NULL;
  fopen_s(&fp, name, "rb");
  if (fp == NULL)
  {
    return;
  }

  for (int y = 0; y < MAX_MAP_Y; y++)
  {
      std::vector<BlockMap*> xTemp;
    for (int x = 0; x < MAX_MAP_X; x++)
    {
      BlockMap* pBlock = new BlockMap();
      int val = 0;
      fscanf_s(fp, "%d", &val );
      if (val > 0)
      {
        pBlock->setType(val);
        pBlock->setYIdx(y);
        pBlock->setXIdx(x);
      }
      xTemp.push_back(pBlock);
    }
    game_map_->AddList(xTemp);
  }

  game_map_->SetMaxX(MAX_MAP_X*TILE_SIZE);
  game_map_->SetMaxY(MAX_MAP_Y*TILE_SIZE);

  game_map_->SetFileMap((std::string)name);

  fclose(fp);
}

void GameMap::LoadMapTiles(SDL_Renderer* screen)
{
    char filename[40];
    for (int y = 0; y < MAX_MAP_Y; y++)
    {
        for (int x = 0; x < MAX_MAP_X; x++)
        {
            BlockMap* pBlock = game_map_->GetTile()[y][x];
            if (pBlock != NULL)
            {
                int val = game_map_->GetTile()[y][x]->getType();
                sprintf_s(filename, "map/%d.png", val);
                TileMat* pTile = new TileMat();
                if (val == 3)
                {
                    pTile->SetIsClip(true);
                }
                bool ret = pTile->LoadImg(filename, screen);
                if (ret)
                {
                    game_map_->GetTile()[y][x]->setTile(pTile);
                }
            }
        }
    }
}



void GameMap::DrawMap(SDL_Renderer* des)
{
  int map_x = 0;
  int x1 = 0;
  int x2 = 0;

  int map_y = 0;
  int y1 = 0;
  int y2 = 0;

  // map_x la vi tri tile hien tai
  map_x = game_map_->getStartX()/TILE_SIZE;

  // gia tri x1 la gia tri con thua sau phep chia
  x1 = (game_map_->getStartX() %TILE_SIZE);

  if (x1 == 0)
  {
      // neu phep chia co so du bang 0, nghia la start_x = nguyen lan TILE
      x2 = x1 + SCREEN_WIDTH;
  }
  else
  {
      // Neu phep co du > 0 thi cong them 1 TILE SIZE
      x2 = x1 + SCREEN_WIDTH + TILE_SIZE;
  }

  map_y = game_map_->getStartY()/TILE_SIZE;
  y1 = (game_map_->getStartY()%TILE_SIZE);
  if (y1 == 0)
  {
      y2 = y1 + SCREEN_HEIGHT;
  }
  else
  {
      y2 = y1 + SCREEN_HEIGHT + TILE_SIZE;
  }
  
  //gia tri am la de cac tile size hien thi khuat 1 phan ve ben trai, vi player di chuyen ve ben phai
  for (int y_pos = -y1; y_pos < y2; y_pos += TILE_SIZE)
  {
    map_x = game_map_->getStartX()/TILE_SIZE;
    for (int x_pos = -x1; x_pos < x2; x_pos +=TILE_SIZE)
    {
      BlockMap* pBlock = game_map_->GetTile()[map_y][map_x];
      if (pBlock->GetTile() != NULL)
      {
          pBlock->setXpMap(x_pos);
          pBlock->setYpMap(y_pos);
          pBlock->Update();
          pBlock->Render(des);
      }
      map_x++;
    }
    map_y++;
  }
}

bool GameMap::ChecTileMoney(const int& tile)
{
    if (tile == STATE_MONEY ||
        tile == STATE_MONEY ||
        tile == STATE_MONEY2 ||
        tile == STATE_MONEY2)
    {
        return true;
    }
    return false;
}

bool GameMap::CheckBlank(const int& tile)
{
    if (tile == BLANK_TILE)
        return true;
    return false;
}